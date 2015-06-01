/* 
 * CS:APP Data Lab 
 * 
 * Zhihao Li (zhihaol)
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code 
must conform to the following style:

int Funct(arg1, arg2, ...) {
  /* brief description of how your implementation works */
  int var1 = Expr1;
  ...
    int varM = ExprM;

  varJ = ExprJ;
  ...
    varN = ExprN;
  return ExprR;
}

Each "Expr" is an expression using ONLY the following:
1. Integer constants 0 through 255 (0xFF), inclusive. You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables (no global variables).
3. Unary integer operations ! ~
4. Binary integer operations & ^ | + << >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators. You are not restricted to
one operator per line.

You are expressly forbidden to:
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, ||, -, or ?:
6. Use any form of casting.
7. Use any data type other than int.  This implies that you
cannot use arrays, structs, or unions.


You may assume that your machine:
1. Uses 1s complement, 32-bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
/*
 * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
 */
int pow2plus1(int x) {
  /* exploit ability of shifts to compute powers of 2 */
  return (1 << x) + 1;
}

/*
 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
 */
int pow2plus4(int x) {
  /* exploit ability of shifts to compute powers of 2 */
  int result = (1 << x);
  result += 4;
  return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
    the coding rules are less strict.  You are allowed to use looping and
    conditional control.  You are allowed to use both ints and unsigneds.
    You can use arbitrary integer and unsigned constants.

    You are expressly forbidden to:
    1. Define or use any macros.
    2. Define any additional functions in this file.
    3. Call any functions.
    4. Use any form of casting.
    5. Use any data type other than int or unsigned.  This means that you
    cannot use arrays, structs, or unions.
    6. Use any floating point data types, operations, or constants.


    NOTES:
    1. Use the dlc (data lab checker) compiler (described in the handout) to 
  check the legality of your solutions.
2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
  that you are allowed to use for your implementation of the function. 
  The max operator count is checked by dlc. Note that '=' is not 
  counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
  header comment for each function. If there are any inconsistencies 
  between the maximum ops in the writeup and in this file, consider
  this file the authoritative source.

  /*
   * STEP 2: Modify the following functions according the coding rules.
   * 
   *   IMPORTANT. TO AVOID GRADING SURPRISES:
   *   1. Use the dlc compiler to check that your solutions conform
   *      to the coding rules.
   *   2. Use the BDD checker to formally verify that your solutions produce 
   *      the correct answers.
   */


#endif
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  /* Use De Morgan's Law to convert OR to NEGATE and AND */
  return ~((~x) & (~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* 
   * Suppose we are talking about the 32-bit integer, TMIN
   * is 1 followed by 31 0s.
   */
  return 1 << 31;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* Obviously... */
  return ~x + 1;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /* Move the byte to rightmost position and use 0xff
   * to mask out the more significant bytes.
   */
  return (x >> (n << 3)) & 0xff;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  /*
   * For positive numbers, x/(2^n) == x >> n;
   * for negative numbers, x/(2@n) == (x + 1<<n - 1)>>n
   */
  int isNeg = x >> 31;
  int a = ((isNeg & 1) << n) + isNeg;
  return (x + a) >> n;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /* Use mask to mask out the leading bits. */
  int mask = ~((1 << 31) >> n << 1);
  return (x >> n) & mask;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /*
   * 		!x		!(x >> 31)		result
   * 0   1 				1						1
   * P	 0				1						1
   * N	 0				0						0
   *
   * There is an XOR relationship.
   */
  return (!x) ^ (!(x >> 31));
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
  /*
   * If x and y have the same sign, check if (x-y) is negative;
   * otherwise, an overflow is likely to happen. But the negative
   * number is always less than the positive number.
   */
  int signDiff = x ^ y; // if the signs of x and y are different
  int interm = x + ~y + 1; // x - y
  return (((signDiff & x) | (~signDiff & interm)) >> 31) & 1;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /*
   * The leading bit of ((-x) | x) is 1 for all numbers except for 0
   */
  /* int tmp = 1 << 31; */
  /* int after = ~tmp + x; */
  /* int signDiff = ~(after ^ x); */
  /* int sign = x ^ tmp; */
  /* return ((sign & signDiff) >> 31) & 1; */
  int tmp = (((~x + 1) | x) >> 31); // 0xffffffff or 0x0
  return  tmp + 1;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  /*
   * If a positive number is power of 2, the leading bit should be
   * 0 and (x-1)&x == 0
   */
  int sign = !(x >> 31);
  return (!!x) & sign & !((x + ~1 + 1) & x);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  /*
   * Find the leftmost 1. Use a method that is similar to 
   * binary search.
   */
  int result = 0;
  result = (!!(x >> 16)) << 4; // if > 16? 
  // based on previous result, if > (result + 8)
  result = result + ((!!(x >> (result + 8))) << 3);
  result = result + ((!!(x >> (result + 4))) << 2);
  result = result + ((!!(x >> (result + 2))) << 1);
  result = result + (!!(x >> (result + 1)));
  return result;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  /*
   * Pay attention to exp == 0, exp == 00000001
   */
  unsigned s = uf & 0x80000000u;
  unsigned exp = uf & 0x7f800000u;
  unsigned frac = uf & 0x007fffffu;
  unsigned toAdd = ((frac & 3) == 3); // round to nearest even
  unsigned new_frac = frac >> 1;
  if (exp == 0x7f800000u) return uf; // inf or nan
  else if (exp == 0x00000000u) {
    frac = new_frac + toAdd; // add the leading 1
  }
  else if (exp == 0x00800000u) {
    frac = (new_frac | 0x00400000u) + toAdd;
    exp = 0;
  }
  else {
    exp = (exp-0x00800000u);
  }
  return s + exp + frac;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned s = 0, exp = 31, frac = 0, toAdd = 0;
  if (x == 0x00000000u) return 0x00000000u;
  if (x & 0x80000000u) { s = 0x80000000u; x = -x; }
  while (1) {
    if (x & 0x80000000u) break;
    exp -= 1;
    x <<= 1;
  }
  if ((x & 0x000001ff) == 0x180) toAdd = 1;
  else if ((x & 0xff) > 0x80) toAdd = 1;
  /* + toAdd may lead to a carry
   * if this happens, we need to 
   *    frac >>= 1
   *    exp += 1 
   * However, since we supress the leading 1 of frac,
   * the carry can be automatically added to exp.
   */
  frac = ((x & 0x7fffffffu) >> 8) + toAdd;
  
  return s + ((exp + 127) << 23) + frac;
}
