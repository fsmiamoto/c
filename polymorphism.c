// Based on listing 9.56 of Low-Level Programming by Igor Zhirkov book.
#include <stdio.h>
#include <stdbool.h>

#define pair(T) pair_##T
#define any(T) pair_##T##_any

#define MKPAIR(T) struct pair(T) {\
    T fst; \
    T snd; \
}; \
bool pair_##T##_any(struct pair(T) pair, bool (*predicate)(T)) {\
    return predicate(pair.fst) || predicate(pair.snd); \
}

MKPAIR(int);

bool is_positive(int a) { return a > 0;}

int main(int argc, char** argv) {
    struct pair(int) obj;
    obj.fst = -1;
    obj.snd = -1;
    printf("%d\n",any(int)(obj,is_positive));
    return 0;
}
