/*

brainmelt interpreter
Version 1.0.3

Command list:
```
@: Output the value of the current address
$: Input standard input 1 byte at a time to the current address
+: Increase the value of the memory address by 1
-: Decrease the value of the memory address by 1
*: Shift the address value once to the left
/: Shift the address value once to the right
?: Divide the address value by the value of the previous address and get the remainder
>: Increase the address position by 1
<: Decrease the address position by 1
[: If it is equal to 0, move to the end of the corresponding `]`
]: Move to the end of the corresponding `[`
^: Set the value of the current address to the result of ANDing the value of the previous address
%: Set the value of the current address to the result of ORing the value of the previous address
!: NOT the value of the current address
#: Call from the current address
=: Indicates the end of the program
```

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 33554432

int memory[MEMORY_SIZE] = {0};
int *ptr = memory;
FILE *file;

#define MAX_CALL_STACK 8388608
int *call_stack[MAX_CALL_STACK];
int stack_pointer = 0;

void help() 
{

    printf("brainmelt HELP\n");
    printf("usage:\n");
    printf("    bi [input.bms]\n");
    printf("\nbrainmelt interpreter version 1.0.3\n");

}

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
    
        help();
        return 0;
    
    }

    file = fopen(argv[1], "r");
    if (!file)
    {
    
        printf("failed to open file.\n");
        return 1;
    
    }

    int chr;
    while ((chr = fgetc(file)) != EOF)
    {
    
        switch (chr)
        {
        
            case '@':
                putchar(*ptr);
                break;
            case '$':
                *ptr = getchar();
                break;
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
            case '*':
                *ptr <<= 1;
                break;
            case '/':
                *ptr >>= 1;
                break;
            case '?':
                *ptr = *ptr % *(ptr - 1);
                break;
            case '>':
                ptr++;
                //if (ptr >= memory + MEMORY_SIZE) ptr = memory;
                break;
            case '<':
                ptr--;
                //if (ptr < memory) ptr = memory + MEMORY_SIZE - 1;
                break;
            case '[':
                if (*ptr == 0)
                {
            
                    int loop = 1;
                    while (loop > 0)
                    {
                    
                        chr = fgetc(file);
                        if (chr == '[') loop++;
                        else if (chr == ']') loop--;
                    
                    }
                
                }
                break;
            case ']':
                if (*ptr != 0)
                {
                
                    int loop = 1;
                    while (loop > 0)
                    {
                    
                        fseek(file, -2, SEEK_CUR);
                        chr = fgetc(file);
                        if (chr == ']') loop++;
                        else if (chr == '[') loop--;
                    
                    }
                
                }
                break;
            case '^':
                *ptr = *ptr & *(ptr - 1);
                break;
            case '%':
                *ptr = *ptr | *(ptr - 1);
                break;
            case '!':
                *ptr = ~(*ptr);
                break;
            case '#':
                if (stack_pointer < MAX_CALL_STACK)
                {
                
                    call_stack[stack_pointer++] = ptr;
                    ptr = memory + *ptr;
                
                } else
                {
                
                    printf("Call stack overflow\n");
                
                }
                break;
            case '=':
                fclose(file);
                return 0;
        
        }
    
    }

}
