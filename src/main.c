#include <stddef.h> // define NULL
#include "lstr.h"

LStr filter(LStr *s) {
    LStr res = cutWord(s);
    int base = countChar(res, '1');
    LStr tail = getTail(res);
    LStr word;
    while (word = cutWord(s), word != NULL) {
        if (countChar(word, '1') == base) {
            tail->next = word;
            tail = getTail(word);
        } else
            freeLStr(word);
    }
    return res;
}

int main() {
   LStr res;
   LStr line = readLine(NULL);
   while (line != NULL) {
       res = filter(&line);
       printLStr(res);
       freeLStr(res);
       line = readLine(line);
   }

   return 0;
}