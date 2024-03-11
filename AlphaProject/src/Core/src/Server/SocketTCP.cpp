#include "appch.h"
#include "SocketTCP.h"

SocketTCP::SocketTCP(SocketType socketType, std::string ipAddress) : ipAddress(ipAddress) {
    if ((socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\n Socket creation error \n"
                  << std::endl;
    }

    if (SocketType::Server == socketType) {
        // Forcefully attaching socket to the port 8080
        if (setsockopt(socketFileDescriptor, SOL_SOCKET,
                       SO_REUSEADDR, &opt,
                       sizeof(opt))) {
            std::cout << "\nsetsockopt\n"
                      << std::endl;
        }
        socketAddress.sin_addr.s_addr = INADDR_ANY;
    }

    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(PORT);

    if (SocketType::Client == socketType) {
        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, ipAddress.c_str(), &socketAddress.sin_addr) <= 0) {
            std::cout << ipAddress << std::endl;
            std::cout << "\nInvalid address/ Address not supported \n"
                      << std::endl;
        }
    } else if (SocketType::Server == socketType) {
        // Forcefully attaching socket to the port 8080
        if (bind(socketFileDescriptor, (struct sockaddr*)&socketAddress,
                 addressLenght) < 0) {
            std::cout << "bind failed" << std::endl;
        }
        std::cout << "Server is listening" << std::endl;
    }
}

bool SocketTCP::isListenning() {
    return listen(socketFileDescriptor, MAX_CONNECTIONS) < 0;
}

bool SocketTCP::SendMessage(int socket, std::string* message) {
    if (!socket) {
        if ((status = connect(socketFileDescriptor, (struct sockaddr*)&socketAddress,
                              sizeof(socketAddress))) < 0) {
            std::cout << "\nConnection Failed \n"
                      << std::endl;
            return false;
        }
        send(socketFileDescriptor, message->c_str(), message->size(), 0);
        return true;
    } else {
        send(socket, message->c_str(), message->size(), 0);
        return true;
    }
}

bool SocketTCP::ReciveMessage(int socket, std::string* response) {
    if (!socket) {
        readedValue = read(socketFileDescriptor, response, 1024 - 1);
    } else {
        readedValue = read(socket, response, 1024 - 1);
    }

    return readedValue > 0;
}

void SocketTCP::EndConnection() {
    if (SocketType::Server == socketType)
        close(newSocket);
    close(socketFileDescriptor);
}
