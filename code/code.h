

int base_encode(char * original,char * base64);
int base_decode(char * original,char *dedata);
void encrytion(char * original,char * MyKey,char * encipher);
void decrytion(char * original,char * YourKey,char * message);
void BC_code(char * original,char * base64);
void BC_decode(char * base64,char * decoded);
int compress(char * original,int m,char * compressed);
int decompress(char * original,int m,char * decompressed);
