#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"

int main(void)
{
    FILE *fp = fopen("txt.cpp", "r");

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
        printf("At 0x%p (src)\n", src);
        fclose(fp);
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        ch = fgetc(fp);
        src[i] = ch;
    }

    src[len] = 0;

    printf("Choose your decision:\n");
    printf("1: Camel to snake\n");
    printf("2: Snake to camel\n");
    printf("Choose: ");
    int d = 0;
    scanf("%d", &d);

    char *dest = malloc(2 * len + 1);

    if (!dest) {
        printf("!!! Bad Alloc !!!\n");
        printf("At 0x%p (dest)\n", dest);
        free(src);
        fclose(fp);
        exit(1);
    }

    if (d == 1) 
        camel_to_snake(dest, src);
    else if (d == 2)
        snake_to_camel(dest, src);
    else {
        free(dest);
        free(src);
        fclose(fp);
        exit(1);
    }
        

    fclose(fp);
    fp = fopen("txt.cpp", "w");

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

    free(dest);
    free(src);
    fclose(fp);
    return 0;
}