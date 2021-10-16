#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

/* Return true (non-zero) if c is a whitespace character
   ('\t' or ' ').
   Zero terminator are not printable (therefore false) */
int space_char(char c)
{
  if ((c == '\t') || (c == ' ')) {
    return 1;
  } else {
    return 0;
  }
}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
int non_space_char(char c)
{
  switch (c) {
  case '\t':
  case ' ':
  case '\0':
    return 0;
  default:
    return 1;
  }
}

/* Returns a pointer to the first character of the next
   space-separated word in zero-terminated str. Return a zero pointer if
   str does not contain any words. */
char *word_start(char *str)
{
  /* Start at first element of str (*str == str[0]).
     If it's a non_space_char, increment str.
     str++ moves pointer (str) to the NEXT address (which is address of str[1] of original str).
     
     ex. If str = "Hello", then str points to 'H' and str++ results in 
     str pointing to 'e', and *str = 'e' since *str is the object. 

     Note: word_start() really returns a substring of original str starting
     at the location of the first non_space_char and *word_start() returns *str
     which is the actual char. */

  while(space_char(*str)) { //find first non_space_char
    str++; 
  }
  return str;
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  /* Works in the same manner as word_start,
     but finds the first space_char instead. */
  while(non_space_char(*word)) {
    word++;
  }
  return word; 
}

/* helper function */
short len(char *str)
{
  short length = 0;
  while (*str != '\0') {
    length++;
    str++;
  }
  return length;
}

/* Counts the number of words in the string argument.
   This method was written using the example from the book */
int count_words(char *str) {
  int state = 0; // in = 1, out = 0
  int num_words = 0; //total word count

  int i = 0;
  while (str[i] != '\0') { //continue until end of string is reached
    if (str[i] == '\t' || str[i] == ' ') {
      state = 0; // out of word
    } else if (state == 0) {
      state = 1;
      num_words++;
    }
    i++;
  }
  return num_words;
}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len) {

  char *copy = (char*)malloc((len+1)*sizeof(char));

  
  for (int i = 0; i < len; i++) {
    copy[i] = inStr[i]; //could also do copy[i] = *(inStr+i)
  }
  copy[len] = '\0'; // add in the '\0' character
  return copy;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char **tokenize(char *str){

  int num_words = count_words(str); //total words

  char **tokens = (char**)malloc((num_words+1)*sizeof(char*)); //allocate memory
  char *begin; //start of word
  char *end; //end of word
  int len; //keep track of each word length

  //iterate through str and copy each word into tokens
  for (int i = 0; i < num_words; i++) {

    begin = word_start(str);
    end = word_terminator(begin);
    len = end - begin;

    tokens[i] = copy_str(begin, len);

    str = end;
  }

  tokens[num_words] = 0; //the last entry should be 0

  return tokens;  
}

/* Prints all tokens. */
void print_tokens(char **tokens)
{
  int i = 0;
  while(tokens[i] != NULL) {
    printf("tokens[%d] = \"%s\"\n", i, tokens[i]);
    i++;
  }
  printf("tokens[%d] = %d\n", i, 0);
     
}

/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens)
{
  int i = 0;
  while(tokens[i] != NULL) {
    free(tokens[i]); //free memory for each pointer in tokens
    i++;
  }

  free(tokens); // finally, free tokens itself
}
