#ifndef ACL_H
#define ACL_H

#include <netinet/in.h>

struct evhttp_request;
struct cmd;
struct conf;

struct acl_commands {
	unsigned int count;
	char **commands;
};

struct acl {

	/* CIDR subnet + mask */
	struct {
		int enabled;
		in_addr_t subnet;
		in_addr_t mask;
	} cidr;

	char *http_basic_auth;

	/* commands that have been enabled or disabled */
	struct acl_commands enabled;
	struct acl_commands disabled;

	struct acl *next;
};

int
acl_match_client(struct acl *a, struct evhttp_request *rq, in_addr_t *ip);

int
acl_allow_command(struct cmd *cmd, struct conf *cfg, struct evhttp_request *rq);

#endif
