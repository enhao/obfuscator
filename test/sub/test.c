#include <stdio.h>

int main(int argc, char** argv)
{
    int a = 3;
    int b = 5;
    int c = 7;

    a = b + c;
    printf("%d = %d + %d\n", a, b, c);
    
    b = c - a;
    printf("%d = %d - %d\n", b, c, a);
    
    c = a & b;
    printf("%d = %d & %d\n", c, a, b);
    
    a = b | c;
    printf("%d = %d | %d\n", a, b, c);
    
    b = c ^ a;
    printf("%d = %d ^ %d\n", b, c, a);

    return 0;
}

