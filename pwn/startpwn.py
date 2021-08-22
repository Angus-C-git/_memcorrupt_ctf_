#!/usr/bin/python3 
import subprocess
import os, signal


def kill_server(name):    
    try:
         
        # iterating through each instance of the process
        for line in os.popen("ps ax | grep " + name + " | grep -v grep"):
            fields = line.split()
             
            # extracting Process ID from the output
            pid = fields[0]
             
            # terminating process
            os.kill(int(pid), signal.SIGKILL)
        print("Process Successfully terminated")
    except:
        print("Run me as root, $sudo startpwn")
  


def main():
    print("""

Starting pwn servers...

==== [challenge -> host:port mapping]  ====


    natt -> localhost:4242
    skid -> localhost:6447


    """)

    skid = subprocess.Popen(
        "./start_skid",
        stdout=subprocess.PIPE,
    )

    natt = subprocess.Popen(
        "./start_natt",
        stdout=subprocess.PIPE,
    )

    print("Press any key to kill the servers ...")
    input()
    kill_server("./skid")
    kill_server("./natt")



if __name__ == "__main__":
    main()
