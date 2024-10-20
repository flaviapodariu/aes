#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "aes.h"

int main() {
    FILE *file;
    //input file has to be in the same dir as the bin, so pwd would be /aes/bin
    file = fopen("../input.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // read from file and get input size
    fseek(file, 0, SEEK_END);
    int input_size = ftell(file);
    fseek(file, 0, SEEK_SET);


   // Zero Pad to nearest multiple of AES_BLOCKLEN (16 for AES128)
   // last modulo ensures we don't add an unnecessary 16 byte pad when the input size is a multiple of 16.
    int padded_size = input_size + (AES_BLOCKLEN - (input_size % AES_BLOCKLEN)) % AES_BLOCKLEN;
 
    uint8_t *input = (uint8_t*) malloc(padded_size * sizeof(uint8_t));

    size_t bytesRead = fread(input, 1, input_size, file);
    fclose(file);

    uint8_t *input_copy = (uint8_t*) malloc(padded_size * sizeof(uint8_t));
    memcpy(input_copy, input, input_size);

    // Example key and input data
    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    // --------------------------------------ENCRYPTION -----------------------------------------------------
    // Initialize AES context with the key
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);

    clock_t start_time = clock();
    AES_CBC_encrypt_buffer(&ctx, input, padded_size);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken to encrypt %d bytes: %f seconds\n", padded_size, time_taken);

    // Print encrypted text
    Print_Text(input, padded_size);
    
    // --------------------------------------ENCRYPTION -----------------------------------------------------


    // --------------------------------------DECRYPTION -----------------------------------------------------
    // // re-init context for decryption
    // AES_init_ctx_iv(&ctx, key, iv);

    // start_time = clock();
    // AES_CBC_decrypt_buffer(&ctx, input, padded_size);
    // end_time = clock();

    // time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    // printf("Time taken to decrypt %d bytes: %f seconds\n", padded_size, time_taken);

    // // Print decrypted text
    // Print_Text(input, padded_size);
    // --------------------------------------DECRYPTION -----------------------------------------------------



    // input went through encryption and decryption, so if algorithm is correct
    // input and its copy should be identical
    // Check_Results(input_copy, input, input_size);


    free(input);
    free(input_copy);

    return 0;
}

void Print_Text(uint8_t *text, int size) {
    if(size > 64) return;

	for(int i=0;i<size;++i){
		printf(" %2x", text[i]);
	}
	printf("\n");
}

void Check_Results(uint8_t *input, uint8_t *decrypted, int size) {
	if(memcmp((char*) input, (char*) decrypted, size) != 0){
			printf("DECRYPTION ERROR.\n");
			exit(1);
    }

	printf("DECRYPTION OK.\n");
}