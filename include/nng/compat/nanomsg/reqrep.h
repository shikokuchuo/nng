//
// Copyright 2018 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef NNG_COMPAT_REQREP_H
#define NNG_COMPAT_REQREP_H

#ifdef __cplusplus
extern "C" {
#endif

#define NN_PROTO_REQREP 3
#define NN_REQ (NN_PROTO_REQREP * 16 + 0)
#define NN_REP (NN_PROTO_REQREP * 16 + 1)

#define NN_REQ_RESEND_IVL (NN_REQ * 16 + 1)

#ifdef __cplusplus
}
#endif

#endif // NNG_COMPAT_REQREP_H
