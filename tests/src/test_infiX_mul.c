#include "tests.h"

bignum num1 = {.len = 0, .is_negative = false, .num = NULL};
bignum num2 = {.len = 0, .is_negative = false, .num = NULL};
bignum expected = {.len = 0, .is_negative = false, .num = NULL};

/**
 * infiX_subtraction - dummy.
 * @n1: unused.
 * @n2: unused.
 *
 * Return: a 0 length array, NULL on failure.
 */
bignum *infiX_subtraction(bignum *n1, bignum *n2)
{
	(void)n1;
	(void)n2;
	return (alloc_bignum(0));
}

/**
 * setup - initialises variables for tests.
 */
void setup(void) {}

/**
 * teardown - resets variables for tests.
 */
void teardown(void)
{
	num1.len = 0;
	num1.is_negative = false;
	num1.num = NULL;

	num2.len = 0;
	num2.is_negative = false;
	num2.num = NULL;

	expected.len = 0;
	expected.is_negative = false;
	expected.num = NULL;
}

TestSuite(null_inputs, .init = setup, .fini = teardown);

Test(null_inputs, test_null_times_null,
	 .description = "NULL * NULL = NULL", .timeout = 3.0)
{
	bignum *output = infiX_multiplication(NULL, NULL);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_1_times_null,
	 .description = "1 * NULL = NULL", .timeout = 3.0)
{
	uint in1[] = {1};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	bignum *output = infiX_multiplication(&num1, NULL);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_null_times_1,
	 .description = "NULL * 1 = NULL", .timeout = 3.0)
{
	uint in2[] = {1};

	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	bignum *output = infiX_multiplication(NULL, &num2);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_0_times_null,
	 .description = "0 * NULL = NULL", .timeout = 3.0)
{
	uint in1[] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	bignum *output = infiX_multiplication(&num1, NULL);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_null_times_0,
	 .description = "NULL * 0 = NULL", .timeout = 3.0)
{
	uint in2[] = {0};

	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	bignum *output = infiX_multiplication(NULL, &num2);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_minus1_times_null,
	 .description = "-1 * NULL = NULL", .timeout = 3.0)
{
	uint in1[] = {1};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num1.is_negative = true;
	bignum *output = infiX_multiplication(&num1, NULL);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_null_times_minus1,
	 .description = "NULL * -1 = NULL", .timeout = 3.0)
{
	uint in2[] = {1};

	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	num2.is_negative = true;
	bignum *output = infiX_multiplication(NULL, &num2);

	cr_expect(zero(ptr, output));
}

TestSuite(zero_len_arrays, .init = setup, .fini = teardown);

Test(zero_len_arrays, test_null_times_null,
	 .description = "null_array * null_array = null_array", .timeout = 3.0)
{
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(zero(sz, output->len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(zero(ptr, output->num));
	output = free_bignum(output);
}

Test(zero_len_arrays, test_4490998_times_null,
	 .description = "4,490,998 * null_array = null_array", .timeout = 3.0)
{
	uint in1[] = {4490998};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(zero(sz, output->len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(zero(ptr, output->num));
	output = free_bignum(output);
}

Test(zero_len_arrays, test_null_times_largenum,
	 .description = "null_array * 99992175,712000569,0,0,6086,232509426,238542068 = null_array",
	 .timeout = 3.0)
{
	uint in2[] = {238542068, 232509426, 6086, 0, 0, 712000569, 99992175};

	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(zero(sz, output->len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(zero(ptr, output->num));
	output = free_bignum(output);
}

TestSuite(simple_multiplications, .init = setup, .fini = teardown);

Test(simple_multiplications, test_0_times_0, .description = "0 * 0 = 0",
	 .timeout = 3.0)
{
	uint in1[] = {0}, in2[] = {0}, out[1] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

Test(simple_multiplications, test_1_times_0, .description = "1 * 0 = 0",
	 .timeout = 3.0)
{
	uint in1[] = {1}, in2[] = {0}, out[1] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

Test(simple_multiplications, test_0_times_1, .description = "0 * 1 = 0",
	 .timeout = 3.0)
{
	uint in1[] = {0}, in2[] = {1}, out[1] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

Test(simple_multiplications, test_1_times_1, .description = "1 * 1 = 1",
	 .timeout = 3.0)
{
	uint in1[] = {1}, in2[] = {1}, out[] = {1};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

Test(simple_multiplications, test_long_times_0,
	 .description = "938736,0,3,197812382,472346283,691273964 * 0 = 0",
	 .timeout = 3.0)
{
	uint in1[] = {691273964, 472346283, 197812382, 3, 0, 938736};
	uint in2[] = {0}, out[1] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

/*INVERSE*/

Test(simple_multiplications, test_0_times_long,
	 .description = "0 * 938736,0,3,197812382,472346283,691273964 = 0",
	 .timeout = 3.0)
{
	uint in2[] = {691273964, 472346283, 197812382, 3, 0, 938736};
	uint in1[] = {0}, out[1] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

Test(simple_multiplications, test_u100c_times_u100d,
	 .description = "106998112,639854667,188839999,908562372,840000000,948,320000000"
					"* 1230,998777777,777777774,376573322,300000000"
					"= 131,714545884,190091042,282664403,335339231,394484502,817519667,878072308,554218996,792013003,536000000,0",
	 .timeout = 3.0)
{
	uint in1[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112};
	uint in2[] = {300000000, 376573322, 777777774, 998777777, 1230};
	uint out[] = {0, 536000000, 792013003, 554218996, 878072308, 817519667, 394484502, 335339231, 282664403, 190091042, 714545884, 131};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

/*INVERSE*/

Test(simple_multiplications, test_u100d_times_u100c,
	 .description = "1230,998777777,777777774,376573322,300000000 "
					"* 106998112,639854667,188839999,908562372,840000000,948,320000000 "
					"= 131,714545884,190091042,282664403,335339231,394484502,817519667,878072308,554218996,792013003,536000000,0",
	 .timeout = 3.0)
{
	uint in1[] = {300000000, 376573322, 777777774, 998777777, 1230};
	uint in2[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112};
	uint out[] = {0, 536000000, 792013003, 554218996, 878072308, 817519667, 394484502, 335339231, 282664403, 190091042, 714545884, 131};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

TestSuite(negative_multiplications, .init = setup, .fini = teardown);

Test(negative_multiplications, test_minus_u100a_times_minus_u100c,
	 .description = "-1000,0,0,0,0,0,0,0,1 "
					"* -106998112,639854667,188839999,908562372,840000000,948,320000000 "
					"= 106,998112639,854667188,839999908,562372840,0,948320,0,0,106998112,639854667,188839999,908562372,840000000,948,320000000",
	 .timeout = 3.0)
{
	uint in1[] = {1, 0, 0, 0, 0, 0, 0, 0, 1000};
	uint in2[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112};
	uint out[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112, 0, 0, 948320, 0, 562372840, 839999908, 854667188, 998112639, 106};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.is_negative = true;
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.is_negative = true;
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

/*INVERSE*/
Test(negative_multiplications, test_minus_u100c_times_minus_u100a,
	 .description = "-106998112,639854667,188839999,908562372,840000000,948,320000000 "
					"* -1000,0,0,0,0,0,0,0,1 "
					"= 106,998112639,854667188,839999908,562372840,0,948320,0,0,106998112,639854667,188839999,908562372,840000000,948,320000000",
	 .timeout = 3.0)
{
	uint in1[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112};
	uint in2[] = {1, 0, 0, 0, 0, 0, 0, 0, 1000};
	uint out[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112, 0, 0, 948320, 0, 562372840, 839999908, 854667188, 998112639, 106};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.is_negative = true;
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.is_negative = true;
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

Test(negative_multiplications, test_u100a_times_minus_u100c,
	 .description = "1000,0,0,0,0,0,0,0,1 "
					"* -106998112,639854667,188839999,908562372,840000000,948,320000000 "
					"= -106,998112639,854667188,839999908,562372840,0,948320,0,0,106998112,639854667,188839999,908562372,840000000,948,320000000",
	 .timeout = 3.0)
{
	uint in1[] = {1, 0, 0, 0, 0, 0, 0, 0, 1000};
	uint in2[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112};
	uint out[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112, 0, 0, 948320, 0, 562372840, 839999908, 854667188, 998112639, 106};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.is_negative = true;
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.is_negative = true;
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

/*INVERSE*/
Test(negative_multiplications, test_minus_u100c_times_u100a,
	 .description = "-106998112,639854667,188839999,908562372,840000000,948,320000000 "
					"* 1000,0,0,0,0,0,0,0,1 "
					"= -106,998112639,854667188,839999908,562372840,0,948320,0,0,106998112,639854667,188839999,908562372,840000000,948,320000000",
	 .timeout = 3.0)
{
	uint in1[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112};
	uint in2[] = {1, 0, 0, 0, 0, 0, 0, 0, 1000};
	uint out[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112, 0, 0, 948320, 0, 562372840, 839999908, 854667188, 998112639, 106};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.is_negative = true;
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.is_negative = true;
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

Test(negative_multiplications, test_minus_u100a_times_u100c,
	 .description = "-1000,0,0,0,0,0,0,0,1 "
					"* 106998112,639854667,188839999,908562372,840000000,948,320000000 "
					"= -106,998112639,854667188,839999908,562372840,0,948320,0,0,106998112,639854667,188839999,908562372,840000000,948,320000000",
	 .timeout = 3.0)
{
	uint in1[] = {1, 0, 0, 0, 0, 0, 0, 0, 1000};
	uint in2[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112};
	uint out[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112, 0, 0, 948320, 0, 562372840, 839999908, 854667188, 998112639, 106};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.is_negative = true;
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.is_negative = true;
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

/*INVERSE*/
Test(negative_multiplications, test_u100c_times_minus_u100a,
	 .description = "106998112,639854667,188839999,908562372,840000000,948,320000000 "
					"* -1000,0,0,0,0,0,0,0,1 "
					"= -106,998112639,854667188,839999908,562372840,0,948320,0,0,106998112,639854667,188839999,908562372,840000000,948,320000000",
	 .timeout = 3.0)
{
	uint in1[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112};
	uint in2[] = {1, 0, 0, 0, 0, 0, 0, 0, 1000};
	uint out[] = {320000000, 948, 840000000, 908562372, 188839999, 639854667, 106998112, 0, 0, 948320, 0, 562372840, 839999908, 854667188, 998112639, 106};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.is_negative = true;
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.is_negative = true;
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

TestSuite(large_multiplications, .init = setup, .fini = teardown);

Test(large_multiplications, test_o1ka_times_o1kb,
	 .description = "o1ka * o1kb = large3", .timeout = 3.0)
{
	uint in1[] = {645836236, 108893430, 836208119, 270771001, 537613755, 373039867, 833294108, 898839418, 608485063, 546188873, 452231917, 687296422, 111111152, 111111111, 111111111, 111111111, 111111111, 111111111, 111111111, 111111111, 111111111, 111111111, 476411111, 5669047, 700035645, 893473278, 4493, 543630640, 324000, 568376700, 1394, 300000000, 378345892, 8, 734194700, 423768, 0, 445197384, 518101037, 109617878, 558156514, 983336821, 690076644, 693516675, 143226629, 76588580, 210759419, 973911560, 497333540, 14322213, 555048869, 815323758, 539167661, 458688023, 612425259, 624332483, 419554373, 679371075, 393235000, 236728315, 664373133, 150410609, 518660305, 359239326, 307363945, 571210805, 347785534, 563445710, 660409386, 228008317, 804462179, 233074148, 591937180, 160409198, 950235053, 962974549, 171857157, 523072994, 395079814, 321058488, 203652900, 126072395, 363107953, 630915068, 973080517, 612433363, 734409773, 377726669, 707225937, 627074076, 918808553, 941285428, 110569912, 430944738, 394600177, 990968620, 4498198, 265970467, 594659210, 881718792, 749254660, 489225907, 417635079, 182995180, 494838468, 16834009, 911110449, 948701330, 831191398, 792151714, 70940218, 627665839, 410612359, 202045867, 935804051, 937850141, 227018012, 991791152, 506752363, 406483698, 355792683, 47491630, 22359011, 919962818, 955165934, 399211808, 673319428, 319818160, 662785141, 175882430, 630322415, 735383534, 687650610, 46582669, 496678148, 491637987, 871575195, 116330034, 723314187, 385420689, 325094262, 12829142, 208703866, 120005690, 899921757, 77002169, 359486189, 753454258, 278911354, 694037307, 578519296, 494600786, 470779501, 768446187, 472669563, 716361937, 389127515, 976446119, 593192334, 617083917, 272976737, 418747631, 855714255, 226105187, 605917499, 696971445, 573117854, 99153257, 956645492, 728520292, 946389174, 245482697, 655465609, 470307816, 135416351, 729216591, 866144546, 888959338, 809402688, 527131609, 866613186, 419167460, 916600904, 633154349, 747140489, 315862951, 238759183, 148584074, 652667824, 161606397, 677427537, 590777629, 825244648, 835356427, 366982335, 748040826, 852122159, 4896, 900000000, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 385820199, 167580321, 134092496, 277075937, 872169008, 64325722, 827080282, 277960712, 655352740, 163131699, 448213684, 277128786, 514326330, 933871396, 63154105, 745922799, 490015860, 252229607, 711956623, 591788040, 954758766, 467124003, 644524713, 690634208, 510828673, 629041620, 704066384, 468512842, 590156377, 509105852, 101803594, 777808979, 519622805, 972925209, 333284887, 366099858, 584319133, 851605740, 743738793, 912271659, 205902321, 306768696, 951511006, 853007337, 793747247, 858293618, 953587774, 433638706, 827128463, 10931106, 238240138, 541935268, 774418024, 534563619, 736369239, 336516542, 723202909, 72035747, 712282212, 121201039, 863656439, 738195137, 536402352, 988504044, 143816789, 991215483, 635637328, 796292638, 712577246, 870774981, 572335077, 92461651, 417842402, 465754445, 443219011, 441495263, 360383390, 613384414, 161967625, 730605620, 45166037, 501067481, 119816381, 482382428, 993423658, 444792073, 338718477, 357679842, 186546204, 725908514, 242243363, 998754918, 228221686, 517265463, 874612151, 181719511, 64245869, 179742910, 880842840, 733045974, 909570009, 761337985, 469116507, 501497182, 26189637, 141834727, 777673597, 739280728, 284499268, 848912007, 618450280, 855914917, 508218929, 64124951, 440691829, 852588078, 555626401, 202070759, 783604366, 202777713, 212620403, 857142928, 324004839, 349402718, 847565789, 52519590, 658472794, 842462660, 791141310, 195364150, 381999943, 261729562, 18229};
	uint in2[] = {120720357, 397122822, 391212010, 378636564, 527381951, 445364023, 899885040, 831438167, 289912154, 386356373, 467962926, 817125772, 778707749, 515723350, 20924616, 454178424, 114657544, 634432190, 904414952, 143603833, 256133844, 201619676, 377306056, 810451660, 815010674, 281198163, 584823824, 739934236, 774447920, 423387184, 43576798, 141865462, 637259085, 182422433, 869987549, 632282216, 515172654, 118746121, 691817195, 100642458, 401797429, 748808428, 97330459, 859095700, 77613379, 824691165, 375014971, 270261896, 971418347, 287776735, 687392807, 72844992, 808489120, 176184502, 298559149, 515082189, 290641249, 784406918, 18525880, 595556264, 662020707, 137836043, 32027777, 282126204, 398571429, 183240048, 893494027, 908475657, 210325195, 41368093, 567494670, 78549187, 829867982, 939611731, 556446171, 260470617, 388185363, 898568742, 584926832, 930685864, 974259747, 196534676, 548532814, 760521395, 176790149, 995282978, 514569063, 129660418, 873623608, 869739334, 116299016, 931525892, 602082336, 842229732, 82941119, 584280220, 738070679, 549296857, 554682269, 129930289, 352088067, 846285574, 807033108, 924619988, 410518654, 524776378, 210726853, 338324773, 234371231, 345598217, 215913853, 40125185, 169659817, 614457144, 263430597, 839552963, 357693985, 358911228, 31559180, 973973025, 529509086, 130265707, 902771569, 939005219, 909614411, 481137671, 453755527, 315076922, 190488385, 858980849, 914750855, 893492457, 44932638, 537640698, 831905869, 686543771, 164968285, 32694655, 549006585, 907130711, 937753741, 473161761, 60159427, 193787354, 490610706, 977776760, 692607694, 6731141, 102078922, 359416565, 975892579, 663415745, 486552688, 501065002, 401362961, 293547871, 954030315, 717222449, 171804201, 933246578, 628660373, 388008411, 546067821, 318550725, 990682255, 492064339, 647433279, 137385221, 703102597, 102835383, 283915020, 951593059, 607687526, 836935402, 684651719, 23912707, 349733186, 901432221, 855504886, 181532375, 353916766, 945868802, 361242525, 362433248, 541955437, 67937107, 539323500, 323672831, 966437313, 515041060, 651866030, 535923932, 530736394, 457121080, 34778553, 656344571, 766040938, 922800831, 880446217, 23307414, 859193718, 316040919, 995023505, 796297454, 417185715, 452307299, 839507981, 32105848, 520365290, 312607239, 836310795, 763091506, 397308051, 361243336, 973440977, 737772666, 670722593, 362707407, 891880855, 294128542, 811056991, 743094473, 39460017, 899096862, 700449819, 26597046, 259465921, 88171879, 774925466, 948922590, 41763507, 818299518, 949483846, 901683400, 91111044, 894870133, 483119139, 879215171, 907094021, 962766583, 741061235, 120204586, 193580405, 293785014, 701801};
	uint out[] = {973456252, 412698082, 156854265, 231236880, 474358034, 679091949, 447758531, 493377411, 637994538, 575462518, 915755352, 555293881, 482859668, 676700950, 334034557, 28408988, 482628258, 579259594, 738872206, 871197308, 702265474, 735864594, 157512557, 926743357, 882048537, 11150613, 523219675, 755874332, 581977406, 211329093, 984017167, 57567319, 514051826, 791772321, 792638993, 760554402, 43145462, 193551802, 565360348, 17126266, 472717017, 346875411, 481924938, 7117958, 479017028, 247605729, 209278489, 840696239, 392147532, 53495250, 504210065, 502046351, 714511625, 881956908, 62941673, 916753945, 486652595, 412929118, 54954346, 869595157, 382728091, 722988513, 335328409, 634858740, 256572717, 674203563, 11600175, 418581840, 405046569, 423979357, 951659798, 727308504, 147846721, 768544058, 903047950, 295815064, 868897303, 158285362, 949970028, 326721887, 96356142, 812585111, 896931597, 284906965, 874823497, 905386578, 874287653, 607465176, 624185734, 560032461, 392420655, 8741201, 570521627, 187892696, 989242173, 79457270, 461279755, 178329389, 863762415, 784766683, 31200121, 235831641, 266812872, 199500139, 41723628, 544094501, 857075377, 728444420, 941631074, 404474606, 554179674, 578222996, 797987054, 818738326, 750114941, 50103196, 702184938, 613585960, 665317743, 89904246, 998763247, 339029123, 612595234, 311369789, 959610269, 256630824, 806914657, 793679993, 773620201, 656505563, 994393849, 83683155, 683539241, 804011207, 814146601, 718972641, 845237219, 821538729, 996169319, 35360267, 188778355, 171516559, 708660738, 675157272, 476122012, 900085612, 674772993, 833334730, 10283515, 479131685, 598115734, 369471312, 457491682, 743913010, 156425832, 522883672, 386468073, 772647334, 565053022, 562706849, 445012977, 493314535, 615502660, 322329933, 81383481, 271443191, 643358277, 165941717, 986778798, 752550196, 909173766, 375154039, 511109692, 394859628, 384146192, 507157613, 158454506, 791999371, 324651095, 711961205, 468979783, 254824501, 616886879, 746634373, 489181536, 506140156, 444347759, 634431730, 273551361, 375807327, 502322677, 292149421, 966534332, 57901320, 450439429, 695626107, 163249440, 694453265, 334196451, 109269266, 681332690, 861225219, 7573952, 23684526, 911385340, 921755065, 545439132, 830528350, 584344913, 907999009, 155084801, 713641398, 208952730, 997477963, 408430834, 23929822, 704162858, 155645295, 13570028, 595968323, 792853920, 717155113, 60375533, 875568440, 84416889, 283735593, 613303615, 323997640, 158793785, 806776977, 343428972, 60189921, 693181877, 450069176, 969912778, 533925309, 635186714, 178044482, 417746812, 389330418, 40064830, 116884312, 695388930, 630170261, 336660214, 215980765, 916786927, 748054826, 485554673, 134452359, 308228183, 478022556, 966390076, 439246974, 229665139, 858393286, 978296503, 371719426, 629798177, 679786960, 402143518, 283524678, 451155328, 473585934, 548242332, 584125220, 673950073, 260484559, 739354747, 881533924, 26361124, 116924967, 555237505, 99529654, 896048195, 61934823, 160601585, 68047935, 745268295, 416848656, 869553347, 26234477, 692261965, 808106330, 368939608, 849358439, 670595250, 644257130, 596214304, 463399078, 275448545, 727776118, 587712963, 357837625, 164679319, 951643847, 563042657, 830792179, 898451375, 696965900, 208643746, 981614459, 707936773, 495532392, 636082905, 46998285, 998285197, 667305176, 626063933, 533179955, 852260195, 663445217, 529155749, 115445158, 577011797, 25167443, 204047256, 528091432, 119995549, 195632980, 244146639, 739403804, 941838780, 398481977, 483670969, 492958219, 666322530, 527176054, 986460574, 719557393, 674996087, 382550968, 16803867, 173650919, 740280510, 231187964, 754874386, 950555752, 780118606, 101946412, 535080386, 174433453, 334398158, 115832425, 825054471, 389454401, 725668657, 818920111, 172048484, 655057164, 865548808, 488417742, 543910662, 836247751, 666824852, 156780165, 860772084, 143283360, 58418781, 563326303, 435594916, 229167653, 32831233, 652408171, 839839122, 321889398, 821805902, 551017937, 34299250, 878004560, 944623782, 708591772, 214464763, 277627044, 906269682, 610260566, 767915418, 728864978, 834927805, 999929693, 500994779, 535375840, 23423948, 902176013, 648632566, 128840743, 301398950, 553163152, 323527568, 638326068, 658944113, 60443061, 668747641, 113060422, 448574319, 592719878, 2176602, 388104636, 11280977, 577457862, 728759188, 519861282, 964856560, 142865932, 928150663, 430600900, 668499938, 799275115, 263903, 85263396, 510302143, 959387652, 932233414, 760434309, 877255999, 573782281, 520481225, 652841903, 482562292, 903603164, 723593546, 76083784, 136573214, 967418740, 349005310, 81834840, 683948859, 860511074, 370207012, 424903007, 901105805, 754764642, 849934405, 512138206, 837848485, 87432107, 417398926, 471026245, 599294466, 577945852, 86657339, 407494833, 604849411, 966944988, 801330989, 451971306, 609232888, 47659834, 896809512, 994536587, 989839281, 951417795, 603854645, 785913529, 768187002, 306378440, 226203351, 952896790, 910078814, 601852748, 468277671, 569904482, 520109000, 443092900, 237917827, 251315171, 895081352, 177233379, 232447676, 215448790, 917264511, 11583959, 592106742, 199303169, 135876151, 571557807, 882365864, 104982756, 935904656, 417654677, 426751352, 627318519, 766403211, 892041049, 881508720, 607642765, 172673071, 803070934, 227347972, 909313199, 157721361, 535054181, 672603138, 349791820, 141494560, 994784732, 789999905, 892146519, 16980279, 134625955, 687523403, 681010849, 518770241, 719253947, 580477776, 435291970, 486362767, 418331810, 20718479, 464165537, 966564556, 407470630, 572686995, 26282610, 618861478, 625082406, 432892546, 640034560, 862007197, 414071410, 913610433, 920560543, 456160460, 762876589, 255937081, 736179553, 369907390, 60441261, 932243728, 314282262, 179199393, 790480747, 400957046, 646058176, 332997666, 509055242, 753760358, 133152612, 397022623, 228550, 802407198, 493029134, 36573414, 571614603, 319764046, 509983754, 493996015, 675406418, 438125701, 107327858, 964655814, 725049626, 35504121, 78510303, 936704532, 635504588, 884899156, 270193834, 736313759, 364005708, 335726402, 57871891, 125811761, 20979223, 145350869, 169344764, 832087925, 473947957, 420470955, 665579758, 396006552, 668386204, 585089701, 184075882, 787512919, 854795440, 123600449, 865901675, 581215748, 424799045, 934853430, 941417173, 343291745, 918614827, 552525207, 793319466, 12};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}

Test(large_multiplications, test_o500c_times_o500d,
	 .description = "o500c * o500d = medium_large3",
	 .timeout = 3.0)
{
	uint in1[] = {555555555, 55555555, 0, 0, 0, 0, 222222, 0, 0, 0, 0, 0, 0, 0, 0, 888888888, 888888888, 888888888, 888888888, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110000000, 111111111, 111111111, 111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 770000000, 777777777, 777777777, 777777, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 999000000, 99999999};
	uint in2[] = {470282653, 363502795, 428381283, 187482382, 467199043, 93190808, 0, 0, 0, 400000000, 133986336, 818672645, 328552829, 467844093, 238950876, 737842756, 975675668, 665546560, 147030781, 113541635, 672921659, 886614454, 888895933, 888888888, 888888888, 888888888, 268888888, 160980940, 318652713, 746086661, 442022266, 249623720, 646946071, 524660960, 229717732, 571794052, 616061544, 679629263, 171257724, 787077498, 157233507, 209246165, 541784240, 146575444, 344321901, 44149526, 436038339, 561338441, 16196762, 773060562, 104516603, 150106748, 411981638, 444444444, 444444444, 444444444, 444444444, 444444444, 444444444, 4};
	uint out[] = {294287415, 75831780, 177026101, 971593276, 542021713, 458643016, 288781579, 323392264, 745551604, 709987999, 386893910, 59687728, 880490600, 730012872, 52169114, 775827449, 304211339, 140784554, 917261839, 726744766, 627381880, 176393466, 753107174, 225257039, 312755502, 774591122, 391444733, 794137115, 787601054, 497815650, 904572367, 346034109, 789225580, 818484928, 472769027, 459700755, 234944313, 9474951, 66396813, 798295697, 537282204, 385560987, 178114501, 667730617, 309887172, 648486165, 738014897, 465723711, 103389190, 245592126, 321855010, 135634073, 321521982, 385060287, 751325279, 966726173, 898710961, 766861711, 519317447, 355790927, 651476935, 6864796, 107185658, 944506593, 215150947, 245106082, 487662514, 893360024, 766354313, 931665299, 465119474, 166619448, 687943327, 281739217, 664296560, 844889875, 19611252, 79785981, 794177827, 231331982, 906088858, 566537931, 510016717, 342556251, 797501561, 934483127, 256933446, 796722724, 870732331, 946698310, 697978514, 324031829, 359006057, 466459059, 313138659, 379270869, 636354070, 860271637, 678566913, 658638656, 717948827, 82426983, 525815414, 858680557, 398227583, 737007306, 398970894, 579839622, 553031848, 588313222, 295388040, 462978914, 381042495, 694117647, 597846615, 629201539, 172301553, 370598693, 996753719, 999999999, 999999999, 999999999, 999999999, 439999999, 444444444};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.num = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.num = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.num = out;
	bignum *output = infiX_multiplication(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->num, expected.num));
	output = free_bignum(output);
}
