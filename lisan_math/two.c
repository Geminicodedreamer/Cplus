#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
int main()
{
    bool A, B, x;
    // A或B盗窃了x
    int theft = OR(A, B);
    // 若A盗窃了x，则作案时间不能发生在午夜前
    int time1 = !A;
    // 若B证词正确，则在午夜时屋里灯光未灭
    int light1 = B;
    // 若B证词不正确，则作案时间发生在午夜前
    int time2 = !B;
    // 午夜时屋里灯光灭了
    int light2 = false;
    // A盗窃了x作为结论
    int conclusion = A;
    // 复合命题
    bool compound = OR(AND(AND(theft, time1), AND(light1, light2)), AND(AND(theft, time2), !light2));
    // 判断结论
    printf("%d\n", compound);
    system("pause");
    return 0;
}
