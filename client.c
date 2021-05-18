#include"functions.h"

void interface(int socket)
{
    int option=0;
    printf("Welcome! enter one of the following options to continue...\n");
    printf("1 : Sign Up\n");
    printf("2 : Sign In\n");
    scanf("%d",&option);
    while(option!=1 && option!=2)
    {
        printf("Select either 1 or 2 :- ");
        scanf("%d",&option);
        
    }
    int c=0;
    int h=0;

    if(option==1)
    {
        printf("How would you like to sign up?\n");
        printf("1 : User\n");
        printf("2 : Administrator\n");
        printf("3 : Joint Account User\n");
        scanf("%d",&option);
        while(option!=1 && option!=2 && option!=3)
        {
            printf("Select either 1 or 2 or 3:- ");
            scanf("%d",&option);
            
        }
        // printf("%d\n",option);

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
        // printf("%d\n",option);
        
        printf("How would you like to sign in?\n");
        printf("1 : User\n");
        printf("2 : Administrator\n");
        printf("3 : Joint Account User\n");
        scanf("%d",&option);
        while(option!=1 && option!=2 && option!=3)
        {
            printf("Select either 1 or 2 or 3:- ");
            scanf("%d",&option);
            
        }
        // printf("%d\n",option);

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
                // printf("%d\n",c);

                if(c==USER || c==JOINT_USER)
                {
                    printf("What can we help you with?\n");
                    printf("1 : Deposit\n");
                    printf("2 : Withdraw\n");
                    printf("3 : Check Balance\n");
                    printf("4 : Change Password\n");
                    printf("5 : View Details\n");
                    printf("6 : Sign Out\n");
                    scanf("%d",&option);
                     while(option!=1 && option!=2 && option!=3 && option!=4 && option!=5 && option!=6)
                    {
                        printf("Select either 1 or 2 or 3 or 4 or 5 or 6:- ");
                        scanf("%d",&option);
                        
                    }
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
                        sprintf(option_string,"%d",SIGN_OUT);
                        write(socket,option_string,SIZE);
                        return;
                        
                    }
                    
                }
        

        
            else if(c==ADMIN)
            {
                printf("1 : Add User\n");
                printf("2 : Delete User\n");
                printf("3 : Modify User\n");
                printf("4 : Search User Details\n");
                printf("5 : Sign Out\n");
                scanf("%d",&option);
                while(option!=1 && option!=2 && option!=3 && option!=4 && option!=5)
                {
                    printf("Select either 1 or 2 or 3 or 4 or 5 :- ");
                    scanf("%d",&option);
                    
                }
                char option_string[SIZE];
                if(option==1)
                {
                    sprintf(option_string,"%d",ADD_USER);
                    write(socket,option_string,SIZE);
                    int type;
                    char username[SIZE];
                    char password[SIZE];
                    printf("Enter User Account Type\n");
                    printf("1 : Normal\n");
                    printf("2 : Joint\n");
                    scanf("%d",&type);
                    while(type!=1 && type!=2)
                    {
                        printf("Select either 1 or 2 :- ");
                        scanf("%d",&type);
                        
                    }
                    printf("Enter username : ");
                    scanf("%s",username);
                    printf("Enter password : ");
                    scanf("%s",password);

                    if(type==1)
                    {
                        char type_string[SIZE];
                        sprintf(type_string,"%d",SIGN_UP_AS_USER);
                        write(socket,type_string,SIZE);
                    }
                    else if(type==2)
                    {
                        char type_string[SIZE];
                        sprintf(type_string,"%d",SIGN_UP_AS_JOINT);
                        write(socket,type_string,SIZE);
                    }
                    write(socket,username,SIZE);
                    write(socket,password,SIZE);


                    

                }
                else if(option==2)
                {
                    sprintf(option_string,"%d",DELETE_USER);
                    write(socket,option_string,SIZE);
                    char username[SIZE];
                    printf("Enter username to be deleted : ");
                    scanf("%s",username);
                    write(socket,username,SIZE);





                }
                else if(option==3)
                {
                    sprintf(option_string,"%d",MODIFY_USER);
                    write(socket,option_string,SIZE);

                    char old_username[SIZE];
                    char new_username[SIZE];

                    char password[SIZE];
                    
                    printf("Enter username to be modified : ");
                    scanf("%s",old_username);
                     printf("Enter new username : ");
                    scanf("%s",new_username);
                    printf("Enter new password : ");
                    scanf("%s",password);

            
                    write(socket,old_username,SIZE);
                    write(socket,new_username,SIZE);

                    write(socket,password,SIZE);

                            
                }

                else if(option==4)
                {
                    sprintf(option_string,"%d",GET_USER_DETAILS);
                    write(socket,option_string,SIZE);
                    char username[SIZE];

                    printf("Enter username to get details : ");
                    scanf("%s",username);
                    printf("%s\n",username);

                    write(socket , username , SIZE); 

                    
                }
                else if(option==5)
                {
                    sprintf(option_string,"%d",SIGN_OUT);
                    write(socket,option_string,SIZE);
                    return;
                    
                }


            }
            char return_message[SIZE];
            read(socket , return_message, SIZE); 
            printf("%s\n\n",return_message);
        }
    }
    else
    {
        char option_string[SIZE];
        printf("Sign In/Sign Up not successful\n");
        sprintf(option_string,"%d",EXIT);
        write(socket,option_string,SIZE);
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