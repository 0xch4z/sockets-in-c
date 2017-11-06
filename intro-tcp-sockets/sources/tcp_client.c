#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(const int argc, const char **argv) {

	// create a socket
	int network_socket;
	/**
	 * `socket` function creates an endpoint for communication and
	 * returns a file descriptor that refers to that endpoint. The
	 * file descriptor returned by a successful call will be the lowest
	 * numbered file descriptor not currently open for the process.
	 * 
	 * PARAMS:
	 * - `int domain`: specifies a communication domain
	 * - `int type`: specifies communication semantics
	 * - `int protocol`: specifies protocol to be used with socket
	 * 
	 * RETURNS `int fildes` - File descriptor
	 */
	// AF_INET -> constant for IPv4 communication domain
	// SOCK_STREAM -> constant for two-way connection based byte streams
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;
	// specify communication domain for IPv4
	server_address.sin_family = AF_INET;
	// specify port for connection
	// htons helper converts uint between host network byte order
	server_address.sin_port = htons(9002);
	// specify address for connection *localhost*
	// INADDR_ANY -> http://0.0.0.0
	server_address.sin_addr.s_addr = INADDR_ANY;

	/**
	 * `connect` function connects the socket referred to by the file
	 * descriptor `sockfd` to the address specified by `addr`. 
	 * 
	 * PARAMS:
	 * - `int sockfd` - File descriptor of the "client" socket
	 * - `struct sockaddr *addr` - The address of the "server" socket
	 * - `int addrlen` - Length of the address
	 * 
	 * RETURNS `int filedes` - File descriptor
	 */ 
	// must cast server_address to `const struct sockaddr *addr`
	int conn_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	if (conn_status == -1) {
		printf("There was an error connecting to the socket");
	}

	char server_response[256];
	// recieve data from the server
	/**
	 * `recv` function is used to recieve messages from a socket.
	 * 
	 * PARAMS:
	 * - `int sockfd` - File descriptor of "client" socket
	 * - `char buf` - Address of buffer for response/message
	 * - `int len` - Size of response buffer
	 * - `int flags` - Flags
	 */
	recv(network_socket, &server_response, sizeof(server_response), 0);

	printf("response: %s", server_response);

	// close socket
	close(network_socket);

	return 0;
}

