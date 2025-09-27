SERVER
1. Create a socket : a mailbox to which the client can connect to.
                     server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

2.Binding : once the mailbox is made we need to add a address to the mailbox which is what done
                in case of Binding
                bind(server_fd, (struct sockaddr*)&addr, sizeof(addr))

3.Listening to clients: basically waiting for the mailman to post something in the mailbox

listen(server_fd, 5)

4.Accept client connection

int client_fd = accept(server_fd, nullptr, nullptr);

5.Accept the message

    ssize_t n = read(client_fd, buf, sizeof(buf) - 1);

6.Close the connection

In server the first while loop is for connections and second while loop for getting values
from the server

-----------------------------------------------------

COMMANDCENTER

A command center is made to multiplex the commands that are received through the server

commands : <action>:<target>:<property>:<value>

<action>

get:
set:

<target>

led: firefly

<property>

state:

<value>

led
off:
on:






