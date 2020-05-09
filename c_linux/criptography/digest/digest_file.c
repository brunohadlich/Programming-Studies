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
#include <openssl/evp.h>

void digest(char *filename, char *digest_algorithm) {
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
	for (i = 0; i < md_len; i++) {
		printf("%02x", md_value[i]);
	}
	printf("\n");
	fclose(f);
}
//HOW TO USE
//./digest_file to_hash_file sha1
//./digest_file to_hash_file sha256
//./digest_file to_hash_file sha512
//RESULTS:
//1 - sha1: f7e29477dac5e8ce0f02a528207b
//2 - sha256: 4d1648491379360e53f7f2ea934600de5170f7e29477dac5e8ce0f02a528207b
//3 - sha512: 68909eb5661436289978305a86db1994000fd12d4ac0436a85b283ba6282f47bbc161a96f996682f2619538e5f7b6b9941e42241fedbdffcceecaac91d174567
int main(int argc, char *argv[]) {
	char *filename = argv[1];
	char *digest_algorithm = argv[2];
	digest(filename, digest_algorithm);
	return EXIT_SUCCESS;
}
