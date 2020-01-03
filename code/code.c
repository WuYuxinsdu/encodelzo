
/****************************************************************************************/
/**���ߣ������� ������                                                                **/
/**ʱ�䣺2019.1.8                                                                       **/
/**���ܣ��������ַ���ִ��ѹ����DES���ܣ�BASE64���룬BAES64���룬DES���ܣ���ѹ������ **/
/*****************************************************************************************/
#ifndef _CODE_H
#define _DCODE_H

#include "code.h"

/* First let's include "minizo.h". */

#include "minilzo.h"

/* We want to compress the data block at 'in' with length 'IN_LEN' to
 * the block at 'out'. Because the input block may be incompressible,
 * we must provide a little more output space in case that compression
 * is not possible.
 */

#ifndef MAX_LENGTH
#define MAX_LENGTH 1000
#endif

#define BC 1  //miniLZO+Base64
#define BD 2  //DES_ECB+Base64
#define BCD 3 //miniLZO+DES_ECB+Base64

#define IN_LEN      (128*1024ul)
#define OUT_LEN     (IN_LEN + IN_LEN / 16 + 64 + 3)

static unsigned char __LZO_MMODEL in  [ IN_LEN ];
static unsigned char __LZO_MMODEL out [ OUT_LEN ];


/* Work-memory needed for compression. Allocate memory in units
 * of 'lzo_align_t' (instead of 'char') to make sure it is properly aligned.
 */

#define HEAP_ALLOC(var,size) \
    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

//ѹ��,BSAE64���� CB
void BC_code(char * original,char * base64)
{
    char compressed[MAX_LENGTH]={0};    //�������ַ���
    int r1,r2;
    r1=compress(original,strlen(original),compressed);
    r2=base64_encode(compressed,r1,base64);  //����Ҳ�õ���strlen()����
    printf("Compressed %d:%s\nBase64 %d:%s\n",r1,compressed,r2,base64);
}
//BASE64����,��ѹ�� BC
void BC_decode(char * base64,char * decoded)
{
    char dedata[MAX_LENGTH]={0};
    int r1,r2;
    //char *decompressed=(char *)malloc(MAX_LENGTH);
    r1=base64_decode(base64,dedata);
    r2=decompress(dedata,r1,decoded);
    printf("Base64 %d:%s\nDecompressed %d:%s\n",r1,dedata,r2,decoded);
}

//DES����,BASE64����  DB
void BD_code(char * original,char * base64, char *MyKey)
{
    char cipher[MAX_LENGTH]={0};    //�������ַ���
    //char MyKey[9]={0};
    int r1,r2;

    r1=des_ecb_encrypt(cipher,original,strlen(original),MyKey);
    r2=base64_encode(cipher,r1,base64);
    printf("Encryption %d:%s\nBase64 %d:%s\n",r1,cipher,r2,base64);
}
//BASE64����,DES����  BD
void BD_decode(char * base64,char * decoded,char *YourKey)
{
    char dedata[MAX_LENGTH]={0};
    //char YourKey[9]={0};
    int r1,r2;
    r1=base64_decode(base64,dedata);
    r2=des_ecb_decrypt(decoded,dedata,r1,YourKey);
    printf("Base64 %d:%s\nDeEncryption %d:%s\n",r1,dedata,r2,decoded);
}

//ѹ��,����,BSAE64���� CDB
int BCD_code(char * original,char * base64)
{
    char cipher[MAX_LENGTH]={0};    //�������ַ���
    char compressed[MAX_LENGTH]={0};
    char MyKey[9]={0};
    int r1,r2,r3;

    printf("Please input your Secret Key:\n");
    gets(MyKey);
    Key_detection(MyKey);
    r2=compress(original,strlen(original),compressed);
    r3=des_ecb_encrypt(cipher,compressed,r2,MyKey);
    r1=base64_encode(cipher,r3,base64);
    printf("Compressed %d:%s\nEncryption %d:%s\nBase64 %d:%s\n",r2,compressed,r3,cipher,r1,base64);
    return r2;
}
//BASE64����,����,��ѹ��  BDC
void BCD_decode(char * base64,char * decoded,int m)
{
    char message[MAX_LENGTH]={0};
    char dedata[MAX_LENGTH]={0};
    char YourKey[9]={0};
    int r1,r2,r3;
    printf("Please input your Secret Key to Deciphering:\n");  // ��������Կ�Խ���
    gets(YourKey);
    r3=base64_decode(base64,message);
    r1=des_ecb_decrypt(dedata,message,r3,YourKey);
    r2=decompress(dedata,m,decoded);
    printf("Base64 %d:%s\nDeEncryption %d:%s\nDecompressed %d:%s\n",r3,message,m,dedata,r2,decoded);
}

//����ģʽѡ����ܺ���
void code(char * mode,char * original,char * cipher,char *MyKey)
{
    int m=0,a=0;
    m=atoi(mode);
    char temp[10]="";
    switch(m)
    {
    case BC:
        {
            BC_code(original,cipher);
            break;
        }
    case BD:
        {
            BD_code(original,cipher,MyKey);
            break;
        }
    case BCD:
        {
            a=BCD_code(original,cipher);
            strcat(cipher,"\\");
            sprintf(temp,"%d",a);
            strcat(cipher,temp);
            break;
        }
    }
}
//����ģʽѡ����ܺ���
void decode(char * mode,char * cipher,char * decoded)
{

    char YourKey[8]={0};
    int m=0,a,i=0;
    char temp[10]="";
    char *p;
    m=atoi(mode);
    switch(m)
    {
    case BC:
        {
            BC_decode(cipher,decoded);
            printf("The following is the data in BC mode:\n");
            break;
        }
    case BD:
        {
            BD_decode(cipher,decoded);
            printf("The following is the data in BD mode:\n");
            break;
        }
    case BCD:
        {
            p=cipher+strlen(cipher);
            while(*p--!='\\') i++;
            sscanf(p+1,"%d",&a);
            cipher[strlen(cipher)-i]='\0';
            BCD_decode(cipher,decoded,a);
            printf("The following is the data in BCD mode:\n");
            break;
        }
    }
}

void Key_detection(char * Key)
{
    int i=0;
    while(Key[i]!='\0')        // ������Կ����
	{
		i++;
	}
	while(i!=8)                  // ����8 ��ʾ����
	{
		printf("Please input a correct Secret Key!\n");
		gets(Key);
		i=0;
		while(Key[i]!='\0')    // �ٴμ��
		{
			i++;
		}
	}
}

lzo_uint out_len;

//miniLZOѹ��
int compress(char * original,int m,char * compressed)
{
    char r;
    r=lzo1x_1_compress(original,m,compressed,&out_len,wrkmem);
    if(r==LZO_E_OK)
        printf("Compress is successful!\n");
    else
        printf("Error!\n");
    return out_len;
}

lzo_uint in_len;

//miniLZO��ѹ��
int decompress(char * compressed,int m, char * decompressed)
{
    char r;
    int o=0;
//    r = lzo1x_decompress(compressed,strlen(compressed),decompressed,&in_len,NULL);
    r=lzo1x_decompress(compressed,m,decompressed,&in_len,NULL);
    //printf("r=%d\n",r);
    //printf("m:%d  out_len:%d\n",m,out_len);//r��ֵ������-4  ԭ��ȫ�ֱ�����ֲ�������ԭ��
    if(r==LZO_E_OK)
    {
        printf("Decompress is successful!\n");
        o=in_len;  //��ѹ��֮������ݿ��ܻḲ����ԭ����һЩ��������
                   //�������ѹ�������ĩ�˿��ܲ����ǡ�\0'������������ԭʼ���ݣ���������Ҫ��'\0'��Ĩ��
        decompressed[o]=0;
    }
    else
        printf("Error!\n");

    return in_len;
}
#endif
