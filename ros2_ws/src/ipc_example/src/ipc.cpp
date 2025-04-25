#include "ipc_example/ipc.hpp"

namespace ipc
{
    IpcExample::IpcExample() : Node("ipc_example")
    {
        msg_pub_ = this->create_publisher<std_msgs::msg::String>("/icp_msg", 1);
        msg_timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                             std::bind(&IpcExample::msg_timer_callback, this));

        addrlen = sizeof(address);
        msg = {"Hello from server", 1024};

        // Create socket
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Bind the socket
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY; // Bind to any interface
        address.sin_port = htons(PORT);

        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            perror("bind failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Listen for a connection
        if (listen(server_fd, 3) < 0)
        {
            perror("listen failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
    }

    IpcExample::~IpcExample()
    {
    }

    void IpcExample::msg_timer_callback()
    {
        printf("Waiting for a connection...\n");

        // Accept a connection
        if ((rx_socket = accept(server_fd, (struct sockaddr *)&address,
                                (socklen_t *)&addrlen)) < 0)
        {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        // Receiving
        read(rx_socket, &buffer, sizeof(buffer));
        printf("Client msg : %s\n", buffer.msg);
        printf("Client code: %d\n", buffer.code);

        // Sending
        send(rx_socket, &msg, sizeof(msg), 0);
        printf("msg sent to client\n");

        std_msgs::msg::String msg;
        msg.data = std::string(buffer.msg);
        RCLCPP_INFO(this->get_logger(), "Publishing IPC message | %d", buffer.code);
        RCLCPP_INFO(this->get_logger(), buffer.msg);
        msg_pub_->publish(msg);
    }

} // namespace ipc
