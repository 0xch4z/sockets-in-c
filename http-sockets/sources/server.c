#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(const int argc, const char **argv) {
    
    // create html file ref
    FILE *html_data;
    html_data = fopen("index.html", "r");
    
    // read html to response_data
    char response_data[1024];
    fgets(response_data, 1024, html_data);
    printf("html: %s", response_data);
    
    // close file
    fclose(html_data);
    
    // write response header
    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    printf("header: %s", http_header);
    // add body to header for easy response
    strcat(http_header, response_data);
    
    // create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    
    listen(server_socket, 10);
    
    printf("Server started on port 8080...");
    printf("curl localhost:8080");
    
    int client_socket;
    
    // keep handling client
    while (1) {
        // get client socket
        client_socket = accept(server_socket, NULL, NULL);
        // send payload
        send(client_socket, http_header, sizeof(http_header), 0);
        // drop client socket
        close(client_socket);
    }
    
    return 0;
}
