#include <stdio.h>       
#include <stdlib.h>      
#include <string.h>      
#include <unistd.h>      // POSIX API for system calls
#include <arpa/inet.h>   
#include <time.h>        
#include "protocol.h"    
#include "password_utils.h" 

/*
 * Function to handle communication with a single client
 * - Reads password requests
 * - Validates input
 * - Generates passwords based on the request
 * - Sends the generated password or an error message back to the client
 */
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE]; // Buffer for receiving client data
    while (1) {
        // Clear the buffer and read the client's request
        memset(buffer, 0, BUFFER_SIZE);
        read(client_socket, buffer, BUFFER_SIZE);

        // If the client requests to disconnect, break the loop
        if (buffer[0] == 'q') {
            printf("Client disconnected.\n");
            break;
        }

        // Parse the request: first character is the type, the rest is the length
        char type = buffer[0];
        int length = atoi(buffer + 2);

        // Validate the password length
        if (length < MIN_PASSWORD_LENGTH || length > MAX_PASSWORD_LENGTH) {
            const char *error = "Error: Invalid length.\n";
            send(client_socket, error, strlen(error), 0);
            continue; // Skip to the next iteration
        }

        // Generate the password based on the type
        char password[MAX_PASSWORD_LENGTH + 1];
        switch (type) {
            case 'n': generate_numeric(password, length); break;  // Numeric password
            case 'a': generate_alpha(password, length); break;    // Alphabetic password
            case 'm': generate_mixed(password, length); break;    // Mixed password
            case 's': generate_secure(password, length); break;   // Secure password
            default:
                // Handle invalid type
                send(client_socket, "Error: Invalid type.\n", 21, 0);
                continue;
        }

        // Send the generated password back to the client
        send(client_socket, password, strlen(password), 0);
    }

    // Close the client socket after communication ends
    close(client_socket);
}

/*
 * Main function for the TCP server
 * - Sets up the server socket
 * - Listens for incoming client connections
 * - Handles each client connection in a child process
 */
int main() {
    srand(time(NULL)); // Seed the random number generator

    // Create a socket for communication (IPv4, TCP, default protocol)
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // Define the server's address and port
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;              // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;      // Accept connections on any interface
    server_addr.sin_port = htons(DEFAULT_PORT);    // Port (converted to network byte order)

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        return EXIT_FAILURE;
    }

    // Start listening for incoming connections (max 5 clients in queue)
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d...\n", DEFAULT_PORT);

    // Main loop to accept and handle client connections
    while (1) {
        struct sockaddr_in client_addr; // Structure to hold client address info
        socklen_t client_len = sizeof(client_addr);

        // Accept a new client connection
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Display the client's IP and port
        printf("New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Create a child process to handle the client
        if (!fork()) {
            // Child process: close the listening socket and handle the client
            close(server_socket);
            handle_client(client_socket);
            exit(0); // Exit the child process when done
        }

        // Parent process: close the client socket and continue accepting new clients
        close(client_socket);
    }

    // Close the server socket (not reached due to infinite loop)
    close(server_socket);
    return 0;
}
