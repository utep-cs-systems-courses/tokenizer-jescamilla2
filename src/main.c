#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"


int main() {
  char *str = "Hello my name is Jeff";

  /* while(1) {
    putchar('$');
    fgets(str, 100, stdin);
    // printf("%s\n", str);

    if (strcmp(str, "q") == 0) {
      break;
    }
    }*/

  printf("The string you entered is: '%s'\n", str);
  printf("The number of words is: %d\n", count_words(str));
  printf("Here is the tokenized string: \n");

  printf("\n");
  char **tokens = tokenize(str);
  print_tokens(tokens);

  printf("\n");
  printf("After freeing memory...\n");
  free_tokens(tokens);
  print_tokens(tokens);

  printf("\n");
  printf("Next, to create the history.\n");
  printf("Initializing a new history list: L\n");

  List *L = init_history();

  char *strings[5];
  strings[0] = "My dog has fleas";
  strings[1] = "My friend has fleas";
  strings[2] = "My grandma has fleas";
  strings[3] = " ";
  strings[4] = "My teacher has fleas";

  for (int i = 0; i < 5; i++) {
    add_history(L, strings[i]);
  }

  print_history(L);
  
  printf("\n");
  printf("Now to test get_history()...\n");

  for (int i = 0; i < 7; i++) {
    if (strcmp(get_history(L,i),"") == 0) {
      printf("No history found for id %d.\n", i);
    } else {
      printf("Getting history %d: '%s'\n", i, get_history(L, i) );
    }
  }


  printf("\n");
  printf("Freeing history...");
  printf("\n");
  free_history(L);

  printf("\n");
  printf("Now printing history...");
  printf("\n");
  print_history(L);
 
}
