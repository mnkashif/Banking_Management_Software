#include"functions.h"


int signup(int option, char username[], char password[])
{

    char filename[SIZE];
    strcpy(filename,username);

    char extension[] = ".txt";
    
    int fd;
    strcat(filename,extension);


    fd = open(filename,O_WRONLY);
    if(fd != -1) return -1;
    close(fd);
    fd = open(filename,O_WRONLY | O_CREAT,0644);
    if(fd == -1){
        return -1;
    }
    struct user u;
    strcpy(u.username,username);
    strcpy(u.password,password);
    if(option==SIGN_UP_AS_USER )
    {
        u.type=USER;

    }
    else if(option == SIGN_UP_AS_JOINT)
    {
        u.type=JOINT_USER;

    }
    else if( option == SIGN_UP_AS_ADMIN)
    {
        u.type=ADMIN;

    }

    
    write(fd,&u,sizeof(struct user));
    struct account acc;
    acc.balance = 0;
    write(fd,&acc,sizeof(struct account));
    close(fd);
    return 0;


}


void get_details_from_user(int socket, int option){
	char username[SIZE];
	char password[SIZE];
	char return_message[SIZE];
	char option_string[SIZE];
	printf("Enter username : ");
	scanf("%s",username);
	printf("Enter password : ");
	scanf("%s",password);
	sprintf(option_string,"%d",option);
	write(socket , option_string , 2); 
	write(socket , username , SIZE); 
	write(socket , password , SIZE); 
	read(socket , return_message,SIZE); 
	printf("%s\n\n",return_message); 
	if(!strcmp(return_message,"Success.")) exit(1);
	
}

int signin(int option, char username[], char password[]){
    static struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = sizeof(struct user);
    lock.l_pid = getpid();

    char filename[SIZE];
    strcpy(filename,username);
    char extension[] = ".txt";
    int fd;
    strcat(filename,extension);
    fd = open(filename,O_RDONLY,0644);
    if(fd == -1){
        perror("User does not exist"); return -1;
    }
    struct user u;
    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl") ; return -1;}
    lseek(fd,0,SEEK_SET);
    read(fd,&u,sizeof(struct user));
    if((strcmp(u.password,password)!=0) || (option==SIGN_IN_AS_USER && (u.type!=USER)) || (option==SIGN_IN_AS_ADMIN && (u.type!=ADMIN)) || (option==SIGN_IN_AS_JOINT && (u.type!=JOINT_USER))) return -1;
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);
    return 0;
}