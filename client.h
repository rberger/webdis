#ifndef CLIENT_H
#define CLIENT_H

#include "http.h"

struct server;

struct http_client {

	/* socket and server reference */
	int fd;
	in_addr_t addr;
	struct event ev;
	struct server *s;
	int executing;

	/* http parser */
	http_parser_settings settings;
	http_parser parser;

	/* decoded http */
	enum http_method verb;
	str_t path;
	str_t body;

	/* input headers from client */
	struct {
		str_t connection;
		str_t if_none_match;
		str_t authorization;
	} input_headers;

	/* response headers */
	struct input_headers {
		str_t content_type;
		str_t etag;
	} output_headers;

	/* query string */
	str_t qs_type;
	str_t qs_jsonp;

	/* pub/sub */
	struct subscription *sub;

	/* private, used in HTTP parser */
	str_t last_header_name;
};


struct http_client *
http_client_new(int fd, struct server *s);

void
http_client_serve(struct http_client *c);

void
http_client_free(struct http_client *c);

void
http_client_reset(struct http_client *c);

int
http_on_path(http_parser*, const char *at, size_t length);

int
http_on_path(http_parser*, const char *at, size_t length);

int
http_on_body(http_parser*, const char *at, size_t length);

int
http_on_header_name(http_parser*, const char *at, size_t length);

int
http_on_header_value(http_parser*, const char *at, size_t length);

int
http_on_complete(http_parser*);

int
http_on_query_string(http_parser*, const char *at, size_t length);

void
http_send_reply(struct http_client *c, short code, const char *msg,
		const char *body, size_t body_len);

int
http_client_keep_alive(struct http_client *c);

#endif