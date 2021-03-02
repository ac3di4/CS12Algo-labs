/*
string implementation with linked lists
made as universal as possible

[skip should be reworked]
*/

/// linked list node struct
typedef struct Item {
    char c;
    struct Item *next;
} Item;

/// LString is always a pointer to chain of items
#define LStr Item *
/// max size of LString
#define LSTR_MAX_SIZE 2048

/// read line into allocated LString
/// auto malloc for new elements and
/// auto free for unused
/// if arg is NULL, then new LString created
/// LStr * adds additional difficulties and may be slower
LStr readLine(LStr);

/// print out LString (with '\n')
void printLStr(LStr);

/// free LStr
void freeLStr(LStr);

/// get LString last element, NULL arg
/// is not expected
Item *getTail(LStr);

/// cuts out word from LString
LStr cutWord(LStr *);
/// skips all spaces (' ' or '\t')
LStr skipSpaces(LStr);
/// skips all non-spaces (not ' ' or '\t')
LStr skipnSpaces(LStr);

/// count chars in LString
int countChar(LStr, char);


// chainLStr
// count