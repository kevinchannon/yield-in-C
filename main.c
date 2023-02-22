// yield.cpp : Defines the entry point for the application.
//

#include "yield.h"

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
  int var_1;
  const char* var_2;
  double var_3[3];
} TestFnParams_t;

int testFn(Context_t ctx) {

  TestFnParams_t* params = (TestFnParams_t*)ctx.data;

  BEGIN_YIELDABLE(testFn, ctx)

  printf("Context = { %d, \"%s\", [ %f, %f, %f ] }\n",
    params->var_1,
    params->var_2,
    params->var_3[0], params->var_3[1], params->var_3[2]);

  params->var_1 = 2;
  params->var_3[1] += 1.5;

  YIELD(ctx, 0)

    printf("Context = { %d, \"%s\", [ %f, %f, %f ] }\n",
      params->var_1,
      params->var_2,
      params->var_3[0], params->var_3[1], params->var_3[2]);

  params->var_1 = 3;
  params->var_3[1] += 1.5;

  YIELD(ctx, 0)

    printf("Context = { %d, \"%s\", [ %f, %f, %f ] }\n",
      params->var_1,
      params->var_2,
      params->var_3[0], params->var_3[1], params->var_3[2]);

  params->var_1 = 4;
  params->var_3[1] += 1.5;
  params->var_2 = "Something else";

  YIELD(ctx, 0)

    printf("Context = { %d, \"%s\", [ %f, %f, %f ] }\n",
      params->var_1,
      params->var_2,
      params->var_3[0], params->var_3[1], params->var_3[2]);

  params->var_1 = 5;
  params->var_3[1] += 1.5;
    
  YIELD(ctx, 0)

    printf("Context = { %d, \"%s\", [ %f, %f, %f ] }\n",
      params->var_1,
      params->var_2,
      params->var_3[0], params->var_3[1], params->var_3[2]);

  params->var_3[1] += 1.5;

  END_YIELDABLE

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
  int var_1;
  const char* var_2;
  double var_3[3];
} TestFn2Params_t;

int interceedingFn(Context_t ctx) {
  (void)ctx;

  printf(__FUNCTION__ "\n");

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
  init();

  TestFnParams_t params = { 1, "Hello!", { 1.2, 3.4, 5.6} };
  Context_t ctx = { &params, 0 };

  enqueue(testFn, ctx);

  Context_t dummy = { 0 };
  enqueue(interceedingFn, dummy);

  run();

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

