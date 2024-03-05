#include "infiX.h"

static math_func *get_math_func(char *op_symbol);

/**
 * infiX_dealer - determine what operation to carry out based on given symbol
 * @num1: first number
 * @op_symbol: operand
 * @num2: second number
 *
 * Return: 1 on failure, 0 on success
 */
int infiX_dealer(char *num1, char *op_symbol, char *num2)
{
	mid_uint *num1_arr = NULL, *num2_arr = NULL, *ans_arr = NULL;
	lo_uchar *answer = NULL;
	math_func *func_ptr = NULL;

	if (!num1 || !op_symbol)
	{ /*Mandatory arguments missings*/
		print_help("usage");
		return (EXIT_FAILURE);
	}

	func_ptr = get_math_func(op_symbol);
	if (func_ptr)
	{
		errno = 0;
		/*Convert num1 and num2 to mid_uint arrays first*/
		num1_arr = str_to_intarray((lo_uchar *)num1);
		if (num1_arr)
			num2_arr = str_to_intarray((lo_uchar *)num2);

		if (num1_arr && num2_arr)
			ans_arr = func_ptr(num1_arr, num2_arr);
	}

	free(num1_arr);
	free(num2_arr);
	free(remain);
	if (ans_arr)
	{
		answer = intarr_to_str(ans_arr);
		if (answer)
		{
			free(ans_arr);
			printf("%s\n", (char *)answer);
			free(answer);
			return (EXIT_SUCCESS);
		}
	}

	if (!func_ptr)
		print_help("operator"); /*Symbol not found*/

	return (EXIT_FAILURE);
}

/**
 * get_math_func - return the function associated with the give operator
 * @op_symbol: the operator symbol
 *
 * Return: pointer to a function on success, NULL on failure
 */
math_func *get_math_func(char *op_symbol)
{
	int i = 0;
	op_func operators[] = {
		{"+", infiX_addition},
		{"-", infiX_subtraction},
		{"x", infiX_multiplication},
		{"/", infiX_division},
		{NULL, NULL},
	};

	for (i = 0; op_symbol && operators[i].symbol; i++)
		if (!_strcmp(operators[i].symbol, op_symbol))
			return (operators[i].f);

	return (NULL);
}
