#ifndef PROTOCOL_H // Check if PROTOCOL_H is not defined
#define PROTOCOL_H // Define PROTOCOL_H to prevent redefinition

// Default IP address for the server (localhost)
#define DEFAULT_IP "127.0.0.1"

// Default port number the server will listen on
#define DEFAULT_PORT 8080

// Maximum length allowed for a generated password
#define MAX_PASSWORD_LENGTH 32

// Minimum length required for a valid password
#define MIN_PASSWORD_LENGTH 6

// Buffer size used for communication between client and server
#define BUFFER_SIZE 128

#endif // PROTOCOL_H
