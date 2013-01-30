#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <CoreServices/CoreServices.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>

uint64_t GetPIDTimeInNanoseconds(void)
{
  uint64_t        start;
  uint64_t        end;
  uint64_t        elapsed;
  uint64_t        elapsedNano;
  static mach_timebase_info_data_t    sTimebaseInfo;

  // Start the clock.

  start = mach_absolute_time();

  // Call getpid. This will produce inaccurate results because 
  // we're only making a single system call. For more accurate 
  // results you should call getpid multiple times and average 
  // the results.

  (void) getpid();

  // Stop the clock.

  end = mach_absolute_time();

  // Calculate the duration.

  elapsed = end - start;

  // Convert to nanoseconds.

  // If this is the first time we've run, get the timebase.
  // We can use denom == 0 to indicate that sTimebaseInfo is 
  // uninitialised because it makes no sense to have a zero 
  // denominator is a fraction.

  if ( sTimebaseInfo.denom == 0 ) {
    (void) mach_timebase_info(&sTimebaseInfo);
  }

  // Do the maths. We hope that the multiplication doesn't 
  // overflow; the price you pay for working in fixed point.

  elapsedNano = elapsed * sTimebaseInfo.numer / sTimebaseInfo.denom;

  return elapsedNano;
}

#endif
