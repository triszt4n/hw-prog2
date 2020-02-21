void ff(const int *ip) {
    //*ip = 3;
}

int main()
{
// 1. uninitialized, invalid
    //const int i;

// 2. Can't increment
    const int j = 10;
    //j++;

// 3. Can't pass pointer of constant to pointer of variable
    const int l = 10;
    //int *p=&l;
    //(*p)++;

// 4. Function can't accept pointer of constant, needs pointer of variable
    extern void f(int *i);
    const int iv = 100;
    //f(&iv);

// 5. Value is secured, function's first line is invalid
    const int ivv = 100;
    ff(&ivv);

// 6. Value is secured
    const int v[] = {1,2,3};
    //v[1]++;

// 7. OKAY
    const int siz = 20;
    int t[siz];

// 8. Value is secured, last line is valid
    char s1[] = "Hello konstans szoveg";
    const char *pc = s1;
    //pc[0] = 'A';
    pc++;

// 9. only last line is invalid
    char s2[] = "Hello konstans pointer";
    char* const cp = s2;
    cp[0] = 'B';
    //cp++;

// 10. Value is secured, Pointer is secured
    char s3[] = "Hello konstans szoveg konstans pointer";
    const char* const cpc = s3;
    //cpc[0] = 'C';
    //cpc++;

// 11. adu is Szinek, can't pass integer + Szinek overflown
    enum Szinek { tok, zold, makk, piros };
    Szinek adu;
    //adu = 1;
    adu = Szinek(10);

    return(0);
}
