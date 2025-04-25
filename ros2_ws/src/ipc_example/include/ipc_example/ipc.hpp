#ifndef ipc_example__ipc_HPP_
#define ipc_example__ipc_HPP_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Socket includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_IP "143.106.207.65"

typedef struct socket_msg
{
    char msg[100];
    int code;
} socket_msg_t;

namespace ipc
{
    class IpcExample : public rclcpp::Node
    {
    public:
        IpcExample();
        ~IpcExample();

    private:
        int server_fd, rx_socket;
        struct sockaddr_in address;
        int addrlen;
        socket_msg_t buffer;
        socket_msg_t msg;

        void msg_timer_callback();

        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr msg_pub_;
        rclcpp::TimerBase::SharedPtr msg_timer_;
    };
} // namespace ipc
#endif // ipc_example__ipc_HPP_
