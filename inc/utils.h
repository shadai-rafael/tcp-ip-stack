/*
 * =====================================================================================
 *
 *       Filename:  utils.h
 *
 *    Description:  This file contains some utils for tcpip stack definitions.
 *
 *        Version:  1.0
 *        Created:  February 2020
 *       Revision:  0.0
 *       Compiler:  gcc
 *
 *         Author:  Shadai Lopez Garcia, shadai.lopez.garcia@gmail.com
 * 
 * =====================================================================================
 */
#ifndef __UTILS__
#define __UTILS__
#include "graph.h"
/*
*Function that apply the mask on prefix and store the result in str_prefix
*/
void apply_mask(char *, char, char *);

/*
*Function that validates an ipv4 address string representation through regex 
*/
gboolean is_ipv4_valid(const char *ip);

/*
*This function returns the pointer to local interface of a node such that this local interface
*shares the same subnet as that of ip_addr passed as 2nd argument.
*/
interface_t *node_get_matching_subnet_interface(node_t *, char *);

void dump_nw_graph(graph_t *graph);

#endif