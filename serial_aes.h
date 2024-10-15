#ifndef AES_TABLE_H
#define AES_TABLE_H

typedef unsigned char Byte;

Byte getSbox(Byte num);
Byte getinvSbox(Byte num);
void key_schedule128(Byte keys[11*16]);
void key_schedule256(Byte keys[15*16]);
void add_round_key(Byte *block, Byte *key);
void byte_sub(Byte *block);
void shift_row(Byte *block);
Byte ml(Byte num, Byte m);
void mix_columns(Byte *block);
void inv_mix_columns(Byte *block);
void inv_shift_row(Byte *block);
void inv_byte_sub(Byte *block);

void AES_setKey(Byte *nkey);
void AES128_encrypt(Byte *block);
void AES128_decrypt(Byte *block);
void AES256_encrypt_block(Byte *block);
void AES256_encrypt(Byte *input, int length);
void AES256_decrypt_block(Byte *block);
void AES256_decrypt(Byte *input, int length);

// utilitaries
void Print_Text(Byte *text, int size);
void Check_Results(Byte *input, Byte *decrypted, int size);

#endif