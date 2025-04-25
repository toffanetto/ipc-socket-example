#include "ipc_socket.h"

int main()
{
    int server_fd, rx_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    socket_msg_t *buffer;

    socket_msg_t msg = {"Hello from server", 1024};

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

    while (1)
    {
        printf("Waiting for a connection...\n");
        // Accept a connection
        if ((rx_socket = accept(server_fd, (struct sockaddr *)&address,
                                (socklen_t *)&addrlen)) < 0)
        {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        // Exchange messages
        read(rx_socket, buffer, sizeof(buffer));
        printf("Client: %s\n", buffer->msg);

        send(rx_socket, &msg, sizeof(msg), 0);
        printf("msg sent to client\n");
    }

    close(rx_socket);
    close(server_fd);
    return 0;
}