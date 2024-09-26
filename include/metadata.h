#ifndef METADATA_HPP
#define METADATA_HPP

#include <arpa/inet.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
static int decoding_table[256]; // an incoming char can range over ASCII, but by mistake could be
                                // all 8 bits.

static int mod_table[] = {0, 2, 1};

class Metadata {

	Metadata();

	private:
		void initialise_decoding_table();
		char* base64_encode(const unsigned char* data, size_t input_length, char* encoded_data, size_t* output_length);
		int base64_decode(const char* data, size_t input_length, unsigned char* decoded_data, size_t* output_length);

};

#endif
