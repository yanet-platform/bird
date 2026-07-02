/*
 *	BIRD -- Export Protocol
 *
 *      (c) 2023 Georgy Kirichenko <g-e-o-r-g-y@yandex-team.ru>
 *
 *	Can be freely distributed and used under the terms of the GNU GPL.
 */

#ifndef _BIRD_EXPORT_H_
#define _BIRD_EXPORT_H_

#include "lib/socket.h"

/* Extended route attributes in the PROTOCOL_EXPORT namespace.
 * EA_EXPORT_IFINDEX carries the outgoing interface index (u32) of a
 * device route, whose next hop is an interface rather than a gateway. */
#define EA_EXPORT_IFINDEX	EA_CODE(PROTOCOL_EXPORT, 0)

struct export_buf {
	byte *tbuf;
	byte *tpos;
	uint64_t size;
};

struct export_config {
	struct proto_config c;
	const char *socket;
};

struct proto_export {
	struct proto p;
	struct export_config *cf;
	sock *s;
	uint32_t child_index;
	struct export_buf send_buf[2];
	uint32_t send_buf_index;
};

#endif
