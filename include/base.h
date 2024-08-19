////////////////////////////////////////////////////
////////// Section: Common
#define STMNT(expr) \
  do {              \
    expr;           \
  } while (0)

#define ENABLE_ASSERT 1
#if !defined(AssertBreak)
#define AssertBreak() (*(volatile int*)0 = 0)
#endif
#if ENABLE_ASSERT
#define ASSERT(expr) STMNT(if (!(expr)) { AssertBreak(); })
#else
#define ASSERT(expr)
#endif

#define IN_INC(val, min, max) ((val) >= (min) && (val) <= (max))

#define ISALPHANUMERIC(ch) (IN_INC(ch, 'A', 'Z') || IN_INC(ch, 'a', 'z') || IN_INC(ch, '0', '9'))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

////////////////////////////////////////////////////
////////// Section: Bytes
#define BIT_MASK8_R(n) (1 << (n))
#define BIT_MASK8_L(n) (1 << (7 - n))
#define BIT_AT_L(d, n) ((d & BIT_MASK8_L(n)) >> (7 - n))
#define BIT_AT_R(d, n) ((d & BIT_MASK8_R(n)) >> (n))

#define SET_BIT_ARR_ON(data, bit) data[bit / 8] |= BIT_MASK8_L(bit % 8)
#define SET_BIT_ARR_OFF(data, bit) data[bit / 8] &= ~BIT_MASK8_L(bit % 8)
#define BIT_ARR_AT(data, bit) BIT_AT_L(data[bit / 8], bit % 8)

////////////////////////////////////////////////////
////////// Section: Data Structures
/// Singly Linked List
#define LL_PUSH(h, n, v) \
  do {                   \
    (n)->val = (v);      \
    if ((h) == NULL) {   \
      (h) = (n);         \
      (n)->next = NULL;  \
    } else {             \
      (n)->next = (h);   \
      (h) = (n);         \
    }                    \
  } while (0);
