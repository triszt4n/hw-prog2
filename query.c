#include <stdio.h>

char myid[]   = "Ga'z Ge'za,1MI,1,H1g <en@com.hu> XY123Z\n";
char mytask[] = "Feladat = ## ISO 8859-2\n";

int main(int argc, char* argv[])
{
    if (argc > 1) {
        int n = atoi(argv[1]);
        mytask[10] = (n < 10)? ' ' : argv[1][0];
        mytask[11] = (n < 10)? argv[1][0] : argv[1][1];
    }
    setbuf(stdout, NULL);
    printf(myid);
    printf(mytask);
    printf("Mail\n");
    return 0;
}
