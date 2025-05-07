#include <stdio.h>
#include "decode.h"
#include "types.h"
#include<string.h>
#include "common.h"
#include "encode.h"
#include<stdlib.h>
Status read_and_validate_decode_args(char *argv[], decodeInfo *decInfo)
{
    //function for validate .bmp file or not
    if(strstr(argv[2],".bmp") != NULL) //using strstr to check the file
    {
        decInfo->dest_image_fname = argv[2];
    }
    else
    {
        printf("ERROR : you have to gave .bmp file only\n");
        return e_failure;
    }
    if(argv[3]!= NULL)
    {
        decInfo->dup = strtok(argv[3],".");
    }
    else
    {

        decInfo->dup = "ROCKY";
    }
   return e_success;
}
Status open_file(decodeInfo *decInfo)
{
    //opening the files function
    decInfo->fptr_dest_image = fopen(decInfo->dest_image_fname, "r"); //opening the encodedfile in read mode
    // Do Error handling
    if (decInfo->fptr_dest_image == NULL) //if it return null address the print error
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->dest_image_fname);

    	return e_failure;
    }
    printf("INFO: Successfully opened files\n");
    return e_success; //return e_success
}
Status decode_magic_string(decodeInfo *decInfo)
{
    //decode the magic string from the encoded file
    char magic[2];
    if(decode_data_from_image(magic, 2,decInfo->fptr_dest_image)==e_failure) //function call of decode data from image
    {
        printf("ERROR: while decoding data from image\n");
        return e_failure;
    }
    //printf("magic_string encoded sucesfully\n");
    strcpy(decInfo->magic_string,magic); //using strcpy copy the magic string to structure variable 
    printf("INFO: magic_string decoded sucesfully \n");
}
Status do_decoding(decodeInfo *decInfo)
{
    //decoding function
    if(open_file(decInfo) == e_failure) //if it is e_failure print error 
                                         //return e_failure
    {
        printf("ERROR: file doesn't open\n");
        return e_failure;
    }
    printf("## DECODING DATA STARTED ##\n");
    printf("INFO: decoding magic string\n");
    fseek(decInfo->fptr_dest_image,54,SEEK_SET); //fessk function to skip the 54 bytes
    if(decode_magic_string(decInfo)==e_failure) ////idecode magic string if it returns e_failure print error  return e_failure
    {
        printf("ERROR: magic string does not decoded\n");
        return e_failure;
    }


    printf("INFO: Magic string decoded succesfuuly\n");
    char passwd[20]; //declare string
    printf("INFO: Enter password to decode your data: ");
    scanf("%s",passwd); //read password from user
    if(strcmp(decInfo->magic_string,passwd)!=0) //copare the decoded magic string and user entered password if it is equal only go to next next step
    {
        printf("ERROR: your password is wrong sorry!\n");
        return e_failure;
    }
    printf("INFO: password verified\n");

    printf("INFO: decoding secret file extension size\n");

    if(decode_secret_file_extn_size(decInfo->fptr_dest_image,decInfo)==e_failure) //function call for decode secret file extn size then if it returns e_failure then print error and return e_failure
    {
        printf("ERROR: decoding size of secret file  extension is not complted\n");
        return e_failure;
    }
    printf("INFO: secret file extension size decoded successful\n");
  
    printf("INFO: decoding secret file extension\n");
    if(decode_secret_file_extn(decInfo->fptr_dest_image,decInfo)==e_failure) //function call for decode secret file extn then if it returns e_failure then print error and return e_failure
    {
        printf("ERROR: secret file extension data not decoded\n");
        return e_failure;
    }
    printf("INFO:secret file extension decoded succesfull\n");


    decInfo->secret_file_name = malloc(strlen(decInfo->dup) + strlen(decInfo->ext_data) + 1); //dynamically allocating the memory for secret file name
    strcpy(decInfo->secret_file_name, decInfo->dup);
    strcat(decInfo->secret_file_name, decInfo->ext_data);
    printf("INFO: decoding secret file size\n");
    if(decode_secret_file_size(decInfo->fptr_dest_image,decInfo)==e_failure)//function call for decode secret file size if it return  e_failure print error and returns e_failure
    {
        printf("ERROR: secret data is not decoded\n");
        return e_failure;
    }
    printf("INFO: secret size decoded successfully\n");


    decInfo->fptr_secret_data = fopen(decInfo->secret_file_name, "w"); //open the secret file in write mode 
    if (decInfo->fptr_dest_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open the file %s\n", decInfo->dest_image_fname);

    	return e_failure;
    }
    printf("INFO: secret file size Decoded succesfully\n");
    printf("INFO: decodig secret file data\n");
    if(decode_secret_file_data(decInfo)==e_failure) //function call for decode secret file data from encoded file if it returns e_failure then print error and return e_failure
    {
        printf("ERROR: secret filedata not decoded\n");
        return e_failure;
    }
    printf("INFO: secret file data Decoded succesfully\n");
    printf("## DECODED SUCCESSFULLY ##\n");
    return e_success;

}

Status decode_byte_from_lsb(char* data, char *decode_buffer) //function definition for decode byte from lsb
{
    int bit_get=0;
    for(int i=0;i<8;i++) // loop to decode a 1 byte from 8 ytes of data
    {
        int res=decode_buffer[i] & 1;
        res=res << i;
        bit_get=res | bit_get;
    }
    *data = bit_get; //store it in the particular data by dereferencing
}
Status decode_data_from_image(char *data, int size, FILE *fptr_dest_image)
{
    //function definition for the decode data from image 
    char decode_buffer[8];
    for(int i=0;i<size;i++) //loop to decode data by size times
    {
        fread(decode_buffer,8,1,fptr_dest_image); //fread for reading 8 bytes from image
        decode_byte_from_lsb(&data[i], decode_buffer); //function call for decode byte from lsb
    }
}
Status decode_secret_file_extn_size(FILE *fptr_dest_image,decodeInfo *decInfo)
{
    //function defintion for decode secret file extension size from encoded file
    char extn_size_buffer[32];
    fread(extn_size_buffer,32,1,fptr_dest_image); //read 32 bytes from the file encoded file
    int res =0;
    for(int i=0;i<32;i++) //loop to decode 32 bits from 32 bytes fromthe file
    {
        int bit = extn_size_buffer[i] &1;
        bit = bit << i;
        res = res | bit;
    }
    decInfo->ext_size = res; //store it in the ext_size file
    return e_success;
}
Status decode_secret_file_extn(FILE *fptr_dest_image, decodeInfo *decInfo)
{
    //function definiition for secret file extn 
    char ext_b_data[decInfo->ext_size];
    decode_data_from_image(ext_b_data, decInfo->ext_size,fptr_dest_image); //function call for decode data from image
    strcpy(decInfo->ext_data,ext_b_data);
    return e_success;
    
}
Status decode_secret_file_size(FILE *fptr_dest_image, decodeInfo *decInfo)
{   //decode secret file size from the encoded file
    char file_size_buffer[32];
    fread(file_size_buffer,32,1,fptr_dest_image); //read 32 bytes from the encoded image
    int res =0;
    for(int i=0;i<32;i++) // loop to decode 32 bits from the 32 bytes from lsb end
    {
        int bit = file_size_buffer[i] &1;
        bit = bit << i;
        res = res | bit;
    }
    decInfo->secret_fsize = res;
    return e_success; //returning e_success
}
Status decode_secret_file_data(decodeInfo *decInfo)
{ 
    //function definition for the decoding the secret file data extension
    char secret_b_data[decInfo->secret_fsize];
    decode_data_from_image(secret_b_data, decInfo->secret_fsize,decInfo->fptr_dest_image); //decoding the data from the image function calll
    fwrite(secret_b_data,decInfo->secret_fsize,1,decInfo->fptr_secret_data); //write the data to secret file data
    return e_success;
}