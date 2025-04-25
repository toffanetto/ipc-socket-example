#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

#define SERVER_IP "143.106.207.65"

typedef struct socket_msg
{
    char msg[100];
    int code;
} socket_msg_t;




