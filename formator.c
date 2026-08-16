#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"

void usage()
{
    printf(
        "Usage: formator [OPTION] [FILE]\n"
        "OPTION:\n"
        "\t-s    Camel to snake\n"
        "\t-c    Snake to camel\n"
    );
}

int main(int argc, const char **args)
{
    int o = 0;
    if (argc == 3 && args[1][0] == '-' && args[1][1] == 's') {
        o = 1;
    } else if (argc == 3 && args[1][0] == '-' && args[1][1] == 'c') {
        o = 2;
    } else {
        usage();
        return 0;
    }

    FILE *fp = fopen(args[2], "r");

    if (!fp) {
        printf("No such file!\n");
        exit(1);
    }

    printf("Calculating file size...\n");
    int len = 0;
    int ch = 0;

    while ((ch = fgetc(fp)) != EOF) {
        len++;
    }

    rewind(fp);

    printf("Reading file...\n");
    char *src = malloc(len + 1);
    
    if (!src) {
        printf("!!! Bad Alloc !!!\n");
        printf("At 0x%llX (src)\n", (unsigned long long)src);
        fclose(fp);
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        ch = fgetc(fp);
        src[i] = ch;
    }

    src[len] = 0;

    char *dest = malloc(2 * len + 1);

    if (!dest) {
        printf("!!! Bad Alloc !!!\n");
        printf("At 0x%llX (dest)\n", (unsigned long long)dest);
        free(src);
        fclose(fp);
        exit(1);
    }

    if (o == 1) 
        camel_to_snake(dest, src);
    else if (o == 2)
        snake_to_camel(dest, src);
    else {
        free(dest);
        free(src);
        fclose(fp);
        exit(1);
    }
        

    fclose(fp);
    fp = fopen(args[2], "w");

    if (!fp) {
        printf("Error when doing output!\n");
        free(dest);
        free(src);
        exit(1);
    }
    
    char *p = dest;
    while (*p) {
        fputc(*p, fp);
        p++;
    }

    printf("Done!\n");

    free(dest);
    free(src);
    fclose(fp);
    return 0;
}
