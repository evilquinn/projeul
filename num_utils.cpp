

#include <utils.hpp>

void num_to_digit_array(size_t  num,
                        int*&   digit_array,
                        size_t& digit_array_length)
{
    digit_array_length = num_digits(num);
    digit_array = new int[digit_array_length];
    for(int i = digit_array_length - 1; i >= 0; --i)
    {
        digit_array[i] = num % 10;
        num /= 10;
    }
}

void add_to_digit_array(int* add_to, size_t add_to_len, size_t add)
{
    int add_to_pos = add_to_len - 1;

    while(add>0)
    {
        if(add_to_pos >= 0)
        {
            add_to[add_to_pos] += add % 10;

            size_t carry_on_pos = add_to_pos;
            while(add_to[carry_on_pos] >= 10)
            {
                add_to[carry_on_pos] %= 10;
                if(carry_on_pos > 0)
                {
                    --carry_on_pos;
                    ++add_to[carry_on_pos];
                }
                else
                {
                    // no more array to carry on with
                    break;
                }
            }
            --add_to_pos;
            add /= 10;
        }
        else
        {
            break;
        }
    }
}


void add_digit_arrays(int* add_to, size_t add_to_len, int* add, size_t add_len)
{

    int add_pos = add_len - 1;
    int add_to_pos = add_to_len - 1;

    while(add_pos >= 0)
    {
        if(add_to_pos >= 0)
        {
            add_to[add_to_pos] += add[add_pos];

            size_t carry_on_pos = add_to_pos;
            while(add_to[carry_on_pos] >= 10)
            {
                add_to[carry_on_pos] %= 10;
                if(carry_on_pos > 0)
                {
                    --carry_on_pos;
                    ++add_to[carry_on_pos];
                }
                else
                {
                    // no more array to carry on with
                    break;
                }
            }
            --add_to_pos;
            --add_pos;
        }
        else
        {
            // no array to add to, finished
            break;
        }
    }
}


