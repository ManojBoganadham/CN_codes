#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

int main()
{
    // socket client
    int PORT = 3001;
    int sfd, valread;
    struct sockaddr_in address;
    char buffer[1024] = {0};

    // creating a socket endpoint
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // continuously trying to connect the client socket to server socket
    while (connect(sfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("connect");
        cout << "Failed, retrying in 5 seconds" << endl;
        sleep(5);
    }
    cout << "Connection established with the multi data server...\n";

    string s;
    cout<<"Enter the number of data server you want to access: ";
    char choice;
    cin>>choice;
    send(sfd, &choice, sizeof(choice), 0);
    // waiting to receive data from the multi data server
    recv(sfd, buffer, 1024, 0);
    cout <<"From the dataserver "<< choice << ": " << buffer << endl;
    close(sfd);

    return 0;
}