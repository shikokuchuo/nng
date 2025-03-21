//
// Copyright 2025 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
#include <sys/select.h>
#include <sys/time.h>
#define PLATFD int
#else
#include <winsock2.h>
// order counts
#include <mswsock.h>
#define PLATFD SOCKET
#endif

#include <nng/nng.h>

#include <nuts.h>

const char *addr = "inproc://bug346";

void
repthr(void *arg)
{
	nng_socket   rep = *(nng_socket *) arg;
	nng_listener l;
	int          ifd;
	PLATFD       fd;

	nng_listen(rep, addr, &l, NNG_FLAG_NONBLOCK);

	nng_socket_get_recv_poll_fd(rep, &ifd);
	fd = ifd;

	for (;;) {
		fd_set         fset;
		struct timeval tmo;
		nng_msg       *msg;

		FD_ZERO(&fset);
		FD_SET(fd, &fset);

		tmo.tv_sec  = 0;
		tmo.tv_usec = 20 * 1000; // 20 msec

		select(1, &fset, NULL, NULL, &tmo);

		for (;;) {
			int rv;
			rv = nng_recvmsg(rep, &msg, NNG_FLAG_NONBLOCK);
			if (rv != 0) {
				return;
			}
			nng_msg_clear(msg);
			nng_msg_append_u32(msg, 0);
			rv = nng_sendmsg(rep, msg, NNG_FLAG_NONBLOCK);
			if (rv == NNG_ECLOSED) {
				return;
			}
		}
	}
}

void
reqthr(void *arg)
{
	nng_socket req = *(nng_socket *) arg;

	nng_dial(req, addr, NULL, NNG_FLAG_NONBLOCK);

	int query = 0;
	// We just keep pounding out requests, no wait for response.
	for (;;) {
		int rv;
		rv = nng_send(req, &query, sizeof(query), 0);
		if (rv == NNG_ECLOSED) {
			return;
		}
		nng_msleep(50);
	}
}

#define NCLIENTS 10
nng_socket reqs[NCLIENTS];
nng_socket rep;

static void
test_nonblocking(void)
{
	nng_thread *server;
	nng_thread *clients[NCLIENTS];

	NUTS_PASS(nng_rep0_open(&rep));
	for (int i = 0; i < NCLIENTS; i++) {
		NUTS_PASS(nng_req0_open(&reqs[i]));
	}

	NUTS_PASS(nng_thread_create(&server, repthr, &rep));
	for (int i = 0; i < NCLIENTS; i++) {
		NUTS_PASS(nng_thread_create(&clients[i], reqthr, &reqs[i]));
	}

	nng_msleep(15000);
	nng_socket_close(rep);
	nng_thread_destroy(server);
	for (int i = 0; i < NCLIENTS; i++) {
		nng_socket_close(reqs[i]);
		nng_thread_destroy(clients[i]);
	}
}

NUTS_TESTS = {
	{ "nonblocking", test_nonblocking },
	{ NULL, NULL },
};
