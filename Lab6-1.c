#include <stdio.h>

 
int main()
{
    char fileName[30];
    printf("Specify file name you would like to print to: \n");
    scanf("%s",fileName);

    FILE* file1 = fopen(fileName, "a+");

    char c;
    while ((c=getchar()) != EOF)
    {
        fprintf(file1,"%c\n",c);
    }
 
    fclose(file1);
 
    printf("CTRL+d is a correct ending");
 
    return 0;
}
