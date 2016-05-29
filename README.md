# Pipe-Two-Server
Connect to Two servers, and passes messages to each others.

Once the server-on-linux has been connected by user, it sends  
a character 'A', to inform Pipe-Two-Server. Then Pipe-Two-Server  
will connect to local service.

[Compiled binary](https://www.dropbox.com/s/f66mrdja8bpyjdn/Pipe-Two-Server.exe?dl=0)

###Purpose
To forward a service on a windows PC, to a linux server.  
Useful if your windows PC does not have a public ip.

here's link for [server-on-linux](https://www.dropbox.com/s/lg6muziiqoel3hf/server-on-linux?dl=0)
You can write a compatible program runs on Windows,  
to forward your service onto a pubilc Windows server.

###Example
- Public Server  
  ```bash
  while true; do
  server-on-linux port_for_windows port_for_service_use
  done
  ```
  notice that this should be run before Pipe-Two-Server runs.
  
- Windows PC  
  ```
  pipe-two-server.exe service_port linux_server_ip port1
  ```
  Now you can connect to __linux_server_ip:port_for_service_user__  
  just like the service is running there.

###Problem to fix
If **pipe-two-server.exe** has been terminated (while no client connectingto linux server),  
the `server-on-linux` command will keep listening, and the while statement will not continue.

Now just fix it by connecting to **linux_server_ip:port2** to relief it from infinite listening.

###TODO
- prevent suspending listen on the linux_server

###NOTES
tested service (works with this project)
- RDP (port 3389)
