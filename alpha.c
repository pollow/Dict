#include <stdio.h>
#include <ctype.h>
int main ()
{
  int i=0;
  char str[]="aA;'1~!-=.m/\\ _='";
  while (str[i])
  {
    if (isalpha(str[i])) printf ("character %c is alphabetic\n",str[i]);
    else printf ("character %c is not alphabetic\n",str[i]);
    i++;
  }
  return 0;
}

