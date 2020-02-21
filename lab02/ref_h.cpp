// 1.
long  glob;
float fglob;

// 2. OKAY
long& fr()
{
    return glob;
}

// 3. Elveszik a lokális
int& fifi()
{
    int a;
    return a;
}

// 4. Elveszik a lokális
int *fp()
{
    int a;
    return &a;
}

// 5. OKAY
long& fr(long& a, char c)
{
    return a;
}

// 6. Érték szerint adunk, azaz lokális lesz, elveszik
long& fr(long x)
{
    return x;
}


// 7. Bemnetek variációja adhat overloadot --> előzőtől nem különbözik!
/* float& fr(long x)
{
    return fglob;
}*/

// 8. Rossz helyen a default paraméter
/*float szg(int a = 1, float x)
{
    return a * x;
}*/

#include <iostream>
using namespace std;

// 9.
int main()
{
    fr()++; //szemetet növelünk
    cout << fr() << endl;
    fr() = 54;
    cout << fr() << endl;
    fr() = fr() + 4;
    cout << fr() << endl;
    return 0;
}
