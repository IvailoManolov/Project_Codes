#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){
    //Vars.
    int check_correct = 1;
    int check_if_correct = 1;
    int network_status;
    int network_socket;
    char buffer[256];
    char name[30];
    char client_name[30];
    char quit[10] = "EXIT";

    //Check to see if the name is legal.
    while(check_correct){
        printf("Please enter your name (30Characters max): ");
        scanf("%[^\n]%*c",name);
            if(strlen(name) < 30) {
                check_correct = 0;
            }
    }
    //Creating a socket:
    network_socket = socket (AF_INET, SOCK_STREAM ,0);

    //Specifying address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //Making the connection
    network_status = connect (network_socket,(struct sockaddr_in*)&server_address,sizeof(server_address));

    //Checking if connection is legal . 
        if(network_status < 0)
         {
             puts("Couldn't establish connection");
             exit(1);
         }
    //If connection is legal , we have found a clinet. Receiving name and sending your own 
    printf("We have found a client and we are receiving his name : ");
    recv(network_socket,&client_name,sizeof(client_name),0);
    printf("Sending your name to %s \n",client_name);
    send(network_socket,name,sizeof(name),0);
    puts("If you wish to quit the chat room , please type  ' EXIT ' \n ");\
    //Chat Loop 
        while(1){
	    time_t t;
            time(&t);
            puts("Waiting for Data : ");
            recv(network_socket,&buffer,sizeof(buffer),0);
            printf("%s says :%s(%s) \n",client_name,buffer,ctime(&t));
            puts("What would you wish to say  ? ");
            //Check if your message is legal.
                while(check_if_correct)
                {
		    scanf("%[^\n]%*c",&buffer);
                        //If message legal and is EXIT we exit the loop
                    if(strlen(buffer) < 256 && strcmp(buffer,quit)==0){
                        printf("You have exited the chat\n ");
                        exit(1);
                    }
                    //If your message is more of the eligitimate range , type again something smaller.
                    if(strlen(buffer) > 256 ){
                        printf("Your message exceeded 256 characters , try typing again ");
                     }
                     //If everything is fine  Exit LOOP and send message.
                     else {
                         break;
                     }
                }
                //Sending your data
            send(network_socket,buffer,sizeof(buffer),0);

        }
        //Closing the network Socket .
    close(network_socket);


    return 0;
}
