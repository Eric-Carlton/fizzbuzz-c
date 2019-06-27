# FizzBuzz

## Description

A learning project in C. Typical FizzBuzz program that asks user for a number to count to then prints all numbers from 1 to the specified number. Prints "FIZZ" for any number divisible by 3, "BUZZ" for any number divisible by 5, and "FIZZBUZZ" for any number divisible by both 3 and 5.

## Options

| Short | Long   | Required? | Usage                                                                                                  |
|:------|:-------|:----------|:-------------------------------------------------------------------------------------------------------|
| -f    | --fizz | N         | Gives the option to change what is printed when a number divisible by 3. Must be 20 characters or less |
| -b    | --buzz | N         | Gives the option to change what is printed when a number divisible by 5. Must be 20 characters or less |

## Build

Tested with gcc 7.4.0 on Ubuntu 18.04.2: `gcc ./fizzbuzz.c -o fizzbuzz.out`

## Example usage

`./fizzbuzz.out --fizz Harley --buzz Quinn`

## License

[MIT](LICENSE)