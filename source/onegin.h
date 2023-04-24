#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>
#include <ctype.h>


typedef const unsigned int natural;


//------------------------------------------------------------------------------------
//! The function opens the file for reading
//!
//! @param [in]   filename                input file name
//! @return pointer to file
//------------------------------------------------------------------------------------
FILE* OpenFile (const char* filename);


//------------------------------------------------------------------------------------
//! The function reads data about the text
//!
//! @param [in]   onegin_input            input file
//! @param [out]  number_of_characters    number of characters
//! @param [out]  number_of_lines         number of lines
//------------------------------------------------------------------------------------
void TextParametrs (FILE* onegin_input, unsigned int* number_of_characters, unsigned int* number_of_lines);


//------------------------------------------------------------------------------------
//! The function create buffer
//!
//! @param [in]  MAXLENGTH_PTR            Number of lines in the file
//! @param [in]  LENGTH_FILE              Number of characters in the file
//!
//! @return pointer to buffer
//------------------------------------------------------------------------------------
struct sorting* CreateBuffer (natural MAXLENGTH_PTR, natural LENGTH_FILE);


//------------------------------------------------------------------------------------
//! The function fills the buffer with data from the text
//!
//! @param [in]  file                     input file
//! @param [out] buffer                   pointer to buffer
//------------------------------------------------------------------------------------
void FullBuffer (FILE* file, struct sorting* buffer);


//------------------------------------------------------------------------------------
//! The functions �ompares strings
//!
//! @param [in]  str1                     first string
//! @param [in]  str2                     second string
//!
//! @return the difference between the lines
//------------------------------------------------------------------------------------
int StrCmp (const char* str1, const char* str2);


//------------------------------------------------------------------------------------
//! The functions sort strings
//!
//! @param [in]  index                    array of pointers to strings
//! @param [in]  number_of_lines          number of lines
//! @param [in]  Compare                  The function by which sorting will take place
//------------------------------------------------------------------------------------
void Sorting (char** index, natural number_of_lines, int (*Compare)(const char*, const char*));


//------------------------------------------------------------------------------------
//! The function opens the file for writing
//!
//! @param [in]   filename               output file name
//! @return pointer to file
//------------------------------------------------------------------------------------
FILE* CloseFile (const char* filename);


//------------------------------------------------------------------------------------
//! The functions writes the sorted text to the output file
//!
//! @param [in] book                     array of pointers to strings
//! @param [in] output                   output file
//! @param [in] number_of_lines          number of lines
//------------------------------------------------------------------------------------
void Output (char** book, FILE* output, natural number_of_lines);


//------------------------------------------------------------------------------------
//! The functions free memory and close input and output file
//!
//! @param [in] buffer                   buffer
//! @param [in] onegin_input             input file
//! @param [in] onegin_output            output file
//------------------------------------------------------------------------------------
void ExitProgramm (struct sorting* buffer, FILE* onegin_input, FILE* onegin_output);


//------------------------------------------------------------------------------------
//! The function sorts strings from the end (by rhymes)
//!
//! @param [in]  str1                     first string
//! @param [in]  str2                     second string
//!
//! @return the difference between the lines
//------------------------------------------------------------------------------------
int StrRevCmp (const char* str1, const char* str2);

struct sorting {char** ptr; char* book;};

#endif // ONEGIN_H_INCLUDED
