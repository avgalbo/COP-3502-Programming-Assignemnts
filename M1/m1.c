/* COP 3502C Midterm Assignment One
This program is written by: Anthony Galbo */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

char char_items[SIZE];
int int_items[SIZE]; //int stack for postfix math
int top;

void init();
void push(char input);
char pop();
void push_int(int input);
char pop_int();
int precedence(char input);
int isOperator(char input);
void infixToPostfix(char *infix,char *postfix);
int power(int x, unsigned int y);
void mathFunction(char *postfix);

int main(void)
{
  char infix[SIZE], postfix[SIZE], choice;

  while(1)
  {
    printf("\nMenu: press 'y' to proceed and 'q' to quit:");
    scanf("%c", &choice);

    if(choice == 'q')
    {
      printf("\nProgram terminated\n\n");
      break;
    }
    if(choice == 'y')
    {
      printf("\nEnter infix Expression: ");
      scanf("%s", infix);
      infixToPostfix(infix,postfix);
      printf("\nPostfix: %s\n", postfix);
      mathFunction(postfix);
      printf("\n");
    }
  }
  return 0;
}

void init()
{
  top = -1;
}

void push(char input)
{
  char_items[++top] = input;
}

char pop()
{
  return char_items[top--];
}

void push_int(int input)
{
  int_items[++top] = input;
}

char pop_int()
{
  return int_items[top--];
}

int precedence(char input)
{
  if(input == '(' || input == ')')
    return 1;

  if(input == '+' || input == '-')
    return 2;

  if(input == '*' || input == '/' || input == '%')
    return 3;

  if(input == '^')
    return 4;

  return 0;
}

int isOperator(char input)
{
    if(input == '(' || input == ')' || input == '+' || input == '-' ||
       input == '*' || input == '/' || input == '%' || input == '^'  )
       return 1;

    return 0;
}

void infixToPostfix(char *input, char *output)
{
   int i, k, temp;

   init();

   k = 0;
   for(i = 0; input[i] != '\0'; i++)
    {
      temp = input[i];
      //check to see if first encouter of input is an operand,
      if(isOperator(temp) == 0)// if so, put it in the output.
         output[k++] = temp;
      else
      {
         if(temp == '(')//or if the input is a '(' if so,
            push(temp);// push() it in the stack.
         else
         {
            if(temp == ')')
            {
               while(char_items[top] != '(')//or if input is a ')', loop through the elements in
                 output[k++] = pop();//in the stack, pop them out untill a '(' is encountered,
                 pop();// then pop the '(' to the output
            }
            else
            {// precedence check... if the input has greater precedence than
               if(precedence(temp) > precedence(char_items[top]))//the top
                  push(temp);//element in the stack, push() it in the stack.
               else
               {// otherwise if input has lower precedence than the top element
                 //in the stack, loop through the stack and pop() them in the ouput.
                  while(precedence(temp) <= precedence(char_items[top]))
                     output[k++] = pop();
                  //then push the input in the stack that had lower precedence.
                  push(temp);
               }
            }
         }
      }
   }
   //last command would be to pop the remaining elements out of the stack into
   // the output.
   while(char_items[top] != -1)
      output[k++] = pop();
  //always terminate string with a null character ('\0')
   output[k]='\0';
}

int power(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if (y % 2 == 0)
        return power(x, y/2) * power(x, y/2);
    else
        return x * power(x, y/2) * power(x, y/2);
}

void mathFunction(char *output)
{
  int i, x, y, powerResult, result;
  char temp;

  init();

  for(i = 0; output[i] != '\0'; i++)
  {
    temp = output[i];
    // if the first element is not a digit, push it in the stack minus the ASCII value
    if(isdigit(temp))
      push_int(temp-'0');
    //otherwise pop the two ints out of the stack and assign them to ints x and y
    else
    {
      x = pop_int();
      y = pop_int();

        if(temp == '+')
          push_int(x + y);

        if(temp == '-')
          push_int(y - x);

        if(temp == '*')
          push_int(x * y);

        if(temp == '/')
          push_int(y / x);

        if(temp == '%')
          push_int(y % x);

        if(temp == '^')
          push_int(power(x,y));
    }
  }
      result = int_items[top];
      printf("Result: %d\n", result);
}
