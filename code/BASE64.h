#ifndef BASE64_HEADER
#define BASE64_HEADER
// 全局常量定义
const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char padding_char = '=';

int base64_encode(const unsigned char * sourcedata,int m, char * base64);
int num_strchr(const char *str, char c);
int base64_decode(const char * base64, unsigned char * dedata);


#endif
