#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(const int argc, const char **argv) {

	char server_msg[256] = "Hello from the server socket!";

	// create "server" socket
	int server_socket, client_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// define server addr to bind to
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to specified ip and port
	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	// listen for connections
	/**
	 * `listen` function marks the socket referred to by sockfd as a
	 * passive socket, that is, as a socket that will be used
	 * to accept incoming connection requests.
	 * 
	 * PARAMS:
	 * - `int sockfd` - socket file descriptor
	 * - `int backlog` - max length to which the queue of 
	 * pending connections for sockfd may grow. If a conn
	 * request arrives when the queue is full, the client may
	 * receive an error with an indication of ECONNREFUSED or,
	 * in the case the the underlying protocol supports 
	 * retransmission, the request may be ignored so a later
	 * reattempt at connection succeeds.
	 */
	listen(server_socket, 10);

	// store client socket
	client_socket = accept(server_socket, NULL, NULL);

	// send message
	/**
	 * `send` function is used to transmit a message
	 * to another socket.
	 * 
	 * PARAMS: 
	 * - `int sockfd` - socket file descriptor
	 * - `void *buf` - pointer to buffer for response
	 * - `size_t len` - size of buffer for response
	 * - `int flags` - Flags
	 */
	send(client_socket, server_msg, sizeof(server_msg), 0);

	// close the socket
	close(server_socket);

	return 0;
}
