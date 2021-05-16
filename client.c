#include"functions.h"

void interface(int socket)
{
    int option;
    printf("Welcome! enter one of the following options to continue...\n");
    printf("1 : Sign Up\n");
    printf("2 : Sign In\n");
    scanf("%d",&option);
    printf("%d\n",option);
    if(option==1)
    {
        printf("How would you like to sign up?\n");
        printf("1 : User\n");
        printf("2 : Administrator\n");
        printf("3 : Joint Account User\n");
        scanf("%d",&option);
        if(option==1)
            get_details_from_user(socket,SIGN_UP_AS_USER);
        else if(option==2)
            get_details_from_user(socket,SIGN_UP_AS_ADMIN);
        else if(option==3)
            get_details_from_user(socket,SIGN_UP_AS_JOINT);

        if(option==1 || option==3)
        {
            

        }
        else if(option == 2)
        {



        }
        
        
        
    }
    else if(option==2)
    {
        printf("How would you like to sign in?\n");
        printf("1 : User\n");
        printf("2 : Administrator\n");
        printf("3 : Joint Account User\n");
        scanf("%d",&option);
        if(option==1)
            get_details_from_user(socket,SIGN_IN_AS_USER);
        else if(option==2)
            get_details_from_user(socket,SIGN_IN_AS_ADMIN);
        else if(option==3)
            get_details_from_user(socket,SIGN_IN_AS_JOINT);


    }

}




int main()
{

    int client_socket_sd;
    struct sockaddr_in server;
    int addrlen=sizeof(server);
    

    if ((client_socket_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("Creating Socket failed...\n"); 
		return -1; 
	} 

	server.sin_family = AF_INET; 
	server.sin_port = htons(PORT_NO); 
    // server.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr)<=0) 
	{ 
		printf("Invalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(client_socket_sd, (struct sockaddr *)&server, sizeof(server)) < 0) 
	{ 
		printf("Connection to Server Failed \n"); 
		return -1; 
	} 
	interface(client_socket_sd);


	return 0; 














}