#include"functions.h"


void *client_handler(void* socket_desc)
{
    int socket=*(int*)socket_desc;
    while(1)
    {
        printf("Handling Client with socket number :- %d\n",socket);
        char* return_message=(char*)malloc(SIZE);
        char option_string[2];
        read(socket,option_string,2);
        int option=atoi(option_string);
        if(option==SIGN_UP_AS_USER || option==SIGN_UP_AS_ADMIN || option==SIGN_UP_AS_JOINT)
        {
            char username[SIZE];
            char password[SIZE];

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
            char username[SIZE];
            char password[SIZE];

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
        write(socket , return_message ,SIZE ); 




    }

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

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
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
	return 0; 


}

