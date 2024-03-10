#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 4000

class Server {
   public:
    static void Attach() {
        int server_fd, new_socket;
        ssize_t valread;
        struct sockaddr_in address;
        int opt = 1;
        socklen_t addrlen = sizeof(address);
        char buffer[1024] = {0};
        std::string hello = "Hello from server";

        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            std::cout << "fail" << std::endl;
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
            std::cout << "fail" << std::endl;
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            std::cout << "fail" << std::endl;
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0) {
            std::cout << "fail" << std::endl;
            perror("listen");
            exit(EXIT_FAILURE);
        }
        std::cout << "Waiting for connection" << std::endl;
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        valread = read(new_socket, buffer, 1024 - 1);  // subtract 1 for the null
                                                       // terminator at the end
        std::cout << buffer << std::endl;
        send(new_socket, hello.c_str(), hello.size(), 0);
        std::cout << "Hello message sent\n"
                  << std::endl;

        // closing the connected socket
        close(new_socket);
        // closing the listening socket
        close(server_fd);
    }
};