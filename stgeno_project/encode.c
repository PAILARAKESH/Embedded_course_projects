#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);
    rewind(fptr_image);

    // Return image capacity
    return width * height * 3;
}
uint get_file_size(FILE *fptr)
{
    //find the size of secret file data and return it to check_capacity function ///long size_secret_file;
    fseek(fptr,0,SEEK_END);
    return ftell(fptr);
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    printf("Opening required files\n");
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }
    printf("INFO: Openend beautiful.bmp file\n");

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }
    printf("INFO: Openend secret.txt file\n");
    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);
    	return e_failure;
    }
    printf("INFO: Openend destination.bmp file\n");
    return e_success;
}
Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity =  get_image_size_for_bmp(encInfo->fptr_src_image);  //getting the source file size
    printf("INFO: checking secret file size\nINFO: DONE. not empty\n");      // call get_file_size function
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);   //getting the secret file size function call       
    uint header_bits = 54;
    uint magic_len = strlen(MAGIC_STRING);
    uint magic = magic_len*8;
    rewind(encInfo->fptr_secret); 
    printf("INFO: checking beautiful.bmp capacity to handle secret.txt data\n");
    if(encInfo->image_capacity < (header_bits + 32 + magic + 32 + encInfo->size_secret_file + 32 + 32)) //conditio to check sorce file capacity and seret file size and data with some other data
    {
        printf("ERROR: beautiful.bmp is not capable to handle secret.txt data\n");
        return e_failure;
    }
    printf("INFO: DONE\n");
    return e_success;
}
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    //comparing argv[2] and its .bmp using strstr()
    if(strstr(argv[2],".bmp") != NULL) 
    {
        encInfo->src_image_fname = argv[2];
    }
    else
    {
        printf("ERROR: YOU should pass the .bmp files as source\n");
        return e_failure;
    }
    //comparing argv[2] and its .txt .c .sh using strstr()
    if(argv[3]!=NULL)
    {
    if((strstr(argv[3],".txt") != NULL)||(strstr(argv[3],".c") != NULL)||(strstr(argv[3],".sh") != NULL))
    {
        encInfo->secret_fname = argv[3]; 
    }
    else 
    {
        printf("ERROR: you should pass the .txt or .c or .sh files only\n");
        return e_failure;
    }
}
    else 
    {
        printf("ERROR: you should pass the .txt or .c or .sh files only\n");
        return e_failure;
    }
    if(argv[4] == NULL)
    {
        printf("INFO: output file not mentioned.we creating destination .bmp file\n");
        encInfo->stego_image_fname = "destination.bmp";
    }
    else
    {
         //comparing argv[4] and its .bmp using strstr()
        if(strstr(argv[4],".bmp") != NULL)
        {
            encInfo->stego_image_fname = argv[4];
        }
        else
        {
            printf("ERROR: YOU should pass the .bmp files as destination\n");
            return e_failure;
        }
    }
    return e_success;
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    // copy the whole header data from sorce file to destination
    rewind(fptr_src_image);
    char buffer[54];
    fread(buffer,54,1,fptr_src_image); //shifting the source file to the 54 bytes
    fwrite(buffer,54,1,fptr_dest_image); //shifting the destination file to the 54 bytes
    return e_success;
}

Status do_encoding(EncodeInfo *encInfo) //do encoding funtction definition
{
	if(open_files(encInfo) == e_failure) //calling open file function to open the required files
    {
        printf("ERROR : while opening files\n");
        return e_failure;
    }
    printf("INFO: DONE\n");
    printf("## ENCODING PROCEDURE STARTED ##\n");
    if(check_capacity(encInfo)==e_failure) //check cpacity function call for checking sorce file consisting the enough size
    {
        printf("ERROR: Your source file is not capable to store the secret data\n");
        return e_failure;
    }
    if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)!=e_success)
    {// copy the header data from source to destination
        printf("ERROR: failed to copy 54 bytes from header of source file\n");
        return e_failure;
    }
    printf("INFO: Succesfully copied 54 bytes from header of source to dest image\n");
    printf("INFO: encoding maagic string\n");
    if(encode_magic_string(MAGIC_STRING,encInfo)==e_failure) //function call to encode magic string into the destination
    { 
        printf("ERROR: encoding magic string error\n");
        return e_failure;
    }
    printf("INFO: Magic string encoded succesfully\n");
    char* str = strchr(encInfo->secret_fname,'.');
    strcpy(encInfo->extn_secret_file,str);
    printf("INFO: encoding secrest file extension\n");
    if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)!=e_success) //function call for encoding the secret file extension 
    {
        printf("ERROR: Extension not encoded\n");
        return e_failure;
    }
    printf("INFO:Secret file Extension encoded succesfully\n");
    printf("INFO: encoding secret file size\n");
    if(encode_secret_file_size(encInfo->size_secret_file,encInfo)!=e_success)//function call for encoding the secret file size into the destination 
    {
        printf("ERROR: secret file not encoded\n");
        return e_failure;
    }
    printf("INFO: secret file size succesfully encoded\n");
    if(encode_secret_file_data(encInfo)==e_failure) //function call for encoding the secret file data
    {
        printf("ERROR: secret data not encoded succesfiully\n");
        return e_failure;
    }
    printf("INFO: secret file data encoded succesfully\n");
    printf("INFO: encoding remaining data\n");
    if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image)!=e_success)
    {
        printf("ERROR : copying reamining data\n");
        return e_failure;
    }
    printf("## ENCODING DATA SUCCESSFULLY ##\n");
    //step 5 call the encode_magic_string(MAGIC_STRING,encInfo)-->true print succes message go to step 6
    //false -----> return e_failure
    //step 6: Extract .txt fromthe secret file name
    //and store into the structure member (extn_secret_file)
    return e_success;

}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    char magic_str[]=MAGIC_STRING; //copy for the magic string
    int size = strlen(magic_str);
    if(encode_data_to_image(magic_str,size, encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_failure)
    {
        printf("ERROR: Encoding data to image is not successfull\n");
        return e_failure;
    }
    return e_success;
    //step1: int size find size of magic string
    //call encode_data_to_image(magic_string,size, encInfo->fptr_src_image, encinfo->fptr_stego_image)
}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    //encode the byte to lsb of 1 byte of sorce data into image buffer and encode into destination file
    int get_bit=0;
    for(int i=0;i<8;i++) // loop to encode 8 bits into 8 bytes
    {
        get_bit = data & (1<<i);
        get_bit = get_bit >> i; 
        image_buffer[i] = image_buffer[i] & (~(1));
        image_buffer[i] = image_buffer[i] | get_bit;
    }
}
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
     //char image_buffer[8];
    //step1: read 8 bytes from the src image store into imagebuffer
    //step 2: call the encode_byte_to _lsb(data[i],imagebuffer)
    //step 3: write the imageBuffer to dest image
    //step 4: repeat the same process
    //step 5: return e_success
    char image_buffer[8];
    for(int i=0;i<size;i++)
    {
        fread(image_buffer,8,1,fptr_src_image);
        encode_byte_to_lsb(data[i],image_buffer);
        fwrite(image_buffer,8,1,fptr_stego_image);
    }
    return e_success;
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    //encoding the secret file size
    rewind(encInfo->fptr_secret);
    char ext[1];
    for(int i=0;i<32;i++)
    {
        fread(ext,1,1,encInfo->fptr_src_image);
        ext[0]=ext[0]&(~1);
        int bit=file_size&(1<<i);
        bit=bit>> i;
        ext[0]=ext[0]|bit;
        fwrite(ext,1,1,encInfo->fptr_stego_image);
    }
    return e_success;

}
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    //encoding the file extension size int dest file
    printf("INFO: encoding secret file ectension size\n");
    uint len = strlen(file_extn);
    char ext[1];
    for(int i=0;i<32;i++) //loop to encode secret file extension size into destination file
    {
        fread(ext,1,1,encInfo->fptr_src_image); //read 1 byte from source file
        ext[0]=ext[0] & (~1); //encoding the data into the lsb of the ext
        int bit=len&(1<<i);
        bit=bit>>i;
        ext[0] = ext[0]|bit;
        fwrite(ext,1,1,encInfo->fptr_stego_image); // write 1 byte to destination file
    }
    printf("INFO: Secret file size encoded successfully\n");
    //encoding the extension of the file into the dest
    printf("INFO: encoding secret file data\n");
    char img_buffer[8];
    for(int i=0;i<len;i++) // loop to encode secret file extension
    {
        fread(img_buffer,8,1,encInfo->fptr_src_image); //read 8 bytes data from source file
        encode_byte_to_lsb(file_extn[i],img_buffer); //function call of encode byte to lsb
        fwrite(img_buffer,8,1,encInfo->fptr_stego_image);  //write 8 bytes data to destination file
    }
    printf("INFO: secret file data encoded successfully\n");
    return e_success;
    
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char sec_buffer[encInfo->size_secret_file];
    fread(sec_buffer,encInfo->size_secret_file,1,encInfo->fptr_secret);
    //encoding the data to imagein your in your source file
    //after encoding the data to image we if it is success go to next step
    if(encode_data_to_image(sec_buffer,encInfo->size_secret_file,encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_failure) //function call
    {
        printf("ERROR: Encoded data to image is not successfull\n");
        return e_failure;
    }
    return e_success;
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    //copy the reamining data from source file to destination filestination

    char ch[1];
    
    while(fread(ch,1,1,fptr_src) > 0) // loop to cpy the data upto the eof of source file
    {
        fwrite(ch,1,1,fptr_dest);
    }
    printf("INFO: Remaing data is copied successfull\n");
    return e_success;
}
