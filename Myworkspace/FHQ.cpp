/*
1、构造新节点。
v：创建的新节点的权值
返回值：创建节点的编号
*/
int newnode(int v)
{
    tr[++idx].val = v;
    tr[idx].key = rand();
    tr[idx].size = 1;
    return idx;
}

/*
2、向上更新父亲节点的树的大小。
*/
void pushup(int u)
{
    tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + 1;
}

/*
3、分裂以u为树根的树，x指向左根，y指向右根。
u：当前节点
v：传入的数值
x：指向左Treap的根
y：指向右Treap的根
*/
void split(int u, int v, int &x, int &y)
{
    if (!u)
    {
        x = 0, y = 0;
        return;
    }
    if (tr[u].val <= v)
    {
        x = u;
        split(tr[u].r, v, tr[u].r, y);
    }
    else
    {
        y = u;
        split(tr[u].l, v, x, tr[u].l);
    }
    pushup(u);
}

/*
4、将以x为左根，y为右根的两棵树合并成一棵。
x 左Treap的根
y 右Treap的根
返回值：合并之后的新树根
*/
int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (tr[x].key <= tr[y].key)
    {
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}

/*
5、插入一个权值为 v 的点。
*/
void insert(int v)
{
    int x, y, z;
    split(root, v, x, y);
    z = newnode(v);
    root = merge(merge(x, z), y);
}

/*
6、删除权值为 v 的点。
*/
void del(int v)
{
    int x, y, z;
    split(root, v, x, z);
    split(x, v - 1, x, y);
    y = merge(tr[y].l, tr[y].r);
    root = merge(merge(x, y), z);
}

/**
7、返回第 k 个节点。
p 当前节点编号
k 返回第k个节点
返回值：第k个节点的编号。
*/
int get_k(int p, int k)
{
    if (k <= tr[tr[p].l].size)
        return get_k(tr[p].l, k);
    if (k == tr[tr[p].l].size + 1)
        return p;
    return get_k(tr[p].r, k - tr[tr[p].l].size + 1);
}

/*
9、找到 v 的前驱的值。
*/
void get_pre(int v)
{
    int x, y;
    split(root, v - 1, x, y);
    int p = get_k(x, tr[x].size());
    printf("%d\n", tr[p].val);
    root = merge(x, y);
}

/*
9、找到 v 的后继的值。
*/
void get_suc(int v)
{
    int x, y;
    split(root, v, x, y);
    int p = get_k(y, 1);
    printf("%d\n", tr[p].val);
    root = merge(x, y);
}

/*
获取权值为 v 的点在树中的排名。
*/
void get_rank(int v)
{
    int x, y;
    split(root, v - 1, x, y);
    printf("%d\n", tr[x].size + 1);
    root = merge(x.y);
}

/*
获取排名为 k 的点的权值。
*/
void get_val(int k)
{
    int p = get_k(root, k);
    printf("%d\n", tr[p].val);
}

int main()
{

    system("pause");
    return 0;
}