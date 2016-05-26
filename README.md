# Pipe-Two-Server
Connect to Two servers, and passes messages to each others.  
[Compiled binary](https://www.dropbox.com/s/f66mrdja8bpyjdn/Pipe-Two-Server.exe?dl=0)

###Purpose
To forward a service on a windows PC, to a linux server.  
Useful if your windows PC does not have a public ip.

You can write a compatible program runs on Windows,  
to forward your service onto a pubilc Windows server.

###Example
- Public Server  
  ```bash
  mkfifo fifo
  while true; do nc -vl port1 < fifo | nc -vl port2 > fifo; done
  ```
  
- Windows PC  
  ```
  pipe-two-server.exe 127.0.0.1 service_port linux_server_ip port1
  ```
  Now you can connect to **linux_server_ip:port2** just like the service is running there.

###Problem to fix
If **pipe-two-server.exe** has been terminated (while no client connectingto linux server),  
the `nc -vl port2` command will keep listening, and the while statement will not continue.

Now just fix it by connecting to **linux_server_ip:port2** to relief it from infinite listening.

!!! Hearing about broken after long time connection.

###TODO
- connect to service only when notice that client is connecting
  (this is hard to design)
- not to connect to ip1:port1 until ip2:port2 is connected
- prevent suspending listen on the linux_server

###NOTES
tested service (works with this project)
- RDP (port 3389)

This project is just a simulation of folling command on a linux pc
```bash
mkfifo fifo
while true; do nc localhost service_port < fifo | nc linux_server_ip port1 > fifo; done
```
