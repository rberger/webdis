/*
 * Copyright (c) 2009, 2010 Petri Lehtinen <petri@digip.org>
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef JANSSON_PRIVATE_H
#define JANSSON_PRIVATE_H

#include <stddef.h>
#include "jansson.h"
#include "hashtable.h"

#define container_of(ptr_, type_, member_)  \
    ((type_ *)((char *)ptr_ - offsetof(type_, member_)))

/* On some platforms, max() may already be defined */
#ifndef max
#define max(a, b)  ((a) > (b) ? (a) : (b))
#endif

typedef struct {
    json_t json;
    hashtable_t hashtable;
    size_t serial;
    int visited;
} json_object_t;

typedef struct {
    json_t json;
    size_t size;
    size_t entries;
    json_t **table;
    int visited;
} json_array_t;

typedef struct {
    json_t json;
    char *value;
} json_string_t;

typedef struct {
    json_t json;
    double value;
} json_real_t;

typedef struct {
    json_t json;
    json_int_t value;
} json_integer_t;

#define json_to_object(json_)  container_of(json_, json_object_t, json)
#define json_to_array(json_)   container_of(json_, json_array_t, json)
#define json_to_string(json_)  container_of(json_, json_string_t, json)
#define json_to_real(json_)   container_of(json_, json_real_t, json)
#define json_to_integer(json_) container_of(json_, json_integer_t, json)

typedef struct {
    size_t serial;
    char key[1];
} object_key_t;

const object_key_t *jsonp_object_iter_fullkey(void *iter);

void jsonp_error_init(json_error_t *error, const char *source);
void jsonp_error_set(json_error_t *error, int line, int column,
                     const char *msg, ...);

#endif
