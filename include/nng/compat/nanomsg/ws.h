//
// Copyright 2018 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef NNG_COMPAT_WS_H
#define NNG_COMPAT_WS_H

#ifdef __cplusplus
extern "C" {
#endif

#define NN_WS (-4)

#define NN_WS_MSG_TYPE 1

#define NN_WS_MSG_TYPE_TEXT 0x1
#define NN_WS_MSG_TYPE_BINARY 0x2

#ifdef __cplusplus
}
#endif

#endif // NNG_COMPAT_WS_H
