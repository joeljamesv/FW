#include <sys/socket.h>
#include <sys/un.h>
#include <termios.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

std::string getPassword(const std::string &prompt) {
    std::cout << prompt;
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);  // get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~ECHO;  // disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string password;
    std::getline(std::cin, password);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // restore settings
    std::cout << std::endl;
    return password;
}

const char *SOCKET_PATH = "/tmp/bootlistener.sock";

int main() {
    // 1. Create socket
    int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        std::cerr << "Socket Failed";
        return 1;
    }

    // 2. Connect to server
    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "Connection Failed";
        return 1;
    }

    // 3. Send message
    while (true) {
        std::cout << "username: ";
        std::string username;
        std::getline(std::cin, username);
        write(sock_fd, username.c_str(), username.size());

        // Receive server response (password prompt or invalid username)
        char buf[256];
        ssize_t n = read(sock_fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            std::cout << buf;
        }

        if (std::string(buf).find("password: ") != std::string::npos) {
            std::string password = getPassword("");
            write(sock_fd, password.c_str(), password.size());

            // Receive login result
            n = read(sock_fd, buf, sizeof(buf) - 1);
            if (n > 0) {
                buf[n] = '\0';
                std::cout << buf;
            }

            if (std::string(buf).find("Entering Console") != std::string::npos) {
                break;  // proceed to command mode
            }
        }
    }

    // Logged in: normal command loop
    while (true) {
        std::cout << "console: ";
        std::string cmd;
        std::getline(std::cin, cmd);
        write(sock_fd, cmd.c_str(), cmd.size());

        char buf[256];
        ssize_t n = read(sock_fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            std::cout << buf << std::endl;
        }

        if (cmd == "exit") break;
    }

    close(sock_fd);
    return 0;
}
