#include <iostream>
int num_digits( unsigned n )
{
    unsigned num_digits = 0;
    while ( n > 0 )
    {
        ++num_digits;
        n /= 10;
    }
    return num_digits;
}
int select_digit( int n, int index )
{
    int chosen_one = 0;
    int num_digs   = num_digits( n );
    if ( index < 0 || index >= num_digs )
    {
        return -1;
    }
    while ( num_digs - 1 > index )
    {
        n /= 10;
        --num_digs;
    }
    chosen_one = n % 10;
    return chosen_one;
}
int main( int argc, char* argv[] )
{
    /*
     */
    int result       = 1;
    int d            = 1;
    unsigned n       = 1;
    bool done1       = false;
    bool done10      = false;
    bool done100     = false;
    bool done1000    = false;
    bool done10000   = false;
    bool done100000  = false;
    bool done1000000 = false;
    while ( !done1 || !done10 || !done100 || !done1000 || !done10000 ||
            !done100000 || !done1000000 )
    {
        unsigned numd = num_digits( n );
        if ( !done1 && d >= 1 )
        {
            result *= select_digit( n, d == 1 ? 0 : numd - ( d - 1 ) );
            done1 = true;
        }
        if ( !done10 && d >= 10 )
        {
            result *= select_digit( n, d == 10 ? 0 : numd - ( d - 10 ) );
            done10 = true;
        }
        if ( !done100 && d >= 100 )
        {
            result *= select_digit( n, d == 100 ? 0 : numd - ( d - 100 ) );
            done100 = true;
        }
        if ( !done1000 && d >= 1000 )
        {
            result *= select_digit( n, d == 1000 ? 0 : numd - ( d - 1000 ) );
            done1000 = true;
        }
        if ( !done10000 && d >= 10000 )
        {
            result *=
                select_digit( n, d == 10000 ? 0 : numd - ( d - 10000 ) );
            done10000 = true;
        }
        if ( !done100000 && d >= 100000 )
        {
            result *=
                select_digit( n, d == 100000 ? 0 : numd - ( d - 100000 ) );
            done100000 = true;
        }
        if ( !done1000000 && d >= 1000000 )
        {
            result *=
                select_digit( n, d == 1000000 ? 0 : numd - ( d - 1000000 ) );
            done1000000 = true;
        }

        d += numd;
        ++n;
    }

    std::cout << "PE40 " << result << std::endl;

    return 0;
}
