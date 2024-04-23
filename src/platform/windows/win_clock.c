//
// Copyright 2024 Garrett D'Amore <garrett@damore.org>
// Copyright 2017 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include "core/nng_impl.h"

#include <time.h>

#ifdef NNG_PLATFORM_WINDOWS

nni_time
nni_clock(void)
{
	return (GetTickCount64());
}

int
nni_time_get(uint64_t *seconds, uint32_t *nanoseconds)
{
#if defined(NNG_HAVE_TIMESPEC_GET)
  int             rv;
	struct timespec ts;
	if ((rv = timespec_get(&ts, TIME_UTC)) == TIME_UTC) {
		*seconds     = ts.tv_sec;
		*nanoseconds = ts.tv_nsec;
		return (0);
	}
#endif
	return (nni_win_error(GetLastError()));
}

void
nni_msleep(nni_duration dur)
{
	uint64_t exp;

	exp = (uint64_t) GetTickCount64() + dur;

	Sleep((DWORD) dur);
	while ((uint64_t) GetTickCount64() < exp) {
		Sleep(1);
	}
}

#endif // NNG_PLATFORM_WINDOWS
