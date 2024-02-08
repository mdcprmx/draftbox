#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void gen_spaces(FILE* fname_p);
void gen_LFD(FILE* fname_p);
void gen_basic(FILE* fname_p);
void test_file_new(char* arg_str_fname);

int main(int argc, char** argv)
{
    srand(time(NULL));
    while (--argc) {
        test_file_new(argv[argc]);
    }

    return 0;
}

void test_file_new(char* arg_str_fname)
{
    FILE* fname_p = fopen(arg_str_fname, "w");

    if (!strcmp(arg_str_fname, "empty"))
    {} else if (!strcmp (arg_str_fname, "LFD")) 
    {
        gen_LFD(fname_p);
    }

    else
    {
        if (rand() % 2) {
            gen_LFD(fname_p);
        }

        if (rand() % 2) {
            gen_spaces(fname_p);
        }

        gen_basic(fname_p);

        if (rand() % 2) {
            gen_LFD(fname_p);
        }

    }
    fclose(fname_p);
}

void gen_basic(FILE* fname_p)
{
    int rand_count = 256;
    while (rand_count-- )
    {
        char ch = rand() % 256;
        fwrite(&ch, sizeof(char), 1, fname_p);
    }
}

void gen_LFD(FILE* fname_p)
{
    const char probeli[] = {0x0c, 0x0a, 0x0d, 0x09, 0x0b};
    
    int counter = 4;
    while (counter --)
    {
        fwrite(probeli + 1, sizeof(char), 1, fname_p);
    }

}

void gen_spaces(FILE* fname_p)
{
    const char probeli[] = {0x0c, 0x0a, 0x0d, 0x09, 0x0b};
    
    int count = 16;
    while (count --)
    {
        fwrite(probeli + (rand() % sizeof(probeli)), sizeof(char), 1, fname_p);
    }
}

