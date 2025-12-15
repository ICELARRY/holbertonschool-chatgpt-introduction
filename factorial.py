#!/usr/bin/python3
import sys

def factorial(n):
    result = 1
    # Loop to multiply all numbers from n down to 1
    while n > 1:
        result *= n
        n -= 1  # Decrease n to avoid infinite loop
    return result

Read the number from command-line argument and calculate factorial
f = factorial(int(sys.argv[1]))
print(f)
