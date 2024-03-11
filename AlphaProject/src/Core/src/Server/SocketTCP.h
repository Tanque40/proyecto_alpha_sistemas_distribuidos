#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define MAX_CONNECTIONS 50  // ? Same as Java

enum SocketType {
    Server,
    Client
};

class SocketTCP {
   private:
    int status, readedValue, socketFileDescriptor, newSocket;
    int opt = 1;
    std::string ipAddress;
    struct sockaddr_in socketAddress;
    socklen_t addressLenght = sizeof(socketAddress);
    bool shutDownServer = false;

    SocketType socketType;

   public:
    inline SocketTCP() = default;
    SocketTCP(SocketType socketType, std::string ipAddress = "");

    inline bool IsServerRunning() const { return !shutDownServer; }
    inline int GetSocketFileDescriptor() const { return socketFileDescriptor; }
    inline sockaddr_in* GetSocketAddressPtr() { return &this->socketAddress; }
    inline socklen_t* GetAddressLenghtPtr() { return &this->addressLenght; }

    bool isListenning();
    bool SendMessage(int socket, std::string* message);
    bool ReciveMessage(int socket, std::string* response);
    void EndConnection();
};
