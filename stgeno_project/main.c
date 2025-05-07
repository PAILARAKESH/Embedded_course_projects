/*    ////////////------------- DOCUMENTATION -------------------////////////   */
/*
NAME : P.RAKESH
PROJECT : STEGNOGRAPHY PROJECT
BATCH : 24038
DATE: 07/04/2025
DESCRIPTION: This project implements a simple yet effective steganography system that allows users to hide and retrieve secret data (such as text files) within BMP image files. The focus is on utilizing the least significant bit (LSB) technique, which manipulates the least significant bits of pixel values in an image to embed secret information without noticeably altering the image's appearance.

             The project includes two main functionalities:

             Encoding – Hiding a secret file inside a BMP image.

             Decoding – Extracting the hidden file from the stego image.
ENCODING PART: [+] Encoding started...
               [+] Valid BMP file detected: input.bmp
               [+] Secret file loaded: secret.txt (size: 142 bytes)
               [+] Encoding magic string...
               [+] Encoding file extension: .txt
               [+] Encoding secret file size: 142 bytes
               [+] Encoding secret file data...
               [+] Data encoded successfully into stego.bmp
DECODING PART:[+] Decoding started...
              [+] Valid BMP file detected: stego.bmp
              [+] Magic string found. Proceeding with decoding...
              [+] Extracted file extension: .txt
              [+] Extracted file size: 142 bytes
              [+] Decoding secret data...
              [+] Secret data successfully saved to extracted.txt

  
*/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "encode.h"
#include "types.h"
#include "decode.h"
OperationType check_operation_type(char *argv);

int main(int argc,char* argv[])
{
 if(argc>=3) //arguements condition
 {
    if(check_operation_type(argv[1])==e_encode)
    {
      EncodeInfo encInfo;
      if((read_and_validate_encode_args(argv,&encInfo))!=e_success) //function call
      {
        return 0;
    }
    if(do_encoding(&encInfo)==e_success)
    {
       fclose(encInfo.fptr_src_image); //closing the file pointers using structure varable
       fclose(encInfo.fptr_stego_image);
       fclose(encInfo.fptr_secret);
    }
   }
    else if(check_operation_type(argv[1])==e_decode)
    {
      
      decodeInfo decInfo;
      if((read_and_validate_decode_args(argv,&decInfo))==e_success)
      {
         if(do_decoding(&decInfo)!=e_success)
        return 0;
       fclose(decInfo.fptr_dest_image);//closing the file pointers using structure varable
       fclose(decInfo.fptr_secret_data);
    }

    }
    else{
      printf("ERROR: Encoding : ./a.out -e <.bmp file> <.txt> [optional output file]\nDecoding : ./a.out -e <.bmp file> [optional output file]\n");
      return 0;
    }

 }
 else
 {
    printf("ERROR: Encoding : ./a.out -e <.bmp file> <.txt> [optional output file]\nDecoding : ./a.out -e <.bmp file> [optional output file]\n");
    return 0;
 }
}
OperationType check_operation_type(char *argv)// function definition for checking operation
{
if((strcmp("-e",argv))==0) //for encoding
{
   return e_encode;
}
else if(strcmp("-d",argv)==0) //for decoding
{
   return e_decode;
}
else{
   return e_unsupported; //for unsupported
}
}
