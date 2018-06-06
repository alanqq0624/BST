#include <iostream>
using namespace std;
void out(int a, int b)
{
    cout << a << endl
         << b << endl;
}

int power(int base, int power)
{
    int ans = 1;
    for (int i = 0; i < power; i++)
        ans *= base;
    return ans;
}

int power_sp(int n)
{
    int ans = 1;
    power(2, n - 1);
    return --ans;
}

int main()
{
    int in = 3;
    out(++in, 2 * (in - 1) - 1);
    cout << in <<endl << string(in, '_') <<endl;
    cout << power_sp(in);
}