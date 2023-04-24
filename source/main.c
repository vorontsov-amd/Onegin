///\file
///\brief main file on the program sorts the lines in the file

/*! \mainpage
* The program sorts the lines in the file in direct order and from the end of the lines, and also throws out garbage lines
* autor: Vorontov Amadey
*/

#include "onegin.h"

int main (int argc, char** argv)
{
    if (argc != 3)
    {
        puts ("Wrong number of arguments");
        exit (0);
    }
    
    FILE* onegin_input = OpenFile (argv[1]);

    unsigned int number_of_characters = 0, number_of_lines = 0;

    TextParametrs (onegin_input, &number_of_characters, &number_of_lines);

    struct sorting* buffer = CreateBuffer (number_of_lines, number_of_characters);

    FullBuffer (onegin_input, buffer);

    Sorting (buffer->ptr, number_of_lines, StrCmp);

    FILE* onegin_output = CloseFile (argv[2]);

    fputs ("Sortint file:\n", onegin_output);

    Output (buffer->ptr, onegin_output, number_of_lines);

    Sorting (buffer->ptr, number_of_lines, StrRevCmp);

    fputs ("\nReverse sorting file:\n\n", onegin_output);

    Output (buffer->ptr, onegin_output, number_of_lines);

    ExitProgramm (buffer, onegin_input, onegin_output);

    return 0;
}

FILE* OpenFile (const char* filename)
{
    assert (filename);

    FILE* onegin_input = fopen (filename, "a+");

    if (!onegin_input)
        {
        puts ("Cannot open input file!");
        exit(EXIT_FAILURE);
        }

    return onegin_input;
}

void TextParametrs (FILE* onegin_input, unsigned int* number_of_characters, unsigned int* number_of_lines)
{
    assert (onegin_input);
    assert (number_of_characters);
    assert (number_of_lines);

    int ch = '\0';

    if ((ch = getc(onegin_input)) != EOF)
        {
        (*number_of_lines) = 1;
        rewind (onegin_input);
        }
    while ((ch = getc(onegin_input)) != EOF)
        {
        (*number_of_characters)++;
        if (ch == '\n')
            {
            (*number_of_lines)++;
            }
        }
}

struct sorting* CreateBuffer (natural MAXLENGTH_PTR, natural LENGTH_FILE)
{
    static struct sorting buffer =
        {.ptr = (char**) calloc (MAXLENGTH_PTR, sizeof(char*)),
         .book = (char*) calloc (LENGTH_FILE + MAXLENGTH_PTR, sizeof(char))};

    if (buffer.ptr == NULL || buffer.book == NULL)
        {
        puts ("Cannot create sorting buffer");
        exit(EXIT_FAILURE);
        }

    return &buffer;
}


void FullBuffer (FILE* file, struct sorting* buffer)
{
    assert (file);
    assert (buffer);

    rewind(file);

    int ch = 0, i = 0, k = 1;

    while ((ch = getc(file)) != EOF)
        {
        if (ch != '\n')
            {
             buffer->book[i++] = (char) ch;
            }
        else
            {
            i++;
            buffer->book[i++] = (char) ch;
            buffer->ptr[k++] = &buffer->book[i];
            }
        }
    buffer->ptr[0] = &buffer->book[0];
}


void Sorting (char** index, natural number_of_lines, int (*Compare) (const char*, const char*))
{
    assert (index);
    for (unsigned int nPass = 0; nPass < number_of_lines - 1; nPass++)
        for (unsigned int i = 0; i < number_of_lines - 1; i++)
            if (Compare(index[i], index[i+1]) > 0)
                {
                char* exchange = index[i];
                index[i] = index[i+1];
                index[i+1] = exchange;
                }
}


int StrCmp (const char* str1, const char* str2)
{
    assert (str1);
    assert (str2);

    char garbage[] = ",`'\"     <!?-^:;>.()";

    int i = 0, j = 0;
    while (true)
        {
        if (strchr(garbage, str1[i]) != NULL)
            {
            i++;
            continue;
            }
        if (strchr(garbage, str2[j]) != NULL)
            {
            j++;
            continue;
            }
        if (str1[i] != str2[j]) break;
        if (str1[i] == '\0') break;
        i++; j++;
        }
    return (str1[i] - str2[j]);
}

int StrRevCmp (const char* str1, const char* str2)
{
    assert (str1);
    assert (str2);

    char garbage[] = ",`'\"     <!?-^;:>.()";

    int i = strlen(str1) - 1, j = strlen(str2) - 1;
    while (i > 0 && j > 0)
        {
        if (strchr(garbage, str1[i]) != NULL)
            {
            i--;
            continue;
            }
        if (strchr(garbage, str2[j]) != NULL)
            {
            j--;
            continue;
            }
        if (str1[i] != str2[j]) break;
        i--; j--;
        }
    return (str1[i] - str2[j]);
}



FILE* CloseFile (const char* filename)
{
    assert (filename);

    FILE* onegin_output = fopen (filename, "w");

    if (!onegin_output)
        {
        puts ("Cannot open output file");
        exit(EXIT_FAILURE);
        }

    return onegin_output;
}


void Output (char** book, FILE* output, natural number_of_lines)
{
    assert (book);
    assert (output);

    char garbage[] = "LXIV,.     1234567890()<>-{}";
    int nGarbage[number_of_lines];

    for (unsigned int stroka = 0; stroka < number_of_lines; stroka++)
        {
        nGarbage[stroka] = 0;
        for (unsigned int i = 0; book[stroka][i] != '\0'; i++)
            if (strchr(garbage, book[stroka][i]) == NULL)
                {
                nGarbage[stroka]++;
                }
        if (nGarbage[stroka] > 0)
            {
            fputs (book[stroka], output);
            putc ('\n', output);
            }
        }
}



void ExitProgramm (struct sorting* buffer, FILE* onegin_input, FILE* onegin_output)
{
    assert (buffer);
    assert (onegin_input);
    assert (onegin_output);

    free (buffer->ptr);
    free (buffer->book);

    fclose (onegin_input);
    fclose (onegin_output);
}
