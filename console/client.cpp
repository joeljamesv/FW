#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

const char* SOCKET_PATH = "/tmp/bootlistener.sock";

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./client <message>\n";
        return 1;
    }

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
    std::string msg = argv[1];
    write(sock_fd, msg.c_str(), msg.size());

    std::cout << "Message sent: " << msg << std::endl;

    close(sock_fd);
    return 0;
}
