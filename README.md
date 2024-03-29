# INFIX_MATH (tentative name)

## NOTICE

This is a personal project meant to challenge myself and just to practice
writing C projects. Therefore this program and the suite of functions
thereof are not guaranteed to be upto to production standards. Use at your
own risk.

## DESCRIPTION

This project aims to provide some functions that can be used to perform basic
calculations on arbitrary large numbers. The project is written in C and does
not use any external libraries for it's math operations.

This project was compiled using the [gcc](https://gcc.gnu.org/) compiler. Invoke
the make command in a terminal to compile the project for **debugging**:

`make`

To use the program as a simple calculator, invoke make with **release:**

`make release`

## Usage

As this is still in production not alot can be done. Currently only the basic
math operations are available. To use the program as a simple calculator type
the following command in a terminal in the directory where the executable [math](./math)
is contained.

**./math *number* *sign* *\[number\]***

Where ***sign*** is either "**+**" for addition, "**-**" for subtration,
"**x**" for multiplication "**/**" for division or "**%**" for modulus.

Calling **./math** with no arguments or incorrect arguments will cause the
program to abort and print out an error message. The program requires atleast two
arguments in order to start processing input.

## TODO

- Exponetials
- Square root
- Floating Points

## Functions

The suite of functions meant for use are summarised here. It is recommended
to interact with the functions via the [manager](src/infiX_manager.c), as it converts strings
into the correct array format required by most of the functions.

### infiX_manager

The [infiX_manager](./src/infiX_manager.c) function parses user input and calls the right
functions to perform calculations.
It is responsible for detecting errors in user input, converting numbers in
strings into arrays of numbers, calling the required function and returning
correct output.

### infiX_addition

The [infiX_addition](src/infiX_add.c) function adds two numbers stored in arrays.

### infiX_multiplication

The [infiX_multiplication](src/infiX_mul.c) function mutiplies two numbers stored in arrays.

### infiX_subtraction

The [infiX_subtraction](src/infiX_sub.c) function subtracts two numbers stored in arrays.

### infiX_division

The [infiX_division](src/infiX_div.c) function divides two numbers stored in arrays.

### panic

The [panic](src/panic.c) function prints some help text.
