#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define MAX_DIGITS 1000
#define DIGIT_BITS 4 // 每个数字占用4位二进制位
typedef struct
{
    int digits[MAX_DIGITS];
    int len;
    int sign; // 新增一个符号位
} BigNum;
void initBigNum(BigNum *num)
{
    memset(num->digits, 0, sizeof(num->digits));
    num->len = 0;
    num->sign = 1; // 默认正数
}
void readBigNum(BigNum *num)
{
    char str[MAX_DIGITS + 2]; // 原本为 MAX_DIGITS+1，现改为 +2
    scanf("%s", str);
    int len = strlen(str);
    if (str[0] == '-')
    { // 判断符号位
        num->sign = -1;
        len--;
    }
    else
    {
        num->sign = 1;
    }
    for (int i = 0; i < len; i++)
    {
        num->digits[i] = str[len - i - 1 + (num->sign == -1)] - '0'; // 符号位需要多减1
    }
    num->len = len;
}
void printBigNum(BigNum *num)
{
    if (num->sign == -1)
    { // 判断符号位
        printf("-");
    }
    for (int i = num->len - 1; i >= 0; i--)
    { // 符号位需要多加上1
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

bool cmp(BigNum *a, BigNum *b)
{
    if (a->len > b->len)
        return true;
    else if (a->len < b->len)
        return false;
    else
    {
        for (int i = 0; i < a->len; i++)
        {
            if (a->digits[i] < b->digits[i])
                return false;
        }
        return true;
    }
}

void addBigNum(BigNum *a, BigNum *b, BigNum *c)
{
    initBigNum(c);
    if (!cmp(a, b))
    {
        BigNum *tmp = a;
        a = b;
        b = tmp;
    }

    if (a->sign == b->sign)
    { // 同号相加
        int carry = 0;
        int len = a->len > b->len ? a->len : b->len;
        for (int i = 0; i < a->len; i++)
        {
            int digit = (i >= b->len) ? 0 : b->digits[i];
            int tmp = a->digits[i] + digit + carry;
            c->digits[c->len++] = tmp % 10;
            carry = tmp / 10;
        }
        if (carry)
        {
            c->digits[c->len++] = carry;
        }
        c->sign = a->sign;
    }
    else
    { // 异号相减
        int borrow = 0;
        int len = a->len > b->len ? a->len : b->len;
        for (int i = 0; i < len; i++)
        {
            int digit = (i >= b->len) ? 0 : b->digits[i];
            int tmp = a->digits[i] - borrow - digit;
            // printf("%d - %d - %d = %d\n", a->digits[i], borrow, digit, tmp);
            if (tmp < 0)
            {
                tmp += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            c->digits[c->len++] = tmp;
        }
        while (c->len > 1 && c->digits[c->len - 1] == 0)
        { // 去掉前导0
            c->len--;
        }
        if (c->len == 1 && c->digits[0] == 0)
            c->sign = 1;
        else if (a->sign == -1)
            c->sign = -1;
        else
            c->sign = 1;
    }
}
void subtractBigNum(BigNum *a, BigNum *b, BigNum *c)
{
    initBigNum(c);
    b->sign = -b->sign; // 转化为加法
    addBigNum(a, b, c);
    b->sign = -b->sign; // 恢复符号
}
void multiplyBigNum(BigNum *a, BigNum *b, BigNum *c)
{
    initBigNum(c);
    if (cmp(a, b))
    {
        BigNum *tmp = a;
        a = b;
        b = tmp;
    }
    for (int i = 0; i < a->len; i++) // 不压位写法
    {
        BigNum carry, last = *c;
        initBigNum(&carry);
        int carrylen = i, tmp = 0;
        for (int j = 0; j < b->len; j++)
        {
            tmp += a->digits[i] * b->digits[j];
            carry.digits[carrylen++] = tmp % 10;
            tmp /= 10;
        }
        while (tmp)
            carry.digits[carrylen++] = tmp % 10, tmp /= 10;
        carry.len = carrylen;
        addBigNum(&last, &carry, c);
    }
    while (c->len > 1 && c->digits[c->len - 1] == 0)
    { // 去掉前导0
        c->len--;
    }
    c->sign = a->sign * b->sign; // 记得乘上符号位
}
int main()
{
    BigNum a, b, c, d;
    int op;
    do
    {
        printf("请选择要进行的操作：\n");
        printf("1. 加法\n");
        printf("2. 减法\n");
        printf("3. 乘法\n");
        printf("0. 退出\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("请输入两个大整数：\n");
            readBigNum(&a);
            readBigNum(&b);
            addBigNum(&a, &b, &c);
            printf("相加的结果为：\n");
            printBigNum(&c);
            break;
        case 2:
            printf("请输入两个大整数：\n");
            readBigNum(&a);
            readBigNum(&b);
            subtractBigNum(&a, &b, &c);
            printf("相减的结果为：\n");
            printBigNum(&c);
            break;
        case 3:
            printf("请输入两个大整数：\n");
            readBigNum(&a);
            readBigNum(&b);
            multiplyBigNum(&a, &b, &c);
            printf("相乘的结果为：\n");
            printBigNum(&c);
            break;
        case 0:
            break;
        default:
            printf("输入错误，请重新输入！\n");
            break;
        }
    } while (op != 0);
    return 0;
}
