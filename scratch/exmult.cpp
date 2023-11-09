
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <span>

template<typename T> // needs to support std::ostream& operator<<(std::ostream&, T const&)
std::ostream& operator<< (std::ostream& os, std::span<T> data)
{
    os << "{ ";
    std::string sep = "";
    for ( size_t i = 0; i < data.size(); ++i )
    {
        os << sep << data.data()[i];
        sep = ", ";
    }
    return os << " }";
}


void f(int* A, int* B, size_t N)
{
    int product = 1;
    for ( size_t i = 0; i < N; ++i )
    {
        product *= A[i];
    }
    for ( size_t i = 0; i < N; ++i )
    {
        B[i] = product / A[i];
    }
}

void f2(int* A, int* B, int N) {
    // Set prod to the neutral multiplication element
    int prod = 1;

    for (int i = 0; i < N; ++i) {
        // For element "i" set B[i] to A[0] * ... * A[i - 1]
        B[i] = prod;
        // Multiply with A[i] to set prod to A[0] * ... * A[i]
        prod *= A[i];
    }

    // Reset prod and use it for the right elements
    prod = 1;

    for (int i = N - 1; i >= 0; --i) {
        // For element "i" multiply B[i] with A[i + 1] * ... * A[N - 1]
        B[i] *= prod;
        // Multiply with A[i] to set prod to A[i] * ... * A[N - 1]
        prod *= A[i];
    }
}

void f3(int* A, int* B, int N) {
    auto a = std::span{A, (size_t)N};
    auto b = std::span{B, (size_t)N};
    std::exclusive_scan(a.begin(), a.end(), b.begin(), 1, std::multiplies{});
    std::exclusive_scan(a.rbegin(), a.rend(), a.rbegin(), 1, std::multiplies{});
    std::transform(a.begin(), a.end(), b.begin(), b.begin(), std::multiplies());
}


int main()
{
    std::cout << "hello" << std::endl;
    int A[] = { 2, 1, 5, 9 };
    size_t N = sizeof(A)/sizeof(*A);
    int B[N];

    std::cout << "A: " << std::span{A, N} << std::endl;
    f3(A, B, N);
    std::cout << "B: " << std::span{B, N} << std::endl;

    return 0;
}
