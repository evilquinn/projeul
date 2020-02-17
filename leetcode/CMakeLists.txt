
add_executable ( 001_two_sum 001_two_sum.cpp )
add_executable ( 002_add_two_numbers 002_add_two_numbers.cpp )
add_executable ( 003_longest_substring_without_repeating_characters
                 003_longest_substring_without_repeating_characters.cpp )
add_executable ( 004_median_sorted_arrays 004_median_sorted_arrays.cpp )
add_executable ( 005_longest_palindromic_substring 005_longest_palindromic_substring.cpp )
add_executable ( 006_zigzag_conversion 006_zigzag_conversion.cpp )
add_executable ( 007_reverse_integer 007_reverse_integer.cpp )
target_link_libraries( 007_reverse_integer boost )
add_executable ( 008_string_to_integer_atoi 008_string_to_integer_atoi.cpp )
#target_compile_options( 008_string_to_integer_atoi PRIVATE "-ftrapv" )
add_executable ( 009_palindrome_number 009_palindrome_number.cpp )
add_executable ( 010_regular_expression_matching 010_regular_expression_matching.cpp )
