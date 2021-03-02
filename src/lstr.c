/*
implemetation of LString functions
*/
#include <stdio.h>
#include <stdlib.h>
#include "lstr.h"

#define XSTR(s) #s
#define STR(s) XSTR(s)

#define BUF_MAX_SIZE 1023 // define one it less
LStr readLine(LStr s) {
    if (s == NULL) {
        s = malloc(sizeof(Item));
        if (s == NULL) {
            puts("Error not enough memory for LStr allocation");
            return NULL;
        }
        s->next = NULL;
    }
    
    char buf[BUF_MAX_SIZE + 1];
    int n, len, free_space = LSTR_MAX_SIZE;
    // last - last element in the list (used for linking)
    // tail - next element to use (NULL if there is none)
    Item *tail = s, *last = s;
    do {
        len = 0;
        n = scanf("%" STR(BUF_MAX_SIZE) "[^\n]", buf);
        if (n == 0)
            scanf("%*\n");
        if (n > 0) {
            for (; buf[len] != '\0' && len <= free_space; ++len) {
                if (tail == NULL) {
                    tail = malloc(sizeof(Item));
                    if (s == NULL) {
                        puts("Error not enough memory for LStr allocation");
                        freeLStr(s);
                        return NULL;
                    }
                    last->next = tail;
                    tail->next = NULL;
                }
                tail->c = buf[len];
                last = tail;
                tail = last->next;
            }
            free_space -= len;
        } 

    } while (n == 0 || (len == BUF_MAX_SIZE && free_space >= 0));
    freeLStr(tail);
    if (n < 0)
        return NULL;
    last->next = NULL;    
    return s;
}

void printLStr(LStr s) {
    while (s != NULL) {
        printf("%c", s->c);
        s = s->next;
    }
    puts("");
}

void freeLStr(LStr s) {
    while (s != NULL) {
        LStr tmp = s->next;
        free(s);
        s = tmp;
    }
}

Item *getTail(LStr s) {
    while (s->next != NULL) s = s->next;
    return s;
}

LStr cutWord(LStr *s) {
    LStr word = skipSpaces(*s);
    LStr tail = skipnSpaces(word);
    // break links
    if (tail != NULL) {
        *s = tail->next;
        tail->next = NULL;
    } else
        *s = NULL;
    return word;
}

LStr skipSpaces(LStr s) {
    while (s != NULL && (s->c == ' ' || s->c == '\t')) s = s->next;
    return s;
}

LStr skipnSpaces(LStr s) {
    while (s != NULL && s->c != ' ' && s->c != '\t') s = s->next;
    return s;
}

int countChar(LStr s, char c) {
    int cnt = 0;
    while (s != NULL) {
        if (s->c == c)
            cnt++;
        s = s->next;
    }
    return cnt;
}