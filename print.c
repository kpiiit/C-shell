
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#define MAX_BUFFER_SIZE 1024
int print_man_page(char* command) {
    
    //printf("%s",command);
    char *command_name = command;
    struct hostent *server;
    struct sockaddr_in server_addr;
    int sockfd, portno = 80;

    // DNS resolution
    server = gethostbyname("man.he.net");
    if (server == NULL) {
        fprintf(stderr, "Error: Could not resolve host\n");
        exit(1);
    }

    // Initialize socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
       
    }

    // Set up server address
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portno);
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting");
       
    }

    // Send GET request
    char request[MAX_BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);

    if (write(sockfd, request, strlen(request)) < 0) {
        perror("Error writing to socket");
       
    }

    // Read and print response
    char buffer[MAX_BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
        // You need to implement the printTextContent function to print the response.
        // printTextContent(buffer);
        fwrite(buffer, 1, bytes_read, stdout); // A simple way to print the response.
    }

    if (bytes_read < 0) {
        perror("Error reading from socket");
       
    }

    close(sockfd);

}
