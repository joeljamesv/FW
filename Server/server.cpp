#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <iostream>
#include "commandcenter.hpp"

const char* SOCKET_PATH = "/tmp/bootlistener.sock";
int server_fd;

int main() {
    // 1. Create socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed";
        return 1;
    }

    // 2.Binding

    sockaddr_un addr{};                                              // create address structure
    addr.sun_family = AF_UNIX;                                       // UNIX domain socket
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);  // copy path

    // Remove old socket file if exists
    unlink(SOCKET_PATH);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Binding Failed";
        return 1;
    }

    // 3.Listening to clients
    if (listen(server_fd, 5) < 0) {
        std::cerr << "listening Failed";
        return 1;
    }

    // 4.Accept client connection
    bool stopServer = false;

    while (!stopServer) {
        // 4. Accept a client connection
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            std::cerr << "Accept Failed";
            continue;  // if error, wait for the next client
        }

        // 5. Read message from client
        bool logged_in = false;

        while (!logged_in) {
            char buf[256];
            ssize_t n = read(client_fd, buf, sizeof(buf) - 1);
            if (n <= 0) continue;
            buf[n] = '\0';
            std::string input(buf);

            // Expect username first
            if (!logged_in) {
                if (input == "root") {
                    std::string ack = "password: ";
                    write(client_fd, ack.c_str(), ack.size());

                    // Read password
                    n = read(client_fd, buf, sizeof(buf) - 1);
                    if (n <= 0) continue;
                    buf[n] = '\0';
                    std::string password(buf);

                    if (password == "password") {
                        logged_in = true;
                        std::string ack2 = "Entering Console\n";
                        write(client_fd, ack2.c_str(), ack2.size());
                    }
                } else {
                    std::string ack2 = "Invalid Credentials\n";
                    write(client_fd, ack2.c_str(), ack2.size());
                }
            }
        }

        // Once logged in, echo whatever client sends
        while (true) {
            char buf[256];
            ssize_t n = read(client_fd, buf, sizeof(buf) - 1);
            if (n <= 0) break;
            buf[n] = '\0';
            std::string cmd(buf);

            if (cmd == "exit") {
                std::string ack = "Console exited\n";
                write(client_fd, ack.c_str(), ack.size());
                stopServer = true;
                close(client_fd);

                break;
            }

            // Echo back other commands
            process_command(cmd);
            write(client_fd, cmd.c_str(), cmd.size());
        }
    }
    close(server_fd);
    return 0;
}