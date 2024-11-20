# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g3
OUTPUT_DIR = output

# Source files
SERVER_SRCS = server.c password_utils.c
CLIENT_SRCS = client.c
UTILS_SRCS = password_utils.c

# Object files
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

# Targets
all: $(OUTPUT_DIR) server client

# Create the output directory
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Build the server executable
server: $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(OUTPUT_DIR)/server

# Build the client executable
client: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(OUTPUT_DIR)/client

# Compile object files for .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f *.o
	rm -rf $(OUTPUT_DIR)

