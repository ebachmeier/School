#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "udp_sockets.h"
#include "udp_server.h"

int main()
{
  int bytes_read;                   // Number of bytes read
  char buffer[65535];               // Buffer to store incoming message
  char ip_address[INET_ADDRSTRLEN]; // Buffer to store human-readable source IP address
  struct sockaddr_in addr;          // Source address and port
  socklen_t addr_len = sizeof(struct sockaddr_in); // Length of the addr structure

  // Create a socket to listen on port 5000
  int sockfd = create_server_socket("5000");

  // Read the next message into buffer, storing the source address in addr
  bytes_read = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);

  // Convert the source address to a human-readable IP address
  inet_ntop(addr.sin_family, &addr.sin_addr, ip_address, sizeof(ip_address));

  if (bytes_read > 0)
  {
    // Add NULL terminator
    buffer[bytes_read] = '\0';

    printf("Message received from %s: %s\n", ip_address, buffer);
  }

  // Close the socket
  close(sockfd);

  exit(EXIT_SUCCESS);
}
