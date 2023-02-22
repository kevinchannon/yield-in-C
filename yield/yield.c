#include "yield.h"

#include <string.h>

#define MAX_QUEUE_SIZE 100

static YieldingFn_t job_queue[MAX_QUEUE_SIZE] = { 0 };
static Context_t context_queue[MAX_QUEUE_SIZE] = { 0 };
static uint32_t resume_point_queue[MAX_QUEUE_SIZE] = { 0 };
static uint32_t frontPosition = 0;
static uint32_t backPosition = 0;

void init(void)
{
  memset(job_queue, 0, MAX_QUEUE_SIZE * sizeof(YieldingFn_t));
  memset(context_queue, 0, MAX_QUEUE_SIZE * sizeof(Context_t));
  memset(resume_point_queue, 0, MAX_QUEUE_SIZE * sizeof(uint32_t));
  frontPosition = 0;
  backPosition = 0;
}

bool enqueue(YieldingFn_t fn, Context_t context)
{
  if (backPosition - frontPosition > MAX_QUEUE_SIZE) {
    return false;
  }

  uint32_t insertIndex = (backPosition++) % MAX_QUEUE_SIZE;
  job_queue[insertIndex] = fn;

  context.resumePoint = 0;
  context_queue[insertIndex] = context;

  return true;
}

void yield(YieldingFn_t fn, Context_t context)
{
  if (backPosition - frontPosition > MAX_QUEUE_SIZE) {
    return;
  }

  uint32_t insertIndex = (backPosition++) % MAX_QUEUE_SIZE;
  job_queue[insertIndex] = fn;
  context_queue[insertIndex] = context;
}

void run(void)
{
  while (frontPosition < backPosition) {
    uint32_t extractIndex = (frontPosition++) % MAX_QUEUE_SIZE;

    if (0 != job_queue[extractIndex](context_queue[extractIndex])) {
      return;
    }
  }
}
