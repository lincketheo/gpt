#define cqueue_type(type, suffix) \
  typedef struct {                \
    type* base;                   \
    unsigned int head;            \
    unsigned int len;             \
    unsigned int cap;             \
  } type##_cqueue

#define _TAIL(q) (((q)->head + (q)->len) % (q)->cap)

#define _TAIL_INC(q) (((q)->head + (q)->len++) % (q)->cap)

#define CQ_INIT(cq, _cap, alloc)                                     \
  do {                                                               \
    (cq).base = _cap == 0 ? 0 : alloc((_cap) * sizeof *((cq).base)); \
    (cq).head = 0;                                                   \
    (cq).len = 0;                                                    \
    (cq).cap = (_cap);                                               \
  } while (0);

#define CQ_EMPTY(q) ((q)->len == 0)

#define CQ_FULL(q) ((q)->len == (q)->cap)

#define CQ_PUSH(q, e) ( \
    (q)->base[_TAIL_INC(q)] = e)

#define CQ_POP(q) (                         \
    (q)->len--,                             \
    (q)->head = ((q)->head + 1) % (q)->cap, \
    (q)->base[(q)->head == 0 ? (q)->cap - 1 : (q)->head - 1])

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CQ_FULL_1(q, buf, len)                   \
  do {                                           \
    buf = &(q)->base[(q)->head];                 \
    long ret = (long)_TAIL(q) - (long)(q)->head; \
    if (ret < 0) {                               \
      len = (q)->cap - (q)->head;                \
    } else {                                     \
      len = (size_t)ret;                         \
    }                                            \
  } while (0)

#define CQ_FULL_2(q, buf, len) \
  do {                         \
    size_t ret = _TAIL(q);     \
    if (ret < q->head) {       \
      len = ret;               \
      buf = &q->base[0];       \
    } else {                   \
      len = 0;                 \
      buf = NULL;              \
    }                          \
  } while (0)

#define CQ_AVAIL_1(q, buf, len)              \
  do {                                       \
    size_t tail = _TAIL(q);                  \
    buf = &(q)->base[tail];                  \
    long ret = (long)(q)->head - (long)tail; \
    if (ret < 0) {                           \
      len = (q)->cap - tail;                 \
    } else {                                 \
      len = (size_t)ret;                     \
    }                                        \
  } while (0)

#define CQ_AVAIL_2(q, buf, len) \
  do {                          \
    size_t tail = _TAIL(q);     \
    if (tail > (q)->head) {     \
      len = (q)->head;          \
      buf = &(q)->base[0];      \
    } else {                    \
      len = 0;                  \
      buf = NULL;               \
    }                           \
  } while (0)
