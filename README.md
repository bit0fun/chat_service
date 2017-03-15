# chat_service (name TBD)

## What is this?
Plain and simple, this project is a chat service written in C. The idea is to make a secure (read, encrypted communication)
chat service that allows for simple file transfer, email-like messaging, real time chat rooms, that can be accessed
over a website or command line.

## How can I use this?
At the moment, all you can do is connect to a server and have it either confirm that your username is in its database,
or be denied. After 5 times, you get disconnected from the server. (Real functionality is comming soon!)
To compile it, two scripts are included to compile the server and client programs independently. The makefiles also have
GDB debugging targets available as well.

##  How does it work?
A client opens a TCP connection is made to the server, which can be an IP address or domain name, which then sends the user's
username to the server. The server then looks up the username, which will either send an ACK or NACK, on whether it is found.
After 5 tries, the server closes the connection to prevent some spam.
All data is written to individual log files, to prevent the command line from being bombarded. 
