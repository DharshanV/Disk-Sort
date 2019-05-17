#ifndef DEBUG_MACROS_H
#define DEBUG_MACROS_H
const bool DEBUG = 0;
#define DEBUG(x) do { \
  if (DEBUG) cerr << x <<"\n"; \
} while (false)
#endif // !DEBUG_MACROS_H
