#include "metadata.h"

Metadata::Metadata(){

}


void Metadata::initialise_decoding_table(){
	int i;
	for (i = 0; i < 64; i++)
	decoding_table[(unsigned char)encoding_table[i]] = i;
}


char* Metadata::base64_encode(const unsigned char* data, size_t input_length, char* encoded_data, size_t* output_length){

	size_t calculated_output_length = 4 * ((input_length + 2) / 3);
	if (calculated_output_length > *output_length)
		return (NULL);
	*output_length = calculated_output_length;
	
	int i, j;
	for (i = 0, j = 0; i < input_length;) {

		uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
		uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
		uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;
		
		uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
		
		encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
	}

	for (i = 0; i < mod_table[input_length % 3]; i++)
		encoded_data[*output_length - 1 - i] = '=';

	return encoded_data;
}


int Metadata::base64_decode(const char* data, size_t input_length, unsigned char* decoded_data, size_t* output_length){
  if (input_length % 4 != 0)
    return -1;

  size_t calculated_output_length = input_length / 4 * 3;
  if (data[input_length - 1] == '=')
    calculated_output_length--;
  if (data[input_length - 2] == '=')
    calculated_output_length--;
  if (calculated_output_length > *output_length)
    return (-1);
  *output_length = calculated_output_length;

  int i, j;
  for (i = 0, j = 0; i < input_length;) {

    uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

    uint32_t triple =
    (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

    if (j < *output_length)
      decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
    if (j < *output_length)
      decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
    if (j < *output_length)
      decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
  }

  return 0;
}
