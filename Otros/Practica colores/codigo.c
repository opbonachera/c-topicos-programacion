#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned char arr[3] = {0xFF, 0x32, 0x99};

    for(int i = 0; i < 3 ; i++)
    {
        printf("Positive: %x\n", arr[i]);// 1111 1111 for 0xff 0000 0000
        printf("Negative: %x\n", (unsigned char)~arr[i]); // 0011 0010 for 0x32 1100 1101

        printf("Moved by two: %x \n", arr[1] >> 2);
    }
    return 0;
}
