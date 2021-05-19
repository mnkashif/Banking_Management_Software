#include"functions.h"


int signup(int option,int maker, char username[], char password[])
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
    if(maker!=SIGN_IN_AS_ADMIN && maker!=SIGN_UP_AS_ADMIN)
    {
        u.active=1;
    }
    else
    {
        u.active=0;
    }
    write(fd,&u,sizeof(struct user));
    struct account acc;
    acc.balance = 0;
    write(fd,&acc,sizeof(struct account));
    close(fd);
    return 0;


}


int  get_details_from_user(int socket, int option){
	char username[SIZE];
	char password[SIZE];
	char return_message[SIZE];
	char option_string[SIZE];
	printf("Enter username : ");
	scanf("%s",username);
	printf("Enter password : ");
	scanf("%s",password);
	sprintf(option_string,"%d",option);
	write(socket , option_string , SIZE); 
	write(socket , username , SIZE); 
	write(socket , password , SIZE); 
	read(socket , return_message,SIZE); 
	printf("%s\n\n",return_message); 
	if(strcmp(return_message,"Success.")) return 0;
    return 1;
	
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
   
    fd = open(filename,O_RDWR,0644);
    if(fd == -1){
        perror("User does not exist"); return -1;
    }
    struct user u;

    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl") ; return -1;}
    lseek(fd,0,SEEK_SET);
    read(fd,&u,sizeof(struct user));
    if(u.active==1 && (u.type==USER || u.type==ADMIN))
    {
        lock.l_type = F_UNLCK;
        fcntl(fd,F_SETLKW,&lock);
        close(fd);
        return -1;
    }
    printf("username : %s \npassword : %s \nbalance : %d\nActive : %d\n", u.username,u.password,u.type,u.active);
    u.active=1;
    printf("username : %s \npassword : %s \nbalance : %d\nActive : %d\n", u.username,u.password,u.type,u.active);

    lseek(fd,0,SEEK_SET);
    write(fd,&u,sizeof(struct user));
    if((strcmp(u.password,password)!=0) || (option==SIGN_IN_AS_USER && (u.type!=USER)) || (option==SIGN_IN_AS_ADMIN && (u.type!=ADMIN)) || (option==SIGN_IN_AS_JOINT && (u.type!=JOINT_USER))) return -1;
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);

    return 0;
}

int deposit(char username[], int amount){
    static struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = sizeof(struct user);
    lock.l_whence = SEEK_SET;
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();
    
    char filename[SIZE];
    strcpy(filename,username);
    char extension[] = ".txt";
    int fd;
    strcat(filename,extension);
    fd = open(filename,O_RDWR,0644);
    if(fd == -1){
        perror("User not signed in..."); return -1;
    }

    struct account acc;
    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl") ; return -1;}

    lseek(fd,sizeof(struct user),SEEK_SET);
    if(read(fd,&acc,sizeof(struct account))==-1) {perror("read"); return -1;}
    acc.balance += amount;
    lseek(fd,sizeof(struct user),SEEK_SET);
    if(write(fd,&acc,sizeof(struct account))==-1) {perror("write"); return -1;}
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);
    // printf("%s\n",get_user_details(username));
    return 0;
}


int withdraw(char username[], int amount){
    static struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = sizeof(struct user);
    lock.l_whence = SEEK_SET;
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    char filename[SIZE];
    strcpy(filename,username);
    char extension[] = ".txt";
    int fd;
    strcat(filename,extension);
    fd = open(filename,O_RDWR,0644);
    if(fd == -1){
        perror("User not Signed in ..."); return -1;
    }
    struct account acc;
    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl") ; return -1;}

    lseek(fd,sizeof(struct user),SEEK_SET);
    if(read(fd,&acc,sizeof(struct account)) == -1) {perror("read"); return -1;}
    // printf("balance = %d\n",acc.balance);
    acc.balance -= amount;
    if(acc.balance < 0) return -1;
    lseek(fd,sizeof(struct user),SEEK_SET);
    if(write(fd,&acc,sizeof(struct account))==-1) {perror("write"); return -1;}
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);
    return 0;
}

int balance(char username[]){
    static struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_start = sizeof(struct user);
    lock.l_whence = SEEK_SET;
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    char filename[SIZE];
    strcpy(filename,username);
    char extension[] = ".txt";
    int fd;
    strcat(filename,extension);
    fd = open(filename,O_RDONLY,0644);
    if(fd == -1){
        perror("User not Signed in ..."); return -1;
    }
    struct account acc;
    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl") ; return -1;}
    // start of critical section
    lseek(fd,sizeof(struct user),SEEK_SET);
    if(read(fd,&acc,sizeof(struct account))==-1) perror("read");
    // end of critical section
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);
    return acc.balance;
}

int change_password(char username[], char pwd[]){
    static struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = sizeof(struct user);
    lock.l_pid = getpid();

    char filename[SIZE];
    strcpy(filename,username);
    char extension[] = ".txt";
    int fd;
    strcat(filename,extension);
    fd = open(filename,O_RDWR,0644);
    if(fd == -1){
        perror("change pwd"); return -1;
    }
    struct user u;
    lseek(fd,0,SEEK_SET);
    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl") ; return -1;}
    if(read(fd,&u,sizeof(struct user))==-1) { perror("read"); return -1; }
    strcpy(u.password,pwd);
    // printf("User %s",u.password);

    lseek(fd,0,SEEK_SET);
    if(write(fd,&u,sizeof(struct user))==-1) { perror("write"); return -1; }
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);
    return 0;
}

char* get_user_details(char username[]){
    static struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_pid = getpid();

    char filename[SIZE];
    strcpy(filename,username);
    char extension[] = ".txt";
    int fd;
    strcat(filename,extension);

    fd = open(filename,O_RDWR,0644);
    if(fd == -1){
        perror("open"); 
        return "User does not exist\n";
    }
    struct account acc;
    struct user u;
    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl"); return "sorry, account is currently locked\n";}
    // start of critical section
    lseek(fd,0,SEEK_SET);
    if(read(fd,&u,sizeof(struct user))==-1)
        {perror("read"); return "Unable to read account details\n";}
    if(read(fd,&acc,sizeof(struct account))==-1)
        {perror("read"); return "Unable to read account details\n";}
    // end of critical section
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);
    char* return_string=(char*)malloc(SIZE);
    char type[SIZE];
    if(u.type==USER)
    {
        sprintf(type,"%s","normal user");
    }
    else if(u.type==JOINT_USER)
    {
        sprintf(type,"%s","joint user");
    }
    else if(u.type==ADMIN)
    {
        sprintf(type,"%s","admin");
    }
    sprintf(return_string,"username : %s \npassword : %s \ntype : %s\nbalance : %d\nActive : %d\n",
    u.username,u.password,type,acc.balance,u.active);
    close(fd);
    return return_string;
}


int delete_user(char username[])
{       
    static struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_pid = getpid();

    char filename[SIZE];
    strcpy(filename,username);
    char extension[] = ".txt";
    strcat(filename,extension);
    int fd = open(filename,O_RDWR,0644);
    if(fd == -1){ perror("open");}
    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl");}

    return unlink(filename);

}

int modify_user(char old_username[], char new_username[], char new_password[])
{

    static struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_pid = getpid();
    char filename[SIZE];
    strcpy(filename,old_username);
    char extension[] = ".txt";
    int fd,option;
    strcat(filename,extension);
    fd = open(filename,O_RDWR,0644);
    if(fd == -1){
        perror("mod user"); return -1;
    }
    struct user u;
    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl");}
    lseek(fd,0,SEEK_SET);
    if(read(fd,&u,sizeof(struct user))==-1) { perror("read"); return -1; }
    int b=delete_user(old_username);
    if(b==-1)
        return -1;
    if(u.type==USER) option = SIGN_UP_AS_USER;
    else option = SIGN_UP_AS_JOINT;
    strcpy(u.username,new_username);
    b=signup(option,SIGN_UP_AS_ADMIN,new_username,new_password);
    if(b==-1)   
        return -1;
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);
    return 0;



}

void signout(char username[])
{
    static struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_pid = getpid();
    char filename[SIZE];
    strcpy(filename,username);
    char extension[] = ".txt";
    int fd,option;
    strcat(filename,extension);
    fd = open(filename,O_RDWR,0644);
    
    struct user u;
    if(fcntl(fd, F_SETLKW, &lock)==-1) {perror("fcntl");}
    lseek(fd,0,SEEK_SET);
    read(fd,&u,sizeof(struct user));

    u.active=0;
    lseek(fd,0,SEEK_SET);
    write(fd,&u,sizeof(struct user));
    
    lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);


}
