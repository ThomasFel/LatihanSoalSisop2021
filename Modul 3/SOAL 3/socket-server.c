#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char *msg_tambah = "Penambahan berhasil";
    char *msg_kurang = "Pengurangan berhasil";
    char *msg_salah = "command tidak sesuai";
    int num = 5;
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char buffer[1024] = {0};
        valread = read(new_socket , buffer, 1024);

        if (strcmp(buffer, "tambah") == 0) {
            send(new_socket, msg_tambah, strlen(msg_tambah), 0);
            num++;
            printf("Message sent\n");
        }
        
        else if (strcmp(buffer, "kurang") == 0) {
            send(new_socket, msg_kurang, strlen(msg_kurang), 0);
            num--;
            printf("Message sent\n");
        }
        
        else if (strcmp(buffer, "cek") == 0) {
            char str[100];
            sprintf(str, "%d", num);
            send(new_socket, str, strlen(str), 0);
            printf("Message sent\n");
        }
        
        else {
            send(new_socket, msg_salah, strlen(msg_salah), 0);
            printf("Message sent\n");
        }

        memset(buffer, '0', 1024);
    }

    return 0;
}