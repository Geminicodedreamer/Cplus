#include <stdio.h>
#include <stdlib.h>
int AND(int a, int b)
{
    if (a == 1 && b == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int OR(int a, int b)
{
    if (a == 1 || b == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int voting_circuit(int a, int b, int c)
{
    int ab = AND(a, b);
    int bc = AND(b, c);
    int ac = AND(a, c);
    int abc = OR(OR(ab, bc), ac);
    return abc;
}

int main()
{
    int a, b, c;
    // scanf("%d%d%d", &a, &b, &c);
    for (int i = 0; i < 1 << 3; i++)
    {
        c = i & 1;
        b = i >> 1 & 1;
        a = i >> 2 & 1;
        printf("a: %d  b: %d  c: %d  ans: %d\n", a, b, c, voting_circuit(a, b, c));
    }

    system("pause");
    return 0;
}