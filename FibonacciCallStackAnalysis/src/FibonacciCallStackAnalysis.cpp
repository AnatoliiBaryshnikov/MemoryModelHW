// FibonacciCallStackAnalysis.cpp
// n   1 2 3 4 5 6 7 8  9  10 11
// fib 0 1 1 2 3 5 8 13 21 34 55

#include <iostream>

long get_fib_recursion(long n);
long get_fib_iterative(long n);

int main()
{
  const long fib_n_number = 7;
  std::cout << get_fib_recursion(fib_n_number) << std::endl;
  std::cout << get_fib_iterative(fib_n_number) << std::endl;
}

long get_fib_recursion(long n)
  {
  if (n == 1)
    return 0;

  if (n == 2)
    return 1;

  return get_fib_recursion(n - 1) + get_fib_recursion(n - 2);
  }

long get_fib_iterative(long n)
  {
  if (n == 1)
    return 0;

  if (n == 2)
    return 1;

  long n_1 = 1; // n-1
  long n_2 = 0; // n-2
  long fib = 0;
  for (size_t i = 2; i < n; i++)
    {
    fib = n_1 + n_2;
    n_2 = n_1;
    n_1 = fib;
    }

  return fib;
  }
