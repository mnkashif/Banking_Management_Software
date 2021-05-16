#include<stdio.h>
#include<unistd.h> 
#include<sys/socket.h> 
#include<stdlib.h> 
#include<netinet/in.h> 
#include <arpa/inet.h>
#include<string.h> 
#include<pthread.h>
#include<fcntl.h>

#define PORT_NO  5000

#define SIGN_UP_AS_USER 1   
#define SIGN_UP_AS_ADMIN 2
#define SIGN_UP_AS_JOINT 3



#define USER 3
#define ADMIN 4
#define JOINT_USER 5

#define SIGN_IN_AS_USER 6  
#define SIGN_IN_AS_ADMIN 7
#define SIGN_IN_AS_JOINT 8

#define SIZE 100

struct user{
    char username[SIZE];
    char password[SIZE];
    int type;

};

struct account{

    int balance;

};

int signup(int option, char username[], char password[]);
void get_details_from_user(int sock, int option);
int signin(int option, char username[], char password[]);