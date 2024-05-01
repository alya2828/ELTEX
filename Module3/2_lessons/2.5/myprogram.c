#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE *file = fopen("file.txt", "a");
    if (file == NULL){
    	printf("no file\n");
    	return 0;
    }
    int counter = 1;
    while (1)
    {
        fprintf(file, "%d\n", counter);
        fflush(file);
        counter++;
        sleep(1);
    }
    return 0;
}
