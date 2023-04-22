#include "bo2-2.c"
#include "c1.h"
#include "C2-2.H"
#include <stdio.h>
#include <stdlib.h>

void visit(ElemType c)
{
    printf("%lf %lf\n", c.real, c.imag);
}

double AbsComplex(ElemType z)
{
    double n = 0;
    n = sqrt(pow(z.real, 2) + pow(z.imag, 2));
    return n;
}

void BuddleSort(LinkList *L)
{
    int i = 0, count = 0, num;
    LinkList p, q, tail;
    InitList(&p);
    InitList(&q);
    InitList(&tail);
    p = *L;
    while (p->next != NULL)
    {
        count++;
        p = p->next;
    }
    for (; i < count - 1; i++)
    {
        num = count - i - 1;
        q = (*L)->next;
        tail = *L;
        while (num--)
        {
            if (AbsComplex(q->data) > AbsComplex(p->data))
            {
                q->next = p->next;
                p->next = q;
                tail->next = p;
            }
            tail = tail->next;
            q = tail->next;
            p = q->next;
        }
    }
}

void main()
{
    LinkList La;
    ElemType e;
    int i, j, k, lenth, tem;
    ElemType scan;
    InitList(&La);
    printf("pls input 6 complex number:\n");
    for (i = 0; i < 6; i++)
    {
        scanf("%lf %lf", &scan.real, &scan.imag);
        ListInsert(La, i + 1, scan);
    }
    printf("LaList Element=:\n");
    ListTraverse(La, visit);
    BubbleSort(&La);
    printf("sorted Element=:\n");
    ListTraverse(La, visit);

    system("pause");
}