/*
Name        : P Rakesh
Date        : 29/04/2025
Project     : Mp3 Tag reader
Batch       : 24038
Descrition  :The MP3 Tag Reader is a C-based utility designed to extract and display metadata from MP3 audio files. This metadata, commonly stored in ID3 tags (ID3v1 or ID3v2), contains information such as the song title, artist name, album, year, genre, and more. The tool parses these tags and presents the information in a human-readable format, allowing users to quickly view the details embedded in their MP3 files without needing a full-fledged media player.

             Features:

             Reads and displays ID3v1 tag data from MP3 files.

             Extracts fields such as Title, Artist, Album, Year, Comment, and Genre.

             Simple command-line interface.

             Input validation and error handling for unsupported or invalid files.
sample input : Suppose you have an MP3 file named song.mp3 that contains the following ID3v1 metadata:


                        Field	Value
                        Title	Bohemian Rhapsody
                        Artist	Queen
                        Album	A Night at the Opera
                        Year	1975
                        Comment	Remastered
                        Genre	Rock
               You run the tool using the command line:

                  ./a.out -v song.mp3
sample ouput :  Reading ID3v1 tags from: song.mp3

                Title   : Bohemian Rhapsody
                Artist  : Queen
                Album   : A Night at the Opera
                Year    : 1975
                Comment : Remastered
                Genre   : Rock

*/

#include"reader.h"
#include <string.h>
#include "tags.h"
#include "edit.h"

int main(int argc,char* argv[])
{
    if(argc>=3) //condition to check the arguements in my command line
    {
        Treader reader;
        if(check_operation(argv[1])==mp3_view) // function call to check the operation type 
        {
            if((read_and_validate(&reader,argv)) == mp3_success) //raed and validate function call if it is success only go to next step
            {
                if(read_data_mp3(&reader)==mp3_success) //read the data from mp3 file function call
                {
                  printf("SUCCESSFULLY COMPLETED\n");
                }
            }
        }
        else if(check_operation(argv[1])==mp3_edit) 
        {
            Edit edit; //creating structure variable
           if(read_and_validate_args(&edit,argv)==mp3_success) //function call fr read and validate
            {
                if(read_data_mp3_enc(&edit)==mp3_success) //function call for the read_data from mp3 file
                {
                    printf("EDITING COMPLETED\n");
                }
            }
        }
        else
        {
            printf("INFO: ./a.out -v to view the file\n");
            printf("INFO: ./a.out -E to Eidt the file\n");
    
        }
}
else if(argc==2)
{
    if(check_operation(argv[1])==mp3_help) //function call to check the operation type
    {
        printf("INFO: ./a.out -v to view the file\n");
        printf("INFO: ./a.out -E to Eidt the file\n");

    }
    else{
        printf("ERROR: pass valid arugeuements\n");
    } 
}
else{
    printf("ERROR: pass valid arguements\n");
    printf("INFO: for more info -> ./a.out --help\n");
}
}
OperationType check_operation(char* symbol) //check_operation definition
{
    if(strcmp(symbol,"-v")==0) // comparing the arguement of the comand line by using strcmp
    return mp3_view;
    else if(strcmp(symbol,"-e")==0) 
    return mp3_edit;
    else if(strstr(symbol,"--help")!=NULL) //for user user --help
    {
        return mp3_help;
    }
   else
   return mp3_unsupported; //returning unsupported
}