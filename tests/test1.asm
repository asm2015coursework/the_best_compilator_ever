int write(int fd, char* buf, int count)
{
asm {
mov rax, 4
xor rbx, rbx
xor rdx, rdx
mov ebx, dword[rsb + 8]
mov rcx, qword[rsb + 12]
mov edx, dword[rsb + 20]
syscall
};
return;
};
struct lol {
int x;
int y;
void f()
{
return;
}
int xex(int x, int y)
{
return (x+y);
}
}
;
struct lol2 {
lol x;
}
;
int main()
{
int a[333];
int b[((a[2]+(a[32]/a[2]))+123)];
write(b[b[b[b[2]]]], "kek", (b[222]+a[b[2]]));
while (((a[1]+a[2])!=0)) {
if (((a[1]+a[2])==123)) break; else continue;
continue;
};
lol* LOL;
(LOL)->xex(1, 2);
((*LOL)).xex(3, 4);
((((*LOL)).x)+(((*LOL)).x));
((LOL)->y);
lol2 LOL2;
((((LOL2).x)).x);
};

