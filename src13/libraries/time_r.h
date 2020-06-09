#include <time.h>
struct tm * gmtime_r (time_t const *t, struct tm *tp);
struct tm * localtime_r (time_t const *t, struct tm *tp);
