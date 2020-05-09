/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/08/2019 07:27:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void check_digest(char *filename, char *digest_algorithm, char *hash) {
	FILE *f = fopen(filename, "r");

	unsigned char md_value[EVP_MAX_MD_SIZE];
	EVP_MD_CTX *ctx = EVP_MD_CTX_new();
	const EVP_MD *md = EVP_get_digestbyname(digest_algorithm);
	EVP_DigestInit_ex(ctx, md, NULL);
	char buffer[100];
	int md_len;
	int qt_bytes = fread(buffer, 100, 1, f);
	while (qt_bytes > 0) {
		EVP_DigestUpdate(ctx, buffer, qt_bytes);
		qt_bytes = fread(buffer, 100, 1, f);
	}
	EVP_DigestFinal_ex(ctx, md_value, &md_len);
	EVP_MD_CTX_free(ctx);
	int i;
	if (strlen(hash) != md_len * 2) {
		printf("Entry hash length is different of the length of a hash produced by the selected algorithm!\n");
		return;
	}
	int output_size = md_len * 2;
	char *output = (char *)malloc(sizeof(char) * output_size);
	for (i = 0; i < md_len; i++) {
		sprintf(&(output[i*2]), "%02x", md_value[i]);
	}
	for (i = 0; i < output_size; i++) {
		if (hash[i] != output[i]) {
			printf("Different digest values!\n");
			return;
		}
	}
	free(output);
	printf("Same digest value!\n");
	fclose(f);
}
//HOW TO USE
//./digest_compare to_hash_file sha1 sha1_hash
//./digest_compare to_hash_file sha256 sha256_hash
//./digest_compare to_hash_file sha512 sha512_hash
//RESULTS:
//1 - Entry hash length is different of the length of a hash produced by the selected algorithm!
//2 - Different digest values!
//3 - Same digest value!
int main(int argc, char *argv[]) {
	char *filename = argv[1];
	char *digest_algorithm = argv[2];
	char *hash = argv[3];
	check_digest(filename, digest_algorithm, hash);
	return EXIT_SUCCESS;
}
