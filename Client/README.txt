CLIENT

1. Create a socket

2. Connect to the server 

3. Send a message

write(sock_fd, msg.c_str(), msg.size());

4. Close the connection


5. update the terminal setting so that password wont be visible.

tcgetattr(STDIN_FILENO, &oldt);
newt = oldt;
newt.c_lflag &= ~ECHO;
tcsetattr(STDIN_FILENO, TCSANOW, &newt);
