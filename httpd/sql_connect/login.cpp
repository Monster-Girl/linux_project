/*************************************************************************
	> File Name: login.cpp
	> Author: monster
	> Mail: 1104306242@qq.com 
	> Created Time: Tue 22 Aug 2017 05:01:02 PM CST
 ************************************************************************/

#include"sql_agi.h"

using namespace std;

void login(const char *string_arg)
{
	char arg_buf[1024];
	char *argv_buf[3];
	strcpy(arg_buf,string_arg);
	int i=0;
	char *start=arg_buf;
	while(*start)
	{
		if(*start=='=')
		{
			start++;
			argv_buf[i++]=start;
			continue;
		}
		if(*start=='&')
			*start=0;
		start++;
	}
	argv_buf[i]=0;
	sqlAgi db;
	db.myConnect();
	db.Login(argv_buf[0],argv_buf[1]);
}

int main()
{
	char *method=NULL;
	char *query_string=NULL;
	char *string_arg=NULL;
	int content_len=-1;
	char buf[1024];

	if((method=getenv("METHOD")))
	{
		if(strcasecmp(method,"GET")==0)
		{
			if((query_string=getenv("QUERY_STRING")))
			{
				string_arg=query_string;
			}
		}
		else
		{
			if(getenv("CONTENT_LEN"))
			{
				content_len=atoi(getenv("CONTENT_LEN"));
				int i=0;
				for(;i<content_len;i++)
					read(0,&buf[i],1);
				buf[i]=0;
				string_arg=buf;
			}
		}
	//	login(string_arg);
	}


	sqlAgi mydb;
	mydb.myConnect();
	mydb.Login("pete","123456");
	return 0;
}
