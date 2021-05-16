#include"functions.h"

void interface(int socket)
{
    int option;
    printf("Welcome! enter one of the following options to continue...\n");
    printf("1 : Sign Up\n");
    printf("2 : Sign In\n");
    scanf("%d",&option);
    int c=0;
    int h=1;

    if(option==1)
    {
        printf("How would you like to sign up?\n");
        printf("1 : User\n");
        printf("2 : Administrator\n");
        printf("3 : Joint Account User\n");
        scanf("%d",&option);
        if(option==1)
        {
            h=get_details_from_user(socket,SIGN_UP_AS_USER);
            c=USER;
        }
        else if(option==2)
        {
            h=get_details_from_user(socket,SIGN_UP_AS_ADMIN);
            c=ADMIN;
        }
        else if(option==3)
        {
            h=get_details_from_user(socket,SIGN_UP_AS_JOINT);
            c=JOINT_USER;
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
        {
            h=get_details_from_user(socket,SIGN_IN_AS_USER);
            c=USER;
        }
        else if(option==2)
        {
            h=get_details_from_user(socket,SIGN_IN_AS_ADMIN);
            c=ADMIN;
        }
        else if(option==3)
        {
            h=get_details_from_user(socket,SIGN_IN_AS_JOINT);
            c=JOINT_USER;
        }

    }
    if(h)
    {
        while(1)
        {

                if(c==USER || c==JOINT_USER)
                {
                    printf("What can we help you with?\n");
                    printf("1 : Deposit\n");
                    printf("2 : Withdraw\n");
                    printf("3 : Check Balance\n");
                    printf("4 : Change Password\n");
                    printf("5 : View Details\n");
                    printf("6 : Exit\n");
                    scanf("%d",&option);
                    char option_string[SIZE];
                    if(option==1)
                    {
                        sprintf(option_string,"%d",DEPOSIT);
                        write(socket,option_string,SIZE);
                        int damt;
                        char damt_string[SIZE];
                        printf("Enter amount to be deposited : ");
                        scanf("%d",&damt);
                        sprintf(damt_string,"%d",damt);	
                        write(socket, damt_string, SIZE);
                        

                    }
                    else if(option==2)
                    {
                        sprintf(option_string,"%d",WITHDRAW);
                        write(socket,option_string,SIZE);
                        int wamt;
                        char wamt_string[SIZE];
                        printf("Enter amount to be withdrawn : ");
                        scanf("%d",&wamt);
                        sprintf(wamt_string,"%d",wamt);	
                        write(socket, wamt_string, SIZE);
                        

                    }
                    else if(option==3)
                    {
                        sprintf(option_string,"%d",BALANCE);
                        write(socket,option_string,SIZE);
                                
                    }

                    else if(option==4)
                    {
                        sprintf(option_string,"%d",PASSWORD);
                        write(socket,option_string,SIZE);
                        // printf("Enter old password\n");
                        char old_pass[SIZE],new_pass[SIZE];
                        // scanf("%s",old_pass);
                        printf("Enter new password:-");
                        scanf("%s",new_pass);
                        printf("%s",new_pass);
                        // write(socket, old_pass, SIZE);
                        write(socket, new_pass, SIZE);

                        
                    }
                    else if(option==5)
                    {
                        sprintf(option_string,"%d",DETAILS);
                        write(socket,option_string,SIZE);
                        
                    }
                    else if(option==6)
                    {
                        sprintf(option_string,"%d",EXIT);
                        write(socket,option_string,SIZE);
                        return;
                        
                    }
                    char return_message[SIZE];
                    read(socket , return_message, SIZE); 
                    printf("%s\n\n",return_message);
                }
        

        
            else if(c==ADMIN)
            {



            }
        }
    }
    else
    {
        printf("Sign In/Sign Up not successful\n");
        return;
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