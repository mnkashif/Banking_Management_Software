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



#define USER 4
#define ADMIN 5
#define JOINT_USER 6

#define SIGN_IN_AS_USER 7  
#define SIGN_IN_AS_ADMIN 8
#define SIGN_IN_AS_JOINT 9

#define DEPOSIT 10
#define WITHDRAW 11
#define BALANCE 12
#define PASSWORD 13
#define DETAILS 14
#define SIGN_OUT 15
#define EXIT 20

#define ADD_USER 16
#define DELETE_USER 17
#define MODIFY_USER 18
#define GET_USER_DETAILS 19

#define SIZE 100

struct user{
    char username[SIZE];
    char password[SIZE];
    int type;
    int active;

};

struct account{

    int balance;

};

int signup(int option,int maker, char username[], char password[]);
int get_details_from_user(int sock, int option);
int signin(int option, char username[], char password[]);
int deposit(char username[], int amount);
int withdraw(char username[], int amount);
int balance(char username[]);
int change_password(char username[], char pwd[]);
char* get_user_details(char username[]);
int delete_user(char username[]);
int modify_user(char old_username[], char new_username[], char new_password[]);
void signout(char username[]);