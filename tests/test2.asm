int fib(int n)
{
if ((n<2)) return 1;
return (fib((n-1))+fib((n-2)));
};
int main()
{
int res = fib(10);
int id = 10;
int f[(id+1)];
(f[0]=(f[1]=1));
for (int i = 2;(i<=id);(i=(i+1))) (f[i]=(f[(i-1)]+f[(i-2)]));
return 0;
};

