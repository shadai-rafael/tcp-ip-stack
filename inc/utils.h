#ifndef __UTILS__
#define __UTILS__
#include "graph.h"

void apply_mask(char *, char, char *);
gboolean is_ipv4_valid(const char *ip);
interface_t *node_get_matching_subnet_interface(node_t *, char *);
void dump_nw_graph(graph_t *graph);

#endif