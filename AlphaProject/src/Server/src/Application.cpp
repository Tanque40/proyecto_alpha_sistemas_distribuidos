#include <iostream>

#include "Server/SocketTCP.h"

int main() {
    std::string message, response;
    SocketTCP serverSocket(SocketType::Server);
    int newSocket;

    while (serverSocket.IsServerRunning()) {
        if (serverSocket.isListenning()) {
            std::cout << "Error on Listenning" << std::endl;
        }
        if ((newSocket = accept(serverSocket.GetSocketFileDescriptor(), (struct sockaddr*)serverSocket.GetSocketAddressPtr(),
                                serverSocket.GetAddressLenghtPtr())) < 0) {
            std::cout << "Error: On accept new socket" << std::endl;
        }

        if (serverSocket.ReciveMessage(newSocket, &response)) {
            std::cout << "Mensaje Recibido: " << response.c_str() << std::endl;
        } else {
            std::cout << "error al recibir mensaje" << std::endl;
        }

        message = "Hola desde el server";
        if (serverSocket.SendMessage(newSocket, &message)) {
            std::cout << "Respuesta enviada" << std::endl;
        }
    }

    // closing the connected socket
    close(newSocket);

    serverSocket.EndConnection();
    return 0;
}