#include "misc.h"

int isPalindrome(const char* s1, const char* s2)
{
    s2 = s2 + strlen(s2) - 1;

    while(*s1 != '\0' && s2 >= s1)
    {
        if(*s1 !=  *s2)
            return -1;

        s1++;
        s2--;

    }

    return 1;
}
