#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    char name[30];
    char quit[10] = "EXIT";
    char client_name[30];
    char buffer[256];
    int server_socket;
    int client_socket;
    int check_correct = 1; 
    int check_if_correct = 1;
    
    //Creating a socket.
    server_socket = socket(AF_INET,SOCK_STREAM,0);

    //Specifying an address.
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;   

    //Bounding the socket.
    bind (server_socket,(struct sockaddr_in*)&server_address,sizeof(server_address));

    //Listening for clients .
    listen(server_socket,5);
    
    //Storing client information for further use .
    client_socket = accept (server_socket,NULL,NULL);

        //Checking if there is a connection . 
        if(client_socket < 0 ){
            printf("No descriptor of the accepted socket found ");
            exit(1);
        }
        //If there is a positive integer ( descriptor of the accepted socket ) proceed further .
            while(check_correct)
            { 
                printf("Found a client , Choose a name (30 Characters max) : ");
                scanf("%[^\n]%*c",&name);
                    if(strlen(name)  < 30 ) {
                        check_correct = 0;
                    }
                    else{
                        printf("Name is out of the selected border , Please try again ");
                        check_correct = 1 ;
                    }
            }
            //Sending your name and receiving theirs 
        puts("Sending the client your name ");
        send(client_socket,name,sizeof(name),0);
        recv(client_socket,&client_name,sizeof(client_name),0);
        printf("Connected with %s \n ",client_name);
        //Check to see if message is legal 
            while(1){
		time_t t;
                time(&t);
                printf("What would you like to send to %s \n",client_name);
                    while(check_if_correct){
			scanf("%[^\n]%*c",buffer);
                        if(strlen(buffer) < 256 && strcmp(buffer,quit)==0){
                            printf("Exiting the chat Loop");
                            exit(1);
                        }
                        if (strlen(buffer) > 256){
                            printf("Message illegal (Out of border), Please try again ");
                  
                        }
                        else {
                            break;
                        }
                    }
                    //Test passed , sending the message and receiving 
                send(client_socket,buffer,sizeof(buffer),0);
                printf("Waiting for data : \n");
                recv(client_socket,&buffer,sizeof(buffer),0);
                printf("%s says %s(%s) \n",client_name,buffer,ctime(&t));

            }
    //Closing the socket : 
    printf("Closing the socket : ");
    close(server_socket);
    return 0;
}
