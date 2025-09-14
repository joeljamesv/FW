#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

const char* SOCKET_PATH = "/tmp/bootlistener.sock";
int server_fd;

int main() {
    // 1. Create socket
     server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
     if (server_fd < 0) {
          std::cerr<<"Socket creation failed";
          return 1;
     }

     std::cout << "Socket created successfully.\n";

    // 2.Binding

     sockaddr_un addr{};                // create address structure
     addr.sun_family = AF_UNIX;         // UNIX domain socket
     strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1); // copy path

     // Remove old socket file if exists
     unlink(SOCKET_PATH);

     if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
     std::cerr<<"Binding Failed";
     return 1;
     }

     std::cout << "Socket bound to " << SOCKET_PATH << std::endl;

     // 3.Listening to clients
     if (listen(server_fd, 5) < 0) {
     std::cerr<<"listening Failed";
     return 1;
     }

     std::cout << "Socket is now listening for clients..." << std::endl;

     // 4.Accept client connection

     while (true) {
     // 4. Accept a client connection
          int client_fd = accept(server_fd, nullptr, nullptr);
          if (client_fd < 0) {
               std::cerr<<"Accept Failed";
               continue;  // if error, wait for the next client
          }

          // 5. Read message from client
          char buf[256];
          ssize_t n = read(client_fd, buf, sizeof(buf) - 1);
          if (n > 0) {
               buf[n] = '\0';  // null-terminate
               std::string cmd(buf);
               std::cout << "Data Received: " << cmd << std::endl;

          

          }
          close(client_fd);  // close connection after reading
     }
     return 0;

}