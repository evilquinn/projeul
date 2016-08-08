
#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <stddef.h>
#include <vector>
#include <map>
#include <set>

class prime_sieve;

/*
 * counts the number of digits in a number
 * @param n  The number to count the digits of
 * @return   The number of digits in supplied n
 */
int num_digits(long long unsigned n);

/*
 * returns a set containing each digit in the number supplied
 * @param n The number to get digits off
 * @param digits The set will contain the digits
 */
typedef std::set<short> digit_set_t;
void set_of_digits(size_t n, digit_set_t& digits);

/*
 * returns true is two nums have same digits, false otherwise
 */
bool same_digits(size_t lhs, size_t rhs);
bool same_digits_old(size_t lhs, size_t rhs);

/*
 * returns the factorial of the supplied number
 */
size_t factorial(size_t n);

/*
 * calculate the n_conbinations_r value for supplied n and r
 */
size_t n_c_r(size_t n, size_t r);


/*
 * performs digit pattern analysing.  Returns a map containing a count for each
 * digit encountered, and a map containing an value representing the pattern
 * of each digit encountered, e.g.
 *   12123 =>
 *     digit_count => { 1 => 2, 2 => 2, 3 => 1 }
 *     digit_pattern => { 1=> 10100, 2 => 1010, 3 => 1 }
 *
 * @param digit_count map will contain the count for each digit
 * @param digit_pattern map will contain the pattern for each digit
 * @return distinct number of digits
 */
typedef std::map<short, size_t> digit_pattern_map_t;
typedef std::map<short, short> digit_count_map_t;
size_t pattern_of_digits(size_t num,
                         digit_count_map_t& digit_count,
                         digit_pattern_map_t& digit_pattern);

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
bool is_pandigital_for_range(size_t start,
                             size_t end,
                             size_t* ints,
                             size_t ints_size);

/*
 * determines largest prime number which is less that supplied number
 *
 * @param i number for which to determine the largest preceding prime number
 * @param primes ref to a prime_sieve
 *
 * @return largest prime number which is less than i, or 0 if i <=2
 */
size_t prev_prime(size_t i, prime_sieve& primes);

/*
 * determines smallest prime number which is greater than supplied number
 *
 * @param i number for which to determine the smallest subsequent prime number
 * @param primes ref to a prime_sieve
 *
 * @return smallest prime number greater than i or 0 if i >= primes.max
 */
size_t next_prime(size_t i, prime_sieve& primes);

/*
 * calculates the prime factors for a number and prints result to std::cout
 *
 * @param num the number to prime factorise
 * @param primes a prime sieve
 *
 */
size_t calc_prime_factors(size_t num,
                          std::vector<size_t>& prime_factors,
                          prime_sieve& primes);

/*
 * return a digit array representing the supplied number
 *
 * @param num The number
 * @param digit_array upon return will point to array of digits for num
 * @param digit_array_length upon return will be set to length of digit array
 */
void num_to_digit_array(size_t  num,
                        int*&   digit_array,
                        size_t& digit_array_length);

/*
 * Adds supplied number to the digit array
 */
void add_to_digit_array(int* add_to, size_t add_to_len, size_t add);

/*
 * Add two digit arrays (numbers, in the form of an array, where each element
 * represents each digit of the number) together, returning the result in the
 * add_to digit array
 *
 * @param add_to     The digit array to add to, where the result will be stored
 * @param add_to_len The length of the digit array to add to
 * @param add        The digit array to add
 * @param add_len    The length of the digit array to add
 */
void add_digit_arrays(int* add_to, size_t add_to_len, int* add, size_t add_len);

/*
 * Multiplies the digit array by supplied number, result in digit array
 */
void mult_digit_array_by(int* mult, size_t mult_len, size_t mult_by);


#endif // UTILS_HPP_
