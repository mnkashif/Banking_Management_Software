#include"functions.h"


void *client_handler(void* socket_desc)
{
    int socket=*(int*)socket_desc;
    char username[SIZE];
    char password[SIZE];
    while(1)
    {
        char* return_message=(char*)malloc(SIZE);
        char option_string[SIZE];

        read(socket,option_string,SIZE);
        int option=atoi(option_string);
        printf("option= %d\n",option);
        if(option==EXIT)
        {
            break;
        }
        if(option==SIGN_UP_AS_USER || option==SIGN_UP_AS_ADMIN || option==SIGN_UP_AS_JOINT)
        {

            read(socket,username,SIZE);
            read(socket,password,SIZE);
            int b=signup(option,username,password);


            if(b==-1)
            {
                return_message="Failure.";
            }
            else
            {
                return_message="Success.";

            }


        }
        else if(option==SIGN_IN_AS_USER || option==SIGN_IN_AS_ADMIN || option==SIGN_IN_AS_JOINT)
        {
            
            // printf("tp\n");
            read(socket,username,SIZE);
            read(socket,password,SIZE);
            int b=signin(option,username,password);


            if(b==-1)
            {
                return_message="Failure.";
            }
            else
            {
                return_message="Success.";

            }



        }
        else if(option==DEPOSIT)
        {
            char damt_string[SIZE];
            read(socket,damt_string,SIZE);
            int damt=atoi(damt_string);
            int b=deposit(username,damt);
            if(b==-1)
            {
                return_message="Some error occured while depositing.";
            }
            else{

                sprintf(return_message,"Successfully deposited %d to account",damt);
                // strcat(return_message,damt_string);
                // strcat(return_message,"to account...");
            }


        }
        else if(option==WITHDRAW)
        {
            char wamt_string[SIZE];
            read(socket,wamt_string,SIZE);
            int wamt=atoi(wamt_string);
            int b=withdraw(username,wamt);
            if(b==-1)
            {
                return_message="Some error occured while withdrawing.";
            }
            else{

                sprintf(return_message,"%d successfully withdrawn from account",wamt);

                // strcat(return_message,"successfully withdrawn from account...");
            }

            
        }
        else if(option==BALANCE)
        {
            int b=balance(username);
            
            if(b==-1)
            {
                return_message="User not signed in...";
            }
            else
            {
                sprintf(return_message,"%s %d.","Account balance is",b);
                // strcat(return_message,balance);
                // strcat(return_message,".");
            }

        }
        else if(option==PASSWORD)
        {
            char new_pass[SIZE];
            read(socket,new_pass,SIZE);
            printf("new pass = %s",new_pass);

            int b=change_password(username,new_pass);
            if(b==-1)
            {
                return_message="Some error occured while updating password.";
            }
            else
            {
                return_message="Password successfully changed.";
            }
           
            
        }
        else if(option==DETAILS)
        {
            return_message=get_user_details(username);

        }
        write(socket , return_message ,SIZE ); 




    }
    return 0;

}

int main()
{
    int server_fd,new_socket_sd,opt=1;
    struct sockaddr_in server, client;
    int addrlen=sizeof(server);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
		perror("Creating Socket failed..."); 
		exit(EXIT_FAILURE); 
	} 

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
                perror("setsockopt");
                exit(EXIT_FAILURE);
        }


    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT_NO);

    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server))<0) { 
		perror("Binding Socket failed..."); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) { 
		perror("Listening error..."); 
		exit(EXIT_FAILURE); 
	} 

    printf("Bank is open to clients !\n");

    while(1){
        if ((new_socket_sd = accept(server_fd, (struct sockaddr *)&server,(socklen_t*)&addrlen))<0) { 
            perror("Accepting Connection failed\n"); 
            exit(EXIT_FAILURE); 
        } 
        pthread_t thread_id;
        if(pthread_create(&thread_id,NULL,client_handler,(void*)&new_socket_sd)<0)
        {
            perror("Could not create thread to handle client\n");
            return 1;
        }
        printf("Handler assigned\n");
    }
    close(server_fd);
    close(new_socket_sd);
	return 0; 


}

