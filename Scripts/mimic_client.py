import socket import time

    CONNECT_TIMEOUT = 3.0 RECV_STEP = 0.1 RECV_TOTAL_TIMEOUT = 5.0

    class MimicClient:def __init__(self, socket_path = "/tmp/bootlistener.sock") :self.socket_path = socket_path self.sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) self.sock.settimeout(CONNECT_TIMEOUT) self.sock.connect(self.socket_path) self.sock.settimeout(0.2)

                                                                                                                                                                                                                                           def recv_until(self, needle, timeout = RECV_TOTAL_TIMEOUT) :deadline = time.time() + timeout buf = b "" while time.time() < deadline:
            try:
                part = self.sock.recv(1024)
                if not part:
                    break
                buf += part
                try:
                    s = buf.decode(errors='ignore')
                except:
                    s = str(buf)
                if needle in s:
                    return s
            except (BlockingIOError, socket.timeout):
                pass
            except Exception:
                break
            time.sleep(RECV_STEP)
        try:
            return buf.decode(errors='ignore')
        except:
            return None

    def send_no_newline(self, text):
        if isinstance(text, str):
            data = text.encode()
        else:
            data = text
        self.sock.sendall(data)

    def close(self):
        self.sock.close()
