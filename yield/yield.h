#ifndef YIELD_H
#define YIELD_H

#include <stdint.h>
#include <stdbool.h>

#define BEGIN_YIELDABLE(fn, context) \
  static YieldingFn_t __this_fn__ = fn; switch(context.resumePoint) { default:

#define END_YIELDABLE }

#define YIELD(context, value) \
    context.resumePoint = __LINE__; \
    yield(__this_fn__, context); \
    return value; \
  case __LINE__:

typedef struct {
  void* data;
  uint32_t resumePoint;
} Context_t;

typedef int (*YieldingFn_t)(Context_t context);

void init(void);

bool enqueue(YieldingFn_t fn, Context_t context);
void yield(YieldingFn_t fn, Context_t context);

void run(void);

#endif
