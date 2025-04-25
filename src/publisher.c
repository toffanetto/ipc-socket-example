#include "ipc_socket.h"

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    socket_msg_t * buffer;

    socket_msg_t msg = {"Hello from client", 2048};


    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) { 
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    send(sock, &msg, sizeof(msg), 0);
    printf("Message sent to server\n");

    read(sock, buffer, sizeof(buffer));
    printf("Server: %s\n", buffer->msg);

    close(sock);
    return 0;
}