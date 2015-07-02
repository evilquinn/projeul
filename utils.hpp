
#ifndef UTILS_HPP_
#define UTILS_HPP_

/*
 * counts the number of digits in a number
 * @param n  The number to count the digits of
 * @return   The number of digits in supplied n
 */
int num_digits(long long unsigned n);

/*
 * counts the number of digits in an array of numbers
 * e.g. returns foreach(int i, ints) total+=num_digits(i);
 *
 * @param int    s  The number array to count the digits of
 * @param ints_size The number of numbers in the array
 * @return   The number of digits in supplied array
 */
int num_digits_array(long long unsigned* ints, int ints_size);

/*
 * determines if the concatenation of the ints in the supplied array is
 * pandigital for the supplied range
 * i.e. the concatenated number contains every digit in the supplied range
 *      exactly once.
 * e.g. is_pandigital_for_range(1, 3, {12, 3}, 2) == true
 *      is_pandigital_for_range(1, 4, {12, 3}, 2) == false
 *
 * @param start The beginning number of the range
 * @param end   The final number of the range
 * @param ints  The array of integers to concatenate and test
 * @param ints_size The number of ints in the array
 *
 * @return      TRUE if the concatenation of the ints in the array is
 *              pandigital for the supplied range, FALSE otherwise.
 */
bool is_pandigital_for_range(int start, int end, size_t* ints, int ints_size);


#endif // UTILS_HPP_
