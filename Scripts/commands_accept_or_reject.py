#script for sending bad and good commands to the server.

import subprocess
import time

binary_path = "../Client/bin/execute_me"  # adjust path

proc = subprocess.Popen(
    [binary_path],
    stdin=subprocess.PIPE,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    text=True,
    bufsize=1  # line-buffered
)

def print_output():
    while True:
        line = proc.stdout.readline()
        if not line:
            break
        print(line, end='')  # print as-is without extra newline

# Step 1: send root
proc.stdin.write("root\n")
proc.stdin.flush()
time.sleep(1)  # wait a bit
print_output()  # print anything server sent

# Step 2: send password
proc.stdin.write("password\n")
proc.stdin.flush()
time.sleep(1)
print_output()

# Step 3: send exit
proc.stdin.write("exit\n")
proc.stdin.flush()
time.sleep(1)
print_output()

proc.wait()
