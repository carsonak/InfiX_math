#include "infiX.h"

/**
 * infiX_op - a wrapper function for the infiX_math functions
 * @num1: first number
 * @sign: operand
 * @num2: second number
 *
 * Return: 1 on failure, 0 on success
 */
int infiX_op(char *num1, char *sign, char *num2)
{
	int i = 0;
	mid_uint *num1_arr = NULL, *num2_arr = NULL, *ans_arr = NULL;
	lo_uchar *answer = NULL;
	op_func operators[] = {
		{"+", infiX_add},
		{"-", infiX_sub},
		{"x", infiX_mul},
		{"/", infiX_div},
		{NULL, NULL},
	};

	if (!num1 || !num2 || !sign)
	{
		print_help();
		return (EXIT_FAILURE);
	}

	for (i = 0; operators[i].sign; i++)
	{
		if (operators[i].sign[0] == sign[0])
		{
			/**
			 * Send num1 and num2 to the converters first
			 * Offset pointers by number of leading zeros
			 */
			num1_arr = str_to_intarray((lo_uchar *)&num1[pad_char(num1, "0")]);
			if (!num1_arr)
				break;

			num2_arr = str_to_intarray((lo_uchar *)&num2[pad_char(num2, "0")]);
			if (!num2_arr)
				break;

			ans_arr = operators[i].f(num1_arr, num2_arr);
			break;
		}
	}

	free(remain);
	if (ans_arr)
	{
		answer = intarr_to_str(ans_arr);
		if (answer)
		{
			printf("%s\n", (char *)&answer[pad_char((char *)answer, "0")]);
			free(answer);
			return (EXIT_SUCCESS);
		}
	}

	if (!operators[i].sign)
		print_help();

	return (EXIT_FAILURE);
}

/**
 * print_help - print help text
 */
void print_help(void)
{
	fprintf(stderr, "USAGE: <num1> <operand> <num2>\n");
	fprintf(stderr, "Only base 10 numbers are currently supported.\n");
	fprintf(stderr, "Currently supported operands: '+' '-' 'x'  '/'.\n");
}
