#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "serial_aes.h"

/*
    -> input and plain_text contain the same values initially
    -> after encryption, input will contain the encrypted value of the plain_text
    -> after decryption, input will contain the decrypted value, which should be the plain_text

*/
int main() {
    
    FILE *file;
    file = fopen("input.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // read from file and get input size
    fseek(file, 0, SEEK_END);
    int input_size = ftell(file) + 1;
    fseek(file, 0, SEEK_SET);

    Byte *input = (Byte*) malloc(input_size * sizeof(Byte));
    if (input == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    if(input) {
        fread(input, 1, input_size, file);
    } else {
        printf("ERROR: AES needs an input to encrypt it.\n");
        exit(1);
    }

    fclose(file);
    
    // create a copy for the initial input,
    // because it will be overwritten by the encryption and decryption functions
    Byte *plain_text = (Byte*) malloc(input_size * sizeof(Byte));
    memcpy(plain_text, input, input_size);
	
    // Test only
    Check_Results(plain_text, input, input_size);

	Byte key[32]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0,
				  0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20,
				  0x21, 0x22, 0x23, 0x24, 0x25, 0x26};	
	AES_setKey(key);

    clock_t start_time = clock();
    AES256_encrypt(input, input_size);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken to encrypt %d bytes: %f seconds\n", input_size, time_taken);


/*  For testing small inputs:
        printf("Encrypted:\n");
        Print_Text(input, input_size);
 */

    // start_time = clock();
	// AES256_decrypt(input, input_size);	
    // // end_time = clock();
    
    // time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    // printf("Time taken to decrypt %d bytes: %f seconds\n", input_size, time_taken);

    // hopefully, the initial text will be equal to "input" aka the decrypted text
    // Check_Results(plain_text, input, input_size);
	
	return 0;
}

void Print_Text(Byte *text, int size) {
	for(int i=0;i<size;++i){
		printf(" %2x", text[i]);
	}
	printf("\n");
}

void Check_Results(Byte *input, Byte *decrypted, int size) {
	for(int i=0; i<size; ++i){
		if(input[i] != decrypted[i]){
			printf("DECRYPTION ERROR.\n");
			exit(1);
		}
	}
	printf("DECRYPTION OK.\n");
}