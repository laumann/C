#include <stdio.h>
#include <stdlib.h>
/**
 * C recursive descent expression parser. Grammar:
 *
 *   <primary> ::= digit | (<exp>)
 *   <unary>   ::= <primary> | -<unary> | +<unary>
 *   <mult>    ::= <unary> | <mult> * <unary> |
 *                 <mult> / <unary> | <mult> % <unary>
 *   <exp>     ::= <exp> + <mult> | <exp> - <mult> | <mult> 
 *
 */

int expr(void);
int mult_expr(void);
int unary_expr(void);
int primary_expr(void);

int
main(int argc, char* argv[])
{
  int val;

  for ( ; ; ) {
    printf("Expression: ");
    val = expr();
    if (getchar() != '\n') {
      printf("Error!\n");
      while (getchar() != '\n')
	; /* NULL */
    }
    else {
      printf(" = %d\n", val);
    }
  }
  exit(EXIT_SUCCESS);
}

/*
 * Grammar:
 * <exp>     ::= <exp> + <mult> | <exp> - <mult> | <mult> 
 */
int
expr()
{
  int val, ch_in;

  val = mult_expr();

  for ( ; ; ) {
    switch (ch_in = getchar()) {
    case '+': 
      val = val + mult_expr();
      break;
    case '-':
      val = val - mult_expr();
      break;
    default:
      ungetc(ch_in, stdin);
      return val;
    }
  }
}

/*
 * Grammar:
 * <mult>    ::= <unary>
 *             | <mult> * <unary>
 *             | <mult> / <unary>
 *             | <mult> % <unary>
 */
int
mult_expr()
{
  int val, ch_in;

  val = unary_expr();

  for ( ; ; ) {
    switch(ch_in = getchar()) {
    case '*':
      val = val * unary_expr();
      break;
    case '/':
      val = val / unary_expr();
      break;
    case '%':
      val = val % unary_expr();
      break;
    default:
      ungetc(ch_in, stdin);
      return val;
    }
  }
}

/*
 * Grammar:
 *   <unary>   ::= <primary> | -<unary> | +<unary>
 */
int
unary_expr()
{
  int val, ch_in;
  
  switch(ch_in = getchar()) {
  case '-':
    val = -unary_expr();
    break;
  case '+':
    val = unary_expr();
    break;
  default:
    ungetc(ch_in, stdin);
    val = primary_expr();
    break;
  }
  return val;
}

int
primary_expr()
{
  int val, ch_in, pos=1;
  char number[BUFSIZ];

  ch_in = getchar();

  if (ch_in >= '0' && ch_in <= '9') {
    number[0] = ch_in;
    /* printf("%d", number[0]-'0'); */
    for (;;) {
      ch_in = getchar();
      if (ch_in >= '0' && ch_in <= '9') {
	number[pos] = ch_in;
	/* printf("%d", number[pos]-'0'); */
	pos++;
      }
      else {
	ungetc(ch_in, stdin);
	break;
      }
    }
    /* printf("\n"); */
    number[pos+1] = '\0'; /* terminate the string */
    val = atoi(number);   /* convert */
    /* printf("Got number: %d\n", val); */
    goto out;
  }
  if (ch_in == '(') {
    val = expr();
    getchar();  /* Skip closing ')' */
    goto out;
  }
  printf("Error: primary read %d\n", ch_in);
  exit(EXIT_FAILURE);

 out:
  return val;
}
