/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3 - Decompression
 * Name: Jacob Reed
 * Student ID: 14162996
 * Date of submission: 07 / 10 / 2021
 *
 * This decompression algorithm is based on LZ77 compression algorithm.
 * This takes triplets produced by the compression algorithm and
 * decodes them to re-create the original file.

 * CURRENTLY PRODUCES A SEGMENTATION FAULT AFTER SCANF(OFILE). UNSURE WHY

 * potential changes;
 * MUST IMPLEMENT CHANGING COMPRESSION FILE NAME - user choose name, push
    an extension on the file or add to the name.
 * continued function separation
 * better commenting
 * efficiencies may be possible in the algorithm
******************************************************************************/

#include <stdio.h> /*printf(), fopen(), fgetc(), EOF, FILE, fwrite(), scanf()*/
#include <stdlib.h> /*malloc(), realloc(), free(),*/

void decompressFile(char Ifile[], char Ofile[]){

/******************************************************************************
Initialisation of necessary tracking ints and array streams
******************************************************************************/
    

    int i, pos = 0, outcount = 0;
    /*Input stream as char array of entire compressed file*/
    unsigned char* inputStream = NULL;
    if((inputStream = (unsigned char*) malloc(0)) == NULL){
        printf("Error creating inputStream\n");
        return;
    }
    
    
    /*Output stream for decompressed file*/
    unsigned char* outputStream = NULL;
    if((outputStream = (unsigned char*) malloc(0)) == NULL){
        printf("Error creating outputStream\n");
        return;
    }
    
    
    /* receive all input data, allocate to input stream and count chars*/
    FILE* FP;
    FP = fopen(Ifile, "rb");
    if(!FP){
        printf("Error opening file\n");
        return;
    }
    

    
    char ch;
    int fileCharLength = 1;
    for(ch = fgetc(FP); ch != EOF; ch = fgetc(FP)){
        inputStream = (unsigned char*)realloc(inputStream, fileCharLength*sizeof(unsigned char));
        inputStream[fileCharLength-1] = ch;
        fileCharLength++;  
    }
    inputStream = (unsigned char*)realloc(inputStream, fileCharLength*sizeof(unsigned char));
    inputStream[fileCharLength] = '\0';
    
    
    fclose(FP);
    
    
/******************************************************************************
Main loop of function. 
******************************************************************************/
   
    for(i = 0; i<fileCharLength; i = i + 3){
        
        
        /*Track the current triplet to be decompressed*/
        unsigned char offset = inputStream[i];
        unsigned char length = inputStream[i+1];
        unsigned char character = inputStream[i+2];
        
        /*Update position tracking variables*/
        pos = outcount;
        outcount = outcount + length + 1;
        
        /*Update size of the output array to handle the new size of string*/
        outputStream = (unsigned char*) realloc(outputStream, outcount*sizeof(unsigned char));
        
        /*Add the encoded characters to the end of the output array*/
        int j;
        for(j = 0; j<length; j++){
            outputStream[pos+j] = outputStream[pos-offset+j];    
        }
        
        /*printf("%d,%d,%c",pos,length,character);*/
        outputStream[pos+length] = character;
        
    }  
    
    
    /* this is a testing function to output the decompressed data
    directly to the current terminal. only in debug
    i = 0;
    while(i<outcount){
        printf("%c",outputStream[i]);
        i++;
    }
    */

    /*Writing the new decompressed file from output stream*/
    FILE* FPO;
    if((FPO = fopen(Ofile, "wb")) == NULL){
        printf("Error opening file\n");
        return;
    }
    
    FILE* NFP;
    NFP = fopen(Ofile, "w");
    if(NFP == NULL){
        printf("Failed to open new compression file");
    }
    for(i = 0; i<=outcount-3; i++){
        putc(outputStream[i], NFP);
    }
    
    fclose(NFP);


    free(inputStream);
    free(outputStream);
    return;
}

/*Testing main function
int main(void){
    char Ifile[100];
    char Ofile[100];
    printf("Enter file to decompress>");
    scanf("%s", Ifile);
    printf("Enter decompressed file name>");
    
    scanf("%s", Ofile);
    
    decompressFile(Ifile, Ofile);
    return 0;
} */
