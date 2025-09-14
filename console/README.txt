

SERVER
1. Create a socket: a mailbox to which the client can connect to.

server_fd = socket(AF_UNIX, SOCK_STREAM, 0); 

2.Binding : once the mailbox is made we need to add a address to the mailbox which is what
done in case of Binding

bind(server_fd, (struct sockaddr*)&addr, sizeof(addr))

3.Listening to clients : basically waiting for the mailman to post something in the mailbox

listen(server_fd, 5)

4.Accept client connection

int client_fd = accept(server_fd, nullptr, nullptr);

5.Accept the message

ssize_t n = read(client_fd, buf, sizeof(buf) - 1);

6.Close the connection

-----------------------------------------------------

CLIENT

1. Create a socket

2. Connect to the server 

3. Send a message

write(sock_fd, msg.c_str(), msg.size());

4. Close the connection

