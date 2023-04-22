#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
const int N = 10000;
const int TIME = 1000;
int main()
{
    for(int T = 1 ; T <= N ; T ++)
    {
        system("C:\\randoom.exe");
        double st = clock();
        system("C:\\icpc.exe");
        double ed = clock();
        system("C:\\helloworld.exe");
        if(system("fc C:\\data.out C:\\data.ans"))
        {
            puts("WA");
            return 0;
        }
        else if(ed - st >= TIME)
        {
            puts("TLE");
            return 0;
        }
        else 
            printf("AC Test #%d : Time %.0lf ms\n",T , ed - st); 
    }
}