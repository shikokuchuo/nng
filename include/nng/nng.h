//
// Copyright 2024 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef NNG_NNG_H
#define NNG_NNG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef NNG_DECL
#if defined(_WIN32) && !defined(NNG_STATIC_LIB)
#if defined(NNG_SHARED_LIB)
#define NNG_DECL __declspec(dllexport)
#else
#define NNG_DECL __declspec(dllimport)
#endif // NNG_SHARED_LIB
#else
#if defined(NNG_SHARED_LIB) && defined(NNG_HIDDEN_VISIBILITY)
#define NNG_DECL __attribute__((visibility("default")))
#else
#define NNG_DECL extern
#endif
#endif // _WIN32 && !NNG_STATIC_LIB
#endif // NNG_DECL

#ifndef NNG_DEPRECATED
#if defined(__GNUC__) || defined(__clang__)
#define NNG_DEPRECATED __attribute__((deprecated))
#else
#define NNG_DEPRECATED
#endif
#endif

#define NNG_MAJOR_VERSION 1
#define NNG_MINOR_VERSION 7
#define NNG_PATCH_VERSION 3
#define NNG_RELEASE_SUFFIX \
	"" // if non-empty (i.e. "pre"), this is a pre-release

#define NNG_MAXADDRLEN (128)

<<<<<<< HEAD
// NNG_PROTOCOL_NUMBER is used by protocol headers to calculate their
// protocol number from a major and minor number.  Applications should
// probably not need to use this.
#define NNG_PROTOCOL_NUMBER(maj, min) (((x) * 16) + (y))
=======
#define NNG_PROTOCOL_NUMBER(maj, min) (((x) *16) + (y))
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)

typedef struct nng_ctx_s {
	uint32_t id;
} nng_ctx;

typedef struct nng_dialer_s {
	uint32_t id;
} nng_dialer;

typedef struct nng_listener_s {
	uint32_t id;
} nng_listener;

typedef struct nng_pipe_s {
	uint32_t id;
} nng_pipe;

typedef struct nng_socket_s {
	uint32_t id;
} nng_socket;

typedef int32_t nng_duration; // in milliseconds

// nng_time represents an absolute time since some arbitrary point in the
// past, measured in milliseconds.  The values are always positive.
typedef uint64_t nng_time;

typedef struct nng_msg  nng_msg;
typedef struct nng_stat nng_stat;
typedef struct nng_aio  nng_aio;

// Initializers.
// clang-format off
#define NNG_PIPE_INITIALIZER { 0 }
#define NNG_SOCKET_INITIALIZER { 0 }
#define NNG_DIALER_INITIALIZER { 0 }
#define NNG_LISTENER_INITIALIZER { 0 }
#define NNG_CTX_INITIALIZER { 0 }
// clang-format on

struct nng_sockaddr_inproc {
	uint16_t sa_family;
	char     sa_name[NNG_MAXADDRLEN];
};

struct nng_sockaddr_path {
	uint16_t sa_family;
	char     sa_path[NNG_MAXADDRLEN];
};

struct nng_sockaddr_in6 {
	uint16_t sa_family;
	uint16_t sa_port;
	uint8_t  sa_addr[16];
	uint32_t sa_scope;
};
struct nng_sockaddr_in {
	uint16_t sa_family;
	uint16_t sa_port;
	uint32_t sa_addr;
};

struct nng_sockaddr_zt {
	uint16_t sa_family;
	uint64_t sa_nwid;
	uint64_t sa_nodeid;
	uint32_t sa_port;
};

struct nng_sockaddr_abstract {
	uint16_t sa_family;
	uint16_t sa_len;       // will be 0 - 107 max.
	uint8_t  sa_name[107]; // 108 linux/windows, without leading NUL
};

<<<<<<< HEAD
// nng_sockaddr_storage is the size required to store any nng_sockaddr.
// This size must not change, and no individual nng_sockaddr type may grow
// larger than this without breaking binary compatibility.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
struct nng_sockaddr_storage {
	uint16_t sa_family;
	uint64_t sa_pad[16];
};

typedef struct nng_sockaddr_inproc   nng_sockaddr_inproc;
typedef struct nng_sockaddr_path     nng_sockaddr_path;
typedef struct nng_sockaddr_path     nng_sockaddr_ipc;
typedef struct nng_sockaddr_in       nng_sockaddr_in;
typedef struct nng_sockaddr_in6      nng_sockaddr_in6;
typedef struct nng_sockaddr_zt       nng_sockaddr_zt;
typedef struct nng_sockaddr_abstract nng_sockaddr_abstract;
typedef struct nng_sockaddr_storage  nng_sockaddr_storage;

typedef union nng_sockaddr {
	uint16_t              s_family;
	nng_sockaddr_ipc      s_ipc;
	nng_sockaddr_inproc   s_inproc;
	nng_sockaddr_in6      s_in6;
	nng_sockaddr_in       s_in;
	nng_sockaddr_zt       s_zt;
	nng_sockaddr_abstract s_abstract;
	nng_sockaddr_storage  s_storage;
} nng_sockaddr;

enum nng_sockaddr_family {
	NNG_AF_UNSPEC   = 0,
	NNG_AF_INPROC   = 1,
	NNG_AF_IPC      = 2,
	NNG_AF_INET     = 3,
	NNG_AF_INET6    = 4,
	NNG_AF_ZT       = 5, // ZeroTier
	NNG_AF_ABSTRACT = 6
};

typedef struct nng_iov {
	void  *iov_buf;
	size_t iov_len;
} nng_iov;

#define NNG_DURATION_INFINITE (-1)
#define NNG_DURATION_DEFAULT (-2)
#define NNG_DURATION_ZERO (0)

NNG_DECL void nng_fini(void);

NNG_DECL int nng_close(nng_socket);

NNG_DECL int nng_socket_id(nng_socket);

NNG_DECL int nng_socket_set(nng_socket, const char *, const void *, size_t);
NNG_DECL int nng_socket_set_bool(nng_socket, const char *, bool);
NNG_DECL int nng_socket_set_int(nng_socket, const char *, int);
NNG_DECL int nng_socket_set_size(nng_socket, const char *, size_t);
NNG_DECL int nng_socket_set_uint64(nng_socket, const char *, uint64_t);
NNG_DECL int nng_socket_set_string(nng_socket, const char *, const char *);
NNG_DECL int nng_socket_set_ptr(nng_socket, const char *, void *);
NNG_DECL int nng_socket_set_ms(nng_socket, const char *, nng_duration);
NNG_DECL int nng_socket_set_addr(
    nng_socket, const char *, const nng_sockaddr *);

NNG_DECL int nng_socket_get(nng_socket, const char *, void *, size_t *);
NNG_DECL int nng_socket_get_bool(nng_socket, const char *, bool *);
NNG_DECL int nng_socket_get_int(nng_socket, const char *, int *);
NNG_DECL int nng_socket_get_size(nng_socket, const char *, size_t *);
NNG_DECL int nng_socket_get_uint64(nng_socket, const char *, uint64_t *);
NNG_DECL int nng_socket_get_string(nng_socket, const char *, char **);
NNG_DECL int nng_socket_get_ptr(nng_socket, const char *, void **);
NNG_DECL int nng_socket_get_ms(nng_socket, const char *, nng_duration *);
NNG_DECL int nng_socket_get_addr(nng_socket, const char *, nng_sockaddr *);

typedef enum {
	NNG_PIPE_EV_ADD_PRE,  // Called just before pipe added to socket
	NNG_PIPE_EV_ADD_POST, // Called just after pipe added to socket
	NNG_PIPE_EV_REM_POST, // Called just after pipe removed from socket
	NNG_PIPE_EV_NUM,      // Used internally, must be last.
} nng_pipe_ev;

typedef void (*nng_pipe_cb)(nng_pipe, nng_pipe_ev, void *);

NNG_DECL int nng_pipe_notify(nng_socket, nng_pipe_ev, nng_pipe_cb, void *);

NNG_DECL int nng_listen(nng_socket, const char *, nng_listener *, int);

NNG_DECL int nng_dial(nng_socket, const char *, nng_dialer *, int);

NNG_DECL int nng_dialer_create(nng_dialer *, nng_socket, const char *);

NNG_DECL int nng_listener_create(nng_listener *, nng_socket, const char *);

NNG_DECL int nng_dialer_start(nng_dialer, int);

NNG_DECL int nng_listener_start(nng_listener, int);

NNG_DECL int nng_dialer_close(nng_dialer);

NNG_DECL int nng_listener_close(nng_listener);

NNG_DECL int nng_dialer_id(nng_dialer);

NNG_DECL int nng_listener_id(nng_listener);

NNG_DECL int nng_dialer_set(nng_dialer, const char *, const void *, size_t);
NNG_DECL int nng_dialer_set_bool(nng_dialer, const char *, bool);
NNG_DECL int nng_dialer_set_int(nng_dialer, const char *, int);
NNG_DECL int nng_dialer_set_size(nng_dialer, const char *, size_t);
NNG_DECL int nng_dialer_set_uint64(nng_dialer, const char *, uint64_t);
NNG_DECL int nng_dialer_set_string(nng_dialer, const char *, const char *);
NNG_DECL int nng_dialer_set_ptr(nng_dialer, const char *, void *);
NNG_DECL int nng_dialer_set_ms(nng_dialer, const char *, nng_duration);
NNG_DECL int nng_dialer_set_addr(
    nng_dialer, const char *, const nng_sockaddr *);

NNG_DECL int nng_dialer_get(nng_dialer, const char *, void *, size_t *);
NNG_DECL int nng_dialer_get_bool(nng_dialer, const char *, bool *);
NNG_DECL int nng_dialer_get_int(nng_dialer, const char *, int *);
NNG_DECL int nng_dialer_get_size(nng_dialer, const char *, size_t *);
NNG_DECL int nng_dialer_get_uint64(nng_dialer, const char *, uint64_t *);
NNG_DECL int nng_dialer_get_string(nng_dialer, const char *, char **);
NNG_DECL int nng_dialer_get_ptr(nng_dialer, const char *, void **);
NNG_DECL int nng_dialer_get_ms(nng_dialer, const char *, nng_duration *);
NNG_DECL int nng_dialer_get_addr(nng_dialer, const char *, nng_sockaddr *);

NNG_DECL int nng_listener_set(
    nng_listener, const char *, const void *, size_t);
NNG_DECL int nng_listener_set_bool(nng_listener, const char *, bool);
NNG_DECL int nng_listener_set_int(nng_listener, const char *, int);
NNG_DECL int nng_listener_set_size(nng_listener, const char *, size_t);
NNG_DECL int nng_listener_set_uint64(nng_listener, const char *, uint64_t);
NNG_DECL int nng_listener_set_string(nng_listener, const char *, const char *);
NNG_DECL int nng_listener_set_ptr(nng_listener, const char *, void *);
NNG_DECL int nng_listener_set_ms(nng_listener, const char *, nng_duration);
NNG_DECL int nng_listener_set_addr(
    nng_listener, const char *, const nng_sockaddr *);

NNG_DECL int nng_listener_get(nng_listener, const char *, void *, size_t *);
NNG_DECL int nng_listener_get_bool(nng_listener, const char *, bool *);
NNG_DECL int nng_listener_get_int(nng_listener, const char *, int *);
NNG_DECL int nng_listener_get_size(nng_listener, const char *, size_t *);
NNG_DECL int nng_listener_get_uint64(nng_listener, const char *, uint64_t *);
NNG_DECL int nng_listener_get_string(nng_listener, const char *, char **);
NNG_DECL int nng_listener_get_ptr(nng_listener, const char *, void **);
NNG_DECL int nng_listener_get_ms(nng_listener, const char *, nng_duration *);
NNG_DECL int nng_listener_get_addr(nng_listener, const char *, nng_sockaddr *);

<<<<<<< HEAD
// nng_strerror returns a human-readable string associated with the error
// code supplied.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL const char *nng_strerror(int);

NNG_DECL int nng_send(nng_socket, void *, size_t, int);

NNG_DECL int nng_recv(nng_socket, void *, size_t *, int);

<<<<<<< HEAD
// nng_sendmsg is like nng_send, but offers up a message structure, which
// gives the ability to provide more control over the message, including
// providing backtrace information.  It also can take a message that was
// obtained via nn_recvmsg, allowing for zero copy forwarding.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL int nng_sendmsg(nng_socket, nng_msg *, int);

NNG_DECL int nng_recvmsg(nng_socket, nng_msg **, int);

<<<<<<< HEAD
// nng_send_aio sends data on the socket asynchronously.  As with nng_send,
// the completion may be executed before the data has actually been delivered,
// but only when it is accepted for delivery.  The supplied AIO must have
// been initialized, and have an associated message.  The message will be
// "owned" by the socket if the operation completes successfully.  Otherwise,
// the caller is responsible for freeing it.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL void nng_send_aio(nng_socket, nng_aio *);

NNG_DECL void nng_recv_aio(nng_socket, nng_aio *);

NNG_DECL int nng_ctx_open(nng_ctx *, nng_socket);

NNG_DECL int nng_ctx_close(nng_ctx);

NNG_DECL int nng_ctx_id(nng_ctx);

NNG_DECL void nng_ctx_recv(nng_ctx, nng_aio *);

<<<<<<< HEAD
// nng_ctx_recvmsg allows for receiving a message synchronously using
// a context.  It has the same semantics as nng_recvmsg, but operates
// on a context instead of a socket.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL int nng_ctx_recvmsg(nng_ctx, nng_msg **, int);

NNG_DECL void nng_ctx_send(nng_ctx, nng_aio *);

NNG_DECL int nng_ctx_sendmsg(nng_ctx, nng_msg *, int);

NNG_DECL int nng_ctx_get(nng_ctx, const char *, void *, size_t *);
NNG_DECL int nng_ctx_get_bool(nng_ctx, const char *, bool *);
NNG_DECL int nng_ctx_get_int(nng_ctx, const char *, int *);
NNG_DECL int nng_ctx_get_size(nng_ctx, const char *, size_t *);
NNG_DECL int nng_ctx_get_uint64(nng_ctx, const char *, uint64_t *);
NNG_DECL int nng_ctx_get_string(nng_ctx, const char *, char **);
NNG_DECL int nng_ctx_get_ptr(nng_ctx, const char *, void **);
NNG_DECL int nng_ctx_get_ms(nng_ctx, const char *, nng_duration *);
NNG_DECL int nng_ctx_get_addr(nng_ctx, const char *, nng_sockaddr *);

NNG_DECL int nng_ctx_set(nng_ctx, const char *, const void *, size_t);
NNG_DECL int nng_ctx_set_bool(nng_ctx, const char *, bool);
NNG_DECL int nng_ctx_set_int(nng_ctx, const char *, int);
NNG_DECL int nng_ctx_set_size(nng_ctx, const char *, size_t);
NNG_DECL int nng_ctx_set_uint64(nng_ctx, const char *, uint64_t);
NNG_DECL int nng_ctx_set_string(nng_ctx, const char *, const char *);
NNG_DECL int nng_ctx_set_ptr(nng_ctx, const char *, void *);
NNG_DECL int nng_ctx_set_ms(nng_ctx, const char *, nng_duration);
NNG_DECL int nng_ctx_set_addr(nng_ctx, const char *, const nng_sockaddr *);

NNG_DECL void *nng_alloc(size_t);

NNG_DECL void nng_free(void *, size_t);

NNG_DECL char *nng_strdup(const char *);

NNG_DECL void nng_strfree(char *);

NNG_DECL int nng_aio_alloc(nng_aio **, void (*)(void *), void *);

NNG_DECL void nng_aio_free(nng_aio *);

NNG_DECL void nng_aio_reap(nng_aio *);

<<<<<<< HEAD
// nng_aio_stop stops any outstanding operation, and waits for the
// AIO to be free, including for the callback to have completed
// execution.  Therefore, the caller must NOT hold any locks that
// are acquired in the callback, or deadlock will occur.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL void nng_aio_stop(nng_aio *);

NNG_DECL int nng_aio_result(nng_aio *);

NNG_DECL size_t nng_aio_count(nng_aio *);

NNG_DECL void nng_aio_cancel(nng_aio *);

NNG_DECL void nng_aio_abort(nng_aio *, int);

NNG_DECL void nng_aio_wait(nng_aio *);

NNG_DECL bool nng_aio_busy(nng_aio *);

NNG_DECL void nng_aio_set_msg(nng_aio *, nng_msg *);

NNG_DECL nng_msg *nng_aio_get_msg(nng_aio *);

NNG_DECL int nng_aio_set_input(nng_aio *, unsigned, void *);

NNG_DECL void *nng_aio_get_input(nng_aio *, unsigned);

NNG_DECL int nng_aio_set_output(nng_aio *, unsigned, void *);

NNG_DECL void *nng_aio_get_output(nng_aio *, unsigned);

NNG_DECL void nng_aio_set_timeout(nng_aio *, nng_duration);

<<<<<<< HEAD
// nng_aio_set_expire is like nng_aio_set_timeout, except it sets an absolute
// expiration time.  This is useful when chaining actions on a single aio
// as part of a state machine.
NNG_DECL void nng_aio_set_expire(nng_aio *, nng_time);

// nng_aio_set_iov sets a scatter/gather vector on the aio.  The iov array
// itself is copied. Data members (the memory regions referenced) *may* be
// copied as well, depending on the operation.  This operation is guaranteed
// to succeed if n <= 4, otherwise it may fail due to NNG_ENOMEM.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL int nng_aio_set_iov(nng_aio *, unsigned, const nng_iov *);

NNG_DECL bool nng_aio_begin(nng_aio *);

NNG_DECL void nng_aio_finish(nng_aio *, int);

<<<<<<< HEAD
// nng_aio_defer is used to register a cancellation routine, and indicate
// that the operation will be completed asynchronously.  It must only be
// called once per operation on an aio, and must only be called by providers.
// If the operation is canceled by the consumer, the cancellation callback
// will be called.  The provider *must* still ensure that the nng_aio_finish()
// function is called EXACTLY ONCE.  If the operation cannot be canceled
// for any reason, the cancellation callback should do nothing.  The
// final argument is passed to the cancelfn.  The final argument of the
// cancellation function is the error number (will not be zero) corresponding
// to the reason for cancellation, e.g. NNG_ETIMEDOUT or NNG_ECANCELED.
typedef void  (*nng_aio_cancelfn)(nng_aio *, void *, int);
=======
typedef void (*nng_aio_cancelfn)(nng_aio *, void *, int);
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL void nng_aio_defer(nng_aio *, nng_aio_cancelfn, void *);

NNG_DECL void nng_sleep_aio(nng_duration, nng_aio *);

NNG_DECL int      nng_msg_alloc(nng_msg **, size_t);
NNG_DECL void     nng_msg_free(nng_msg *);
NNG_DECL int      nng_msg_realloc(nng_msg *, size_t);
NNG_DECL int      nng_msg_reserve(nng_msg *, size_t);
NNG_DECL size_t   nng_msg_capacity(nng_msg *);
NNG_DECL void    *nng_msg_header(nng_msg *);
NNG_DECL size_t   nng_msg_header_len(const nng_msg *);
NNG_DECL void    *nng_msg_body(nng_msg *);
NNG_DECL size_t   nng_msg_len(const nng_msg *);
NNG_DECL int      nng_msg_append(nng_msg *, const void *, size_t);
NNG_DECL int      nng_msg_insert(nng_msg *, const void *, size_t);
NNG_DECL int      nng_msg_trim(nng_msg *, size_t);
NNG_DECL int      nng_msg_chop(nng_msg *, size_t);
NNG_DECL int      nng_msg_header_append(nng_msg *, const void *, size_t);
NNG_DECL int      nng_msg_header_insert(nng_msg *, const void *, size_t);
NNG_DECL int      nng_msg_header_trim(nng_msg *, size_t);
NNG_DECL int      nng_msg_header_chop(nng_msg *, size_t);
NNG_DECL int      nng_msg_header_append_u16(nng_msg *, uint16_t);
NNG_DECL int      nng_msg_header_append_u32(nng_msg *, uint32_t);
NNG_DECL int      nng_msg_header_append_u64(nng_msg *, uint64_t);
NNG_DECL int      nng_msg_header_insert_u16(nng_msg *, uint16_t);
NNG_DECL int      nng_msg_header_insert_u32(nng_msg *, uint32_t);
NNG_DECL int      nng_msg_header_insert_u64(nng_msg *, uint64_t);
NNG_DECL int      nng_msg_header_chop_u16(nng_msg *, uint16_t *);
NNG_DECL int      nng_msg_header_chop_u32(nng_msg *, uint32_t *);
NNG_DECL int      nng_msg_header_chop_u64(nng_msg *, uint64_t *);
NNG_DECL int      nng_msg_header_trim_u16(nng_msg *, uint16_t *);
NNG_DECL int      nng_msg_header_trim_u32(nng_msg *, uint32_t *);
NNG_DECL int      nng_msg_header_trim_u64(nng_msg *, uint64_t *);
NNG_DECL int      nng_msg_append_u16(nng_msg *, uint16_t);
NNG_DECL int      nng_msg_append_u32(nng_msg *, uint32_t);
NNG_DECL int      nng_msg_append_u64(nng_msg *, uint64_t);
NNG_DECL int      nng_msg_insert_u16(nng_msg *, uint16_t);
NNG_DECL int      nng_msg_insert_u32(nng_msg *, uint32_t);
NNG_DECL int      nng_msg_insert_u64(nng_msg *, uint64_t);
NNG_DECL int      nng_msg_chop_u16(nng_msg *, uint16_t *);
NNG_DECL int      nng_msg_chop_u32(nng_msg *, uint32_t *);
NNG_DECL int      nng_msg_chop_u64(nng_msg *, uint64_t *);
NNG_DECL int      nng_msg_trim_u16(nng_msg *, uint16_t *);
NNG_DECL int      nng_msg_trim_u32(nng_msg *, uint32_t *);
NNG_DECL int      nng_msg_trim_u64(nng_msg *, uint64_t *);
NNG_DECL int      nng_msg_dup(nng_msg **, const nng_msg *);
NNG_DECL void     nng_msg_clear(nng_msg *);
NNG_DECL void     nng_msg_header_clear(nng_msg *);
NNG_DECL void     nng_msg_set_pipe(nng_msg *, nng_pipe);
NNG_DECL nng_pipe nng_msg_get_pipe(const nng_msg *);

NNG_DECL int nng_pipe_get(nng_pipe, const char *, void *, size_t *);
NNG_DECL int nng_pipe_get_bool(nng_pipe, const char *, bool *);
NNG_DECL int nng_pipe_get_int(nng_pipe, const char *, int *);
NNG_DECL int nng_pipe_get_ms(nng_pipe, const char *, nng_duration *);
NNG_DECL int nng_pipe_get_size(nng_pipe, const char *, size_t *);
NNG_DECL int nng_pipe_get_uint64(nng_pipe, const char *, uint64_t *);
NNG_DECL int nng_pipe_get_string(nng_pipe, const char *, char **);
NNG_DECL int nng_pipe_get_ptr(nng_pipe, const char *, void **);
NNG_DECL int nng_pipe_get_addr(nng_pipe, const char *, nng_sockaddr *);

NNG_DECL int          nng_pipe_close(nng_pipe);
NNG_DECL int          nng_pipe_id(nng_pipe);
NNG_DECL nng_socket   nng_pipe_socket(nng_pipe);
NNG_DECL nng_dialer   nng_pipe_dialer(nng_pipe);
NNG_DECL nng_listener nng_pipe_listener(nng_pipe);

<<<<<<< HEAD
// Flags.
#define NNG_FLAG_ALLOC 1u    // Recv to allocate receive buffer
=======
#define NNG_FLAG_ALLOC 1u // Recv to allocate receive buffer
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
#define NNG_FLAG_NONBLOCK 2u // Non-blocking operations

#define NNG_OPT_SOCKNAME "socket-name"
#define NNG_OPT_RAW "raw"
#define NNG_OPT_PROTO "protocol"
#define NNG_OPT_PROTONAME "protocol-name"
#define NNG_OPT_PEER "peer"
#define NNG_OPT_PEERNAME "peer-name"
#define NNG_OPT_RECVBUF "recv-buffer"
#define NNG_OPT_SENDBUF "send-buffer"
#define NNG_OPT_RECVFD "recv-fd"
#define NNG_OPT_SENDFD "send-fd"
#define NNG_OPT_RECVTIMEO "recv-timeout"
#define NNG_OPT_SENDTIMEO "send-timeout"
#define NNG_OPT_LOCADDR "local-address"
#define NNG_OPT_REMADDR "remote-address"
#define NNG_OPT_URL "url"
#define NNG_OPT_MAXTTL "ttl-max"
#define NNG_OPT_RECVMAXSZ "recv-size-max"
#define NNG_OPT_RECONNMINT "reconnect-time-min"
#define NNG_OPT_RECONNMAXT "reconnect-time-max"

<<<<<<< HEAD
// TLS options are only used when the underlying transport supports TLS.

// NNG_OPT_TLS_CONFIG is a pointer to a nng_tls_config object.  Generally
// this can be used with endpoints, although once an endpoint is started, or
// once a configuration is used, the value becomes read-only. Note that
// when configuring the object, a hold is placed on the TLS configuration,
// using a reference count.  When retrieving the object, no such hold is
// placed, and so the caller must take care not to use the associated object
// after the endpoint it is associated with is closed.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
#define NNG_OPT_TLS_CONFIG "tls-config"

#define NNG_OPT_TLS_AUTH_MODE "tls-authmode"

<<<<<<< HEAD
// NNG_OPT_TLS_CERT_KEY_FILE names a single file that contains a certificate
// and key identifying the endpoint.  This is a write-only value.  This can be
// set multiple times for different keys/certs corresponding to
// different algorithms on listeners, whereas dialers only support one.  The
// file must contain both cert and key as PEM blocks, and the key must
// not be encrypted.  (If more flexibility is needed, use the TLS configuration
// directly, via NNG_OPT_TLS_CONFIG.)
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
#define NNG_OPT_TLS_CERT_KEY_FILE "tls-cert-key-file"

#define NNG_OPT_TLS_CA_FILE "tls-ca-file"

#define NNG_OPT_TLS_SERVER_NAME "tls-server-name"

<<<<<<< HEAD
// NNG_OPT_TLS_VERIFIED returns a boolean indicating whether the peer has
// been verified (true) or not (false). Typically, this is read-only, and
// only available for pipes. This option may return incorrect results if
// peer authentication is disabled with `NNG_TLS_AUTH_MODE_NONE`.
#define NNG_OPT_TLS_VERIFIED "tls-verified"

// NNG_OPT_TLS_PEER_CN returns the string with the common name
// of the peer certificate. Typically, this is read-only and
// only available for pipes. This option may return incorrect results if
// peer authentication is disabled with `NNG_TLS_AUTH_MODE_NONE`.
=======
#define NNG_OPT_TLS_VERIFIED "tls-verified"

>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
#define NNG_OPT_TLS_PEER_CN "tls-peer-cn"

#define NNG_OPT_TLS_PEER_ALT_NAMES "tls-peer-alt-names"

#define NNG_OPT_TCP_NODELAY "tcp-nodelay"

#define NNG_OPT_TCP_KEEPALIVE "tcp-keepalive"

#define NNG_OPT_TCP_BOUND_PORT "tcp-bound-port"

#define NNG_OPT_IPC_SECURITY_DESCRIPTOR "ipc:security-descriptor"

#define NNG_OPT_IPC_PERMISSIONS "ipc:permissions"

<<<<<<< HEAD
// IPC peer options may also be used in some cases with other socket types.

// Peer UID.  This is only available on POSIX style systems.
#define NNG_OPT_PEER_UID "ipc:peer-uid"
#define NNG_OPT_IPC_PEER_UID NNG_OPT_PEER_UID

// Peer GID (primary group).  This is only available on POSIX style systems.
#define NNG_OPT_PEER_GID "ipc:peer-gid"
#define NNG_OPT_IPC_PEER_GID NNG_OPT_PEER_GID

// Peer process ID.  Available on Windows, Linux, and SunOS.
// In theory, we could obtain this with the first message sent,
// but we have elected not to do this for now. (Nice RFE for a FreeBSD
// guru though.)
#define NNG_OPT_PEER_PID "ipc:peer-pid"
#define NNG_OPT_IPC_PEER_PID NNG_OPT_PEER_PID

// Peer Zone ID.  Only on SunOS systems.  (Linux containers have no
// definable kernel identity; they are a user-land fabrication made up
// from various pieces of different namespaces. FreeBSD does have
// something called JailIDs, but it isn't obvious how to determine this,
// or even if processes can use IPC across jail boundaries.)
#define NNG_OPT_PEER_ZONEID "ipc:peer-zoneid"
#define NNG_OPT_IPC_PEER_ZONEID NNG_OPT_PEER_ZONEID
=======
#define NNG_OPT_IPC_PEER_UID "ipc:peer-uid"

#define NNG_OPT_IPC_PEER_GID "ipc:peer-gid"

#define NNG_OPT_IPC_PEER_PID "ipc:peer-pid"

#define NNG_OPT_IPC_PEER_ZONEID "ipc:peer-zoneid"
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)

#define NNG_OPT_WS_REQUEST_HEADERS "ws:request-headers"

#define NNG_OPT_WS_RESPONSE_HEADERS "ws:response-headers"

#define NNG_OPT_WS_RESPONSE_HEADER "ws:response-header:"

#define NNG_OPT_WS_REQUEST_HEADER "ws:request-header:"

#define NNG_OPT_WS_REQUEST_URI "ws:request-uri"

#define NNG_OPT_WS_SENDMAXFRAME "ws:txframe-max"

#define NNG_OPT_WS_RECVMAXFRAME "ws:rxframe-max"

#define NNG_OPT_WS_PROTOCOL "ws:protocol"

#define NNG_OPT_WS_SEND_TEXT "ws:send-text"

#define NNG_OPT_WS_RECV_TEXT "ws:recv-text"

<<<<<<< HEAD
// NNG_OPT_SOCKET_FD is a write-only integer property that is used to
// file descriptors (or FILE HANDLE objects on Windows) to a
// socket:// based listener.  This file descriptor will be taken
// over and used as a stream connection.  The protocol is compatible
// with SP over TCP.  This facility is experimental, and intended to
// allow use with descriptors created via socketpair() or similar.
// Note that unidirectional pipes (such as those from pipe(2) or mkfifo)
// are not supported.
#define NNG_OPT_SOCKET_FD "socket:fd"

// XXX: TBD: priorities, ipv4only

// Statistics. These are for informational purposes only, and subject
// to change without notice. The API for accessing these is stable,
// but the individual statistic names, values, and meanings are all
// subject to change.

// nng_stats_get takes a snapshot of the entire set of statistics.
// While the operation can be somewhat expensive (allocations), it
// is done in a way that minimizes impact to running operations.
// Note that the statistics are provided as a tree, with parents
// used for grouping, and with child statistics underneath.  The
// top stat returned will be of type NNG_STAT_SCOPE with name "".
// Applications may choose to consider this root scope as "root", if
// the empty string is not suitable.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL int nng_stats_get(nng_stat **);

NNG_DECL void nng_stats_free(nng_stat *);

NNG_DECL void nng_stats_dump(nng_stat *);

NNG_DECL nng_stat *nng_stat_next(nng_stat *);

NNG_DECL nng_stat *nng_stat_child(nng_stat *);

<<<<<<< HEAD
// nng_stat_name is used to determine the name of the statistic.
// This is a human-readable name.  Statistic names, as well as the presence
// or absence or semantic of any particular statistic are not part of any
// stable API, and may be changed without notice in future updates.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL const char *nng_stat_name(nng_stat *);

NNG_DECL int nng_stat_type(nng_stat *);

NNG_DECL nng_stat *nng_stat_find(nng_stat *, const char *);

NNG_DECL nng_stat *nng_stat_find_socket(nng_stat *, nng_socket);

NNG_DECL nng_stat *nng_stat_find_dialer(nng_stat *, nng_dialer);

NNG_DECL nng_stat *nng_stat_find_listener(nng_stat *, nng_listener);

enum nng_stat_type_enum {
	NNG_STAT_SCOPE   = 0, // Stat is for scoping, and carries no value
	NNG_STAT_LEVEL   = 1, // Numeric "absolute" value, diffs meaningless
	NNG_STAT_COUNTER = 2, // Incrementing value (diffs are meaningful)
	NNG_STAT_STRING  = 3, // Value is a string
	NNG_STAT_BOOLEAN = 4, // Value is a boolean
	NNG_STAT_ID      = 5, // Value is a numeric ID
};

NNG_DECL int nng_stat_unit(nng_stat *);

enum nng_unit_enum {
	NNG_UNIT_NONE     = 0, // No special units
	NNG_UNIT_BYTES    = 1, // Bytes, e.g. bytes sent, etc.
	NNG_UNIT_MESSAGES = 2, // Messages, one per message
	NNG_UNIT_MILLIS   = 3, // Milliseconds
	NNG_UNIT_EVENTS   = 4  // Some other type of event
};

<<<<<<< HEAD
// nng_stat_value returns the actual value of the statistic.
// Statistic values reflect their value at the time that the corresponding
// snapshot was updated, and are undefined until an update is performed.
NNG_DECL uint64_t nng_stat_value(nng_stat *);

// nng_stat_bool returns the boolean value of the statistic.
=======
NNG_DECL uint64_t nng_stat_value(nng_stat *);

>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL bool nng_stat_bool(nng_stat *);

NNG_DECL const char *nng_stat_string(nng_stat *);

<<<<<<< HEAD
// nng_stat_desc returns a human-readable description of the statistic.
// This may be useful for display in diagnostic interfaces, etc.
=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
NNG_DECL const char *nng_stat_desc(nng_stat *);

NNG_DECL uint64_t nng_stat_timestamp(nng_stat *);

NNG_DECL int nng_device(nng_socket, nng_socket);

NNG_DECL void nng_device_aio(nng_aio *, nng_socket, nng_socket);

enum nng_errno_enum {
	NNG_EINTR        = 1,
	NNG_ENOMEM       = 2,
	NNG_EINVAL       = 3,
	NNG_EBUSY        = 4,
	NNG_ETIMEDOUT    = 5,
	NNG_ECONNREFUSED = 6,
	NNG_ECLOSED      = 7,
	NNG_EAGAIN       = 8,
	NNG_ENOTSUP      = 9,
	NNG_EADDRINUSE   = 10,
	NNG_ESTATE       = 11,
	NNG_ENOENT       = 12,
	NNG_EPROTO       = 13,
	NNG_EUNREACHABLE = 14,
	NNG_EADDRINVAL   = 15,
	NNG_EPERM        = 16,
	NNG_EMSGSIZE     = 17,
	NNG_ECONNABORTED = 18,
	NNG_ECONNRESET   = 19,
	NNG_ECANCELED    = 20,
	NNG_ENOFILES     = 21,
	NNG_ENOSPC       = 22,
	NNG_EEXIST       = 23,
	NNG_EREADONLY    = 24,
	NNG_EWRITEONLY   = 25,
	NNG_ECRYPTO      = 26,
	NNG_EPEERAUTH    = 27,
	NNG_ENOARG       = 28,
	NNG_EAMBIGUOUS   = 29,
	NNG_EBADTYPE     = 30,
	NNG_ECONNSHUT    = 31,
	NNG_EINTERNAL    = 1000,
	NNG_ESYSERR      = 0x10000000,
	NNG_ETRANERR     = 0x20000000
};

typedef struct nng_url {
	char *u_rawurl;   // never NULL
	char *u_scheme;   // never NULL
	char *u_userinfo; // will be NULL if not specified
	char *u_host;     // including colon and port
	char *u_hostname; // name only, will be "" if not specified
	char *u_port;     // port, will be "" if not specified
	char *u_path;     // path, will be "" if not specified
	char *u_query;    // without '?', will be NULL if not specified
	char *u_fragment; // without '#', will be NULL if not specified
	char *u_requri;   // includes query and fragment, "" if not specified
} nng_url;

NNG_DECL int nng_url_parse(nng_url **, const char *);

NNG_DECL void nng_url_free(nng_url *);

NNG_DECL int nng_url_clone(nng_url **, const nng_url *);

NNG_DECL const char *nng_version(void);

typedef struct nng_stream          nng_stream;
typedef struct nng_stream_dialer   nng_stream_dialer;
typedef struct nng_stream_listener nng_stream_listener;

NNG_DECL void nng_stream_free(nng_stream *);
NNG_DECL void nng_stream_close(nng_stream *);
NNG_DECL void nng_stream_send(nng_stream *, nng_aio *);
NNG_DECL void nng_stream_recv(nng_stream *, nng_aio *);
NNG_DECL int  nng_stream_get(nng_stream *, const char *, void *, size_t *);
NNG_DECL int  nng_stream_get_bool(nng_stream *, const char *, bool *);
NNG_DECL int  nng_stream_get_int(nng_stream *, const char *, int *);
NNG_DECL int  nng_stream_get_ms(nng_stream *, const char *, nng_duration *);
NNG_DECL int  nng_stream_get_size(nng_stream *, const char *, size_t *);
NNG_DECL int  nng_stream_get_uint64(nng_stream *, const char *, uint64_t *);
NNG_DECL int  nng_stream_get_string(nng_stream *, const char *, char **);
NNG_DECL int  nng_stream_get_ptr(nng_stream *, const char *, void **);
NNG_DECL int  nng_stream_get_addr(nng_stream *, const char *, nng_sockaddr *);
NNG_DECL int  nng_stream_set(nng_stream *, const char *, const void *, size_t);
NNG_DECL int  nng_stream_set_bool(nng_stream *, const char *, bool);
NNG_DECL int  nng_stream_set_int(nng_stream *, const char *, int);
NNG_DECL int  nng_stream_set_ms(nng_stream *, const char *, nng_duration);
NNG_DECL int  nng_stream_set_size(nng_stream *, const char *, size_t);
NNG_DECL int  nng_stream_set_uint64(nng_stream *, const char *, uint64_t);
NNG_DECL int  nng_stream_set_string(nng_stream *, const char *, const char *);
NNG_DECL int  nng_stream_set_ptr(nng_stream *, const char *, void *);
NNG_DECL int  nng_stream_set_addr(
     nng_stream *, const char *, const nng_sockaddr *);

NNG_DECL int nng_stream_dialer_alloc(nng_stream_dialer **, const char *);
NNG_DECL int nng_stream_dialer_alloc_url(
    nng_stream_dialer **, const nng_url *);
NNG_DECL void nng_stream_dialer_free(nng_stream_dialer *);
NNG_DECL void nng_stream_dialer_close(nng_stream_dialer *);
NNG_DECL void nng_stream_dialer_dial(nng_stream_dialer *, nng_aio *);
NNG_DECL int  nng_stream_dialer_set(
     nng_stream_dialer *, const char *, const void *, size_t);
NNG_DECL int nng_stream_dialer_get(
    nng_stream_dialer *, const char *, void *, size_t *);
NNG_DECL int nng_stream_dialer_get_bool(
    nng_stream_dialer *, const char *, bool *);
NNG_DECL int nng_stream_dialer_get_int(
    nng_stream_dialer *, const char *, int *);
NNG_DECL int nng_stream_dialer_get_ms(
    nng_stream_dialer *, const char *, nng_duration *);
NNG_DECL int nng_stream_dialer_get_size(
    nng_stream_dialer *, const char *, size_t *);
NNG_DECL int nng_stream_dialer_get_uint64(
    nng_stream_dialer *, const char *, uint64_t *);
NNG_DECL int nng_stream_dialer_get_string(
    nng_stream_dialer *, const char *, char **);
NNG_DECL int nng_stream_dialer_get_ptr(
    nng_stream_dialer *, const char *, void **);
NNG_DECL int nng_stream_dialer_get_addr(
    nng_stream_dialer *, const char *, nng_sockaddr *);
NNG_DECL int nng_stream_dialer_set_bool(
    nng_stream_dialer *, const char *, bool);
NNG_DECL int nng_stream_dialer_set_int(nng_stream_dialer *, const char *, int);
NNG_DECL int nng_stream_dialer_set_ms(
    nng_stream_dialer *, const char *, nng_duration);
NNG_DECL int nng_stream_dialer_set_size(
    nng_stream_dialer *, const char *, size_t);
NNG_DECL int nng_stream_dialer_set_uint64(
    nng_stream_dialer *, const char *, uint64_t);
NNG_DECL int nng_stream_dialer_set_string(
    nng_stream_dialer *, const char *, const char *);
NNG_DECL int nng_stream_dialer_set_ptr(
    nng_stream_dialer *, const char *, void *);
NNG_DECL int nng_stream_dialer_set_addr(
    nng_stream_dialer *, const char *, const nng_sockaddr *);

NNG_DECL int nng_stream_listener_alloc(nng_stream_listener **, const char *);
NNG_DECL int nng_stream_listener_alloc_url(
    nng_stream_listener **, const nng_url *);
NNG_DECL void nng_stream_listener_free(nng_stream_listener *);
NNG_DECL void nng_stream_listener_close(nng_stream_listener *);
NNG_DECL int  nng_stream_listener_listen(nng_stream_listener *);
NNG_DECL void nng_stream_listener_accept(nng_stream_listener *, nng_aio *);
NNG_DECL int  nng_stream_listener_set(
     nng_stream_listener *, const char *, const void *, size_t);
NNG_DECL int nng_stream_listener_get(
    nng_stream_listener *, const char *, void *, size_t *);
NNG_DECL int nng_stream_listener_get_bool(
    nng_stream_listener *, const char *, bool *);
NNG_DECL int nng_stream_listener_get_int(
    nng_stream_listener *, const char *, int *);
NNG_DECL int nng_stream_listener_get_ms(
    nng_stream_listener *, const char *, nng_duration *);
NNG_DECL int nng_stream_listener_get_size(
    nng_stream_listener *, const char *, size_t *);
NNG_DECL int nng_stream_listener_get_uint64(
    nng_stream_listener *, const char *, uint64_t *);
NNG_DECL int nng_stream_listener_get_string(
    nng_stream_listener *, const char *, char **);
NNG_DECL int nng_stream_listener_get_ptr(
    nng_stream_listener *, const char *, void **);
NNG_DECL int nng_stream_listener_get_addr(
    nng_stream_listener *, const char *, nng_sockaddr *);
NNG_DECL int nng_stream_listener_set_bool(
    nng_stream_listener *, const char *, bool);
NNG_DECL int nng_stream_listener_set_int(
    nng_stream_listener *, const char *, int);
NNG_DECL int nng_stream_listener_set_ms(
    nng_stream_listener *, const char *, nng_duration);
NNG_DECL int nng_stream_listener_set_size(
    nng_stream_listener *, const char *, size_t);
NNG_DECL int nng_stream_listener_set_uint64(
    nng_stream_listener *, const char *, uint64_t);
NNG_DECL int nng_stream_listener_set_string(
    nng_stream_listener *, const char *, const char *);
NNG_DECL int nng_stream_listener_set_ptr(
    nng_stream_listener *, const char *, void *);
NNG_DECL int nng_stream_listener_set_addr(
    nng_stream_listener *, const char *, const nng_sockaddr *);

<<<<<<< HEAD
#ifndef NNG_ELIDE_DEPRECATED
// These are legacy APIs that have been deprecated.
// Their use is strongly discouraged.

// nng_msg_getopt is defunct, and should not be used by programs. It
// always returns NNG_ENOTSUP.
NNG_DECL int nng_msg_getopt(nng_msg *, int, void *, size_t *) NNG_DEPRECATED;

// Socket options.  Use nng_socket_get and nng_socket_set instead.
NNG_DECL int nng_getopt(
    nng_socket, const char *, void *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_getopt_bool(nng_socket, const char *, bool *) NNG_DEPRECATED;
NNG_DECL int nng_getopt_int(nng_socket, const char *, int *) NNG_DEPRECATED;
NNG_DECL int nng_getopt_ms(
    nng_socket, const char *, nng_duration *) NNG_DEPRECATED;
NNG_DECL int nng_getopt_size(
    nng_socket, const char *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_getopt_uint64(
    nng_socket, const char *, uint64_t *) NNG_DEPRECATED;
NNG_DECL int nng_getopt_ptr(nng_socket, const char *, void **) NNG_DEPRECATED;
NNG_DECL int nng_getopt_string(
    nng_socket, const char *, char **) NNG_DEPRECATED;
NNG_DECL int nng_setopt(
    nng_socket, const char *, const void *, size_t) NNG_DEPRECATED;
NNG_DECL int nng_setopt_bool(nng_socket, const char *, bool) NNG_DEPRECATED;
NNG_DECL int nng_setopt_int(nng_socket, const char *, int) NNG_DEPRECATED;
NNG_DECL int nng_setopt_ms(
    nng_socket, const char *, nng_duration) NNG_DEPRECATED;
NNG_DECL int nng_setopt_size(nng_socket, const char *, size_t) NNG_DEPRECATED;
NNG_DECL int nng_setopt_uint64(
    nng_socket, const char *, uint64_t) NNG_DEPRECATED;
NNG_DECL int nng_setopt_string(
    nng_socket, const char *, const char *) NNG_DEPRECATED;
NNG_DECL int nng_setopt_ptr(nng_socket, const char *, void *) NNG_DEPRECATED;

// Context options.  Use nng_ctx_get and nng_ctx_set instead.
NNG_DECL int nng_ctx_getopt(
    nng_ctx, const char *, void *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_ctx_getopt_bool(nng_ctx, const char *, bool *) NNG_DEPRECATED;
NNG_DECL int nng_ctx_getopt_int(nng_ctx, const char *, int *) NNG_DEPRECATED;
NNG_DECL int nng_ctx_getopt_ms(
    nng_ctx, const char *, nng_duration *) NNG_DEPRECATED;
NNG_DECL int nng_ctx_getopt_size(
    nng_ctx, const char *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_ctx_setopt(
    nng_ctx, const char *, const void *, size_t) NNG_DEPRECATED;
NNG_DECL int nng_ctx_setopt_bool(nng_ctx, const char *, bool) NNG_DEPRECATED;
NNG_DECL int nng_ctx_setopt_int(nng_ctx, const char *, int) NNG_DEPRECATED;
NNG_DECL int nng_ctx_setopt_ms(
    nng_ctx, const char *, nng_duration) NNG_DEPRECATED;
NNG_DECL int nng_ctx_setopt_size(nng_ctx, const char *, size_t) NNG_DEPRECATED;

// Dialer options.  Use nng_dialer_get and nng_dialer_set instead.
NNG_DECL int nng_dialer_getopt(
    nng_dialer, const char *, void *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_dialer_getopt_bool(
    nng_dialer, const char *, bool *) NNG_DEPRECATED;
NNG_DECL int nng_dialer_getopt_int(
    nng_dialer, const char *, int *) NNG_DEPRECATED;
NNG_DECL int nng_dialer_getopt_ms(
    nng_dialer, const char *, nng_duration *) NNG_DEPRECATED;
NNG_DECL int nng_dialer_getopt_size(
    nng_dialer, const char *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_dialer_getopt_sockaddr(
    nng_dialer, const char *, nng_sockaddr *) NNG_DEPRECATED;
NNG_DECL int nng_dialer_getopt_uint64(
    nng_dialer, const char *, uint64_t *) NNG_DEPRECATED;
NNG_DECL int nng_dialer_getopt_ptr(
    nng_dialer, const char *, void **) NNG_DEPRECATED;
NNG_DECL int nng_dialer_getopt_string(
    nng_dialer, const char *, char **) NNG_DEPRECATED;
NNG_DECL int nng_dialer_setopt(
    nng_dialer, const char *, const void *, size_t) NNG_DEPRECATED;
NNG_DECL int nng_dialer_setopt_bool(
    nng_dialer, const char *, bool) NNG_DEPRECATED;
NNG_DECL int nng_dialer_setopt_int(
    nng_dialer, const char *, int) NNG_DEPRECATED;
NNG_DECL int nng_dialer_setopt_ms(
    nng_dialer, const char *, nng_duration) NNG_DEPRECATED;
NNG_DECL int nng_dialer_setopt_size(
    nng_dialer, const char *, size_t) NNG_DEPRECATED;
NNG_DECL int nng_dialer_setopt_uint64(
    nng_dialer, const char *, uint64_t) NNG_DEPRECATED;
NNG_DECL int nng_dialer_setopt_ptr(
    nng_dialer, const char *, void *) NNG_DEPRECATED;
NNG_DECL int nng_dialer_setopt_string(
    nng_dialer, const char *, const char *) NNG_DEPRECATED;

// Listener options.  Use nng_listener_get and nng_listener_set instead.
NNG_DECL int nng_listener_getopt(
    nng_listener, const char *, void *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_listener_getopt_bool(
    nng_listener, const char *, bool *) NNG_DEPRECATED;
NNG_DECL int nng_listener_getopt_int(
    nng_listener, const char *, int *) NNG_DEPRECATED;
NNG_DECL int nng_listener_getopt_ms(
    nng_listener, const char *, nng_duration *) NNG_DEPRECATED;
NNG_DECL int nng_listener_getopt_size(
    nng_listener, const char *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_listener_getopt_sockaddr(
    nng_listener, const char *, nng_sockaddr *) NNG_DEPRECATED;
NNG_DECL int nng_listener_getopt_uint64(
    nng_listener, const char *, uint64_t *) NNG_DEPRECATED;
NNG_DECL int nng_listener_getopt_ptr(
    nng_listener, const char *, void **) NNG_DEPRECATED;
NNG_DECL int nng_listener_getopt_string(
    nng_listener, const char *, char **) NNG_DEPRECATED;
NNG_DECL int nng_listener_setopt(
    nng_listener, const char *, const void *, size_t) NNG_DEPRECATED;
NNG_DECL int nng_listener_setopt_bool(
    nng_listener, const char *, bool) NNG_DEPRECATED;
NNG_DECL int nng_listener_setopt_int(
    nng_listener, const char *, int) NNG_DEPRECATED;
NNG_DECL int nng_listener_setopt_ms(
    nng_listener, const char *, nng_duration) NNG_DEPRECATED;
NNG_DECL int nng_listener_setopt_size(
    nng_listener, const char *, size_t) NNG_DEPRECATED;
NNG_DECL int nng_listener_setopt_uint64(
    nng_listener, const char *, uint64_t) NNG_DEPRECATED;
NNG_DECL int nng_listener_setopt_ptr(
    nng_listener, const char *, void *) NNG_DEPRECATED;
NNG_DECL int nng_listener_setopt_string(
    nng_listener, const char *, const char *) NNG_DEPRECATED;

// Pipe options.  Use nng_pipe_get instead.
NNG_DECL int nng_pipe_getopt(
    nng_pipe, const char *, void *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_pipe_getopt_bool(
    nng_pipe, const char *, bool *) NNG_DEPRECATED;
NNG_DECL int nng_pipe_getopt_int(nng_pipe, const char *, int *) NNG_DEPRECATED;
NNG_DECL int nng_pipe_getopt_ms(
    nng_pipe, const char *, nng_duration *) NNG_DEPRECATED;
NNG_DECL int nng_pipe_getopt_size(
    nng_pipe, const char *, size_t *) NNG_DEPRECATED;
NNG_DECL int nng_pipe_getopt_sockaddr(
    nng_pipe, const char *, nng_sockaddr *) NNG_DEPRECATED;
NNG_DECL int nng_pipe_getopt_uint64(
    nng_pipe, const char *, uint64_t *) NNG_DEPRECATED;
NNG_DECL int nng_pipe_getopt_ptr(
    nng_pipe, const char *, void **) NNG_DEPRECATED;
NNG_DECL int nng_pipe_getopt_string(
    nng_pipe, const char *, char **) NNG_DEPRECATED;

// nng_closeall closes all open sockets. Do not call this from
// a library; it will affect all sockets.
NNG_DECL void nng_closeall(void) NNG_DEPRECATED;

#endif // NNG_ELIDE_DEPRECATED

// nng_init_parameter is used by applications to change a tunable setting.
// This function must be called before any other NNG function for the setting
// to have any effect.  This function is also not thread-safe!
//
// The list of parameters supported is *not* documented, and subject to change.
//
// We try to provide sane defaults, so the use here is intended to provide
// more control for applications that cannot use compile-time configuration.
//
// Applications should not depend on this API for correct operation.
//
// This API is intentionally undocumented.
//
// Parameter settings are lost after nng_fini() is called.
typedef int   nng_init_parameter;
NNG_DECL void nng_init_set_parameter(nng_init_parameter, uint64_t);

// The following list of parameters is not part of our API stability promise.
// In particular the set of parameters that are supported, the default values,
// the range of valid values, and semantics associated therein are subject to
// change at any time.  We won't go out of our way to break these, and we will
// try to prevent changes here from breaking working applications, but this is
// on a best effort basis only.
//
// NOTE: When removing a value, please leave the enumeration in place and add
// a suffix _RETIRED ... this will preserve the binary values for binary
// compatibility.
enum {
	NNG_INIT_PARAMETER_NONE = 0, // ensure values start at 1.

	// Fix the number of threads used for tasks (callbacks),
	// Default is 2 threads per core, capped to NNG_INIT_MAX_TASK_THREADS.
	// At least 2 threads will be created in any case.
	NNG_INIT_NUM_TASK_THREADS,

	// Fix the number of threads used for expiration.  Default is one
	// thread per core, capped to NNG_INIT_MAX_EXPIRE_THREADS.  At least
	// one thread will be created.
	NNG_INIT_NUM_EXPIRE_THREADS,

	// Fix the number of poller threads (used for I/O).  Support varies
	// by platform (many platforms only support a single poller thread.)
	NNG_INIT_NUM_POLLER_THREADS,

	// Fix the number of threads used for DNS resolution.  At least one
	// will be used. Default is controlled by NNG_RESOLV_CONCURRENCY
	// compile time variable.
	NNG_INIT_NUM_RESOLVER_THREADS,

	// Limit the number of threads of created for tasks.
	// NNG will always create at least 2 of these in order to prevent
	// deadlocks. Zero means no limit.  Default is determined by
	// NNG_MAX_TASKQ_THREADS compile time variable.
	NNG_INIT_MAX_TASK_THREADS,

	// Limit the number of threads created for expiration.  Zero means no
	// limit. Default is determined by the NNG_MAX_EXPIRE_THREADS compile
	// time variable.
	NNG_INIT_MAX_EXPIRE_THREADS,

	// Limit the number of poller/IO threads created.  Zero means no limit.
	// Default is determined by NNG_MAX_POLLER_THREADS compile time
	// variable.
	NNG_INIT_MAX_POLLER_THREADS,
};

=======
>>>>>>> ce400877 (libnng 1.6.0 bundle for nanonext)
#ifdef __cplusplus
}
#endif

#endif // NNG_NNG_H
