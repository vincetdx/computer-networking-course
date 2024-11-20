#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     // POSIX API for system calls
#include <arpa/inet.h>  // Functions for socket programming
#include "protocol.h"   

/*
 * Main function for the TCP client
 * - Connects to a server
 * - Sends requests for password generation
 * - Receives and displays the generated password
 */
int main() {
    // Create a socket for communication (IPv4, TCP, default protocol)
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // Define the server's address and port
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;                   // IPv4
    server_addr.sin_port = htons(DEFAULT_PORT);         // Port (converted to network byte order)
    inet_pton(AF_INET, DEFAULT_IP, &server_addr.sin_addr); // Convert IP to binary format

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to the server failed");
        close(client_socket);
        return EXIT_FAILURE;
    }
    printf("Connected to the server at %s:%d\n", DEFAULT_IP, DEFAULT_PORT);

    char buffer[BUFFER_SIZE]; // Buffer for sending and receiving data

    // Main loop for communication with the server
    while (1) {
        // Prompt the user for input
        printf("Enter password type and length (e.g., n 8) or 'q' to quit: ");
        fgets(buffer, BUFFER_SIZE, stdin);               // Read input from the user
        buffer[strcspn(buffer, "\n")] = '\0';            // Remove the trailing newline character

        // Send the input to the server
        send(client_socket, buffer, strlen(buffer), 0);

        // If the user enters 'q', exit the loop and close the connection
        if (buffer[0] == 'q') break;

        // Clear the buffer and wait for the server's response
        memset(buffer, 0, BUFFER_SIZE);
        read(client_socket, buffer, BUFFER_SIZE);

        // Display the generated password
        printf("Generated password: %s\n", buffer);
    }

    // Close the socket connection and exit
    close(client_socket);
    return 0;
}
