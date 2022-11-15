#include <sys/time.h>
#include <locale.h>

#define PRINT_TIME_KEEPING(FD, FORE_COLOR) fprintf(FD, FORE_COLOR "%'10lu µs\t" FORE_RESET , timekeeping_get());

struct timeval timekeeping_time;

// https://www.gnu.org/software/libc/manual/html_node/Calculating-Elapsed-Time.html
int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y)
{
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec)
    {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000)
    {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }

    /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;

    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}

void timekeeping_init() {
    gettimeofday(&timekeeping_time, NULL);
    setlocale(LC_NUMERIC, ""); // for %' 10lu
}

unsigned long timekeeping_get()
{
    struct timeval current, delta;
    gettimeofday(&current, NULL);
    timeval_subtract(&delta, &current, &timekeeping_time);
    return delta.tv_sec * 1000000 + delta.tv_usec;
}