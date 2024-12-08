## C codes written as part of the Network Programming Lab Practicals

### Content
This repository contains programs for the following implementations:

- TCP Echo Server and Client
- TCP Chat Server and Client, i.e., two way communication
- TCP Echo Server which reverses received client message before sending as echo, practice such variations for evaluations
- UDP Echo Server and Client
- Broadcast Server and Client using UDP 
- Multicast Server and Client using UDP

### Execution

Run the server program (or whichever program is supposed to receive the message or accept connections): 
```bash
gcc server.c -o <name>
./<name>
```
Run the client program (or whichever program is supposed to send the message or establish connections): 

```bash
gcc client.c -o <name>
./<name>
```
