#include <stdio.h>
#include <dirent.h>
#include <fstream>
#include "aes_setup.h"
#define MEGABYTE                    1048576
#define TEST_FILE                   "C:\\Users\\nxuxp\\OneDrive\\Desktop\\testing.txt"
using namespace std;

/* Functions */
void PrintBytes(
	IN BYTE* pbPrintData,
	IN DWORD    cbDataLen)
{
	DWORD dwCount = 0;

	for (dwCount = 0; dwCount < cbDataLen; dwCount++)
	{
		printf("0x%02x ", pbPrintData[dwCount]);			// "0x%02x, "

		if (0 == (dwCount + 1) % 4) putchar('\n');
	}

}
BYTE SubByte(BYTE input);

int main(void) {
	typedef unsigned char BYTE;
	typedef BYTE* PBYTE;

	PBYTE rgbPlaintext = new BYTE[MEGABYTE];
	PBYTE rgbCiphertext = new BYTE[MEGABYTE];

	/* KEY */
	static BYTE AES_128_KEY[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
	};

	/* getting file size */
	struct stat results;
	stat(TEST_FILE, &results);
	int fileSize = results.st_size;
	if (fileSize > MEGABYTE) fileSize = MEGABYTE;

	/* filling rgbPlaintext with data from file */
	fstream myFile(TEST_FILE, std::ios::in | std::ios::binary);
	myFile.read((char*)rgbPlaintext, fileSize);

	/* encrypting the plaintext using the key */
	aesEncrypt(rgbPlaintext, rgbCiphertext, AES_128_KEY, fileSize);

	/* return */
	return 0;
}
