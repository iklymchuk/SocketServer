/*
 ============================================================================
 Name        : SocketServer.c
 Author      : Ivan Klymchuk
 Version     : 1.0
 Copyright   : Feel free to use
 Description : Socket server
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//********socket***********//
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(void) {

    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server, client;
        server.sin_family = AF_INET;
        server.sin_port = htons(48999);
        server.sin_addr.s_addr = INADDR_ANY;


    bind(socket_desc, (struct sockaddr *) & server, sizeof(server));

    int size = 3;
    listen (socket_desc, size);

    int c = sizeof(struct sockaddr_in);

    int new_socket[size];

    while (size){
        new_socket[0] = accept(socket_desc, (struct sockaddr *) & client, (socklen_t *) & c);

    char * message;
    char client_request[40960];
        recv(new_socket[0], client_request, 40960, 0);

        if (!strcmp(client_request, "startServer")) {
        	//system("sh startServer.sh");
            message = "Server started";
        } else if (!strcmp(client_request, "restartServer")) {
        	//system("sh restartServer.sh");
        	message = "Server restarted";
        } else {
        	message = "Incorrect command!";
        }

    send(new_socket[0], message, strlen(message), 0);
    close(new_socket[0]);
    size--;
    }

}


