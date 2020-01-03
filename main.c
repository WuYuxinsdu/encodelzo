#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 10000

int main()
{
    int i=0,r;
    //printf("%d",sizeof(int));
    char imode[1]={0},omode[1]={0};       //存放键入的模式
    char original[MAX_LENGTH]={0};
    char decoded[MAX_LENGTH]={0};
    char cipher[MAX_LENGTH]="";
	printf("Please input your Message:\n");
	gets(original);                //源字符串
	printf("len is %d\n",strlen(original));
    printf("Please input a mode you want: \n");
    gets(imode);                    //键入模式1、2、3
    r=code(imode,original,cipher);
    printf("Please input a mode to decipher: \n");
    gets(omode);
    decode(omode,cipher,decoded,r);
    printf("%s\n",decoded);
    return 0;
}
