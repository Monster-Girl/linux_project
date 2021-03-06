#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/sendfile.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#define SIZE 1024
#define SUCCESS 0
#define NOTICE 1
#define WARNING 2
#define ERROR 3
#define FATAL 4
int startup(const char* port,int ip);
void print_log(char *msg,int level);
static int get_line(int sock,char line[],int size);
static void echo_string(int sock);
static void drop_header(int sock);
void *handler_request(void* arg);
static int exe_cgi(int sock,const char *method,const char *path,const char *query_string);
