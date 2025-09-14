#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

const char* SOCKET_PATH = "/tmp/bootlistener.sock";

int main() {

    // 1. Create socket
    int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        std::cerr<<"Socket Failed";
        return 1;
    }

    // 2. Connect to server
    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path)-1);

    if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr<<"Connection Failed";
        return 1;
    }

    // 3. Send message
   
     std::string msg;
     std::getline(std::cin, msg);
     write(sock_fd, msg.c_str(), msg.size());
     char buf[256];
     ssize_t n = read(sock_fd, buf, sizeof(buf) - 1);
     if (n > 0) 
     {
          buf[n] = '\0';  
          std::cout << buf << std::endl;
     }
    close(sock_fd);
    return 0;
}
