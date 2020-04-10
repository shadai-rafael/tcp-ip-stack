/*
 * =====================================================================================
 *
 *       Filename:  graph.h
 *
 *    Description:  This file contains the graph definitions.
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
#ifndef __GRAPH__
#define __GRAPH__
#include "net.h"
#include <glib.h>

#define MAX_IF_NAME 32
#define MAX_IF_NUMBER 16
#define MAX_NODE_NAME 32
#define MAX_TP_NAME 32

//Forward declaration
typedef struct node node_t;
typedef struct link link_t;


/*GET macros*/
#define IFACE_MAC(iface) ((iface)->iface_nw_props.mac_addr.mac)
#define IFACE_IP(iface) ((iface)->iface_nw_props.ip_addr.ip)

typedef struct interface{
    gchar name[MAX_IF_NAME];           /*name of the interface*/
    node_t *node;                      /*node that belongs the interface*/
    link_t *link;                      /*link, representation of the connection between interfaces */
    intf_nw_props_t iface_nw_props;    /*interface properties*/
}interface_t;

typedef struct node{
  gchar name[MAX_NODE_NAME];                 /*node name*/
  interface_t *interfaces[MAX_IF_NUMBER];    /*buffer of node interfaces*/
  node_nw_prop_t node_nw_props;              /*node network properties*/
  GList *node_list;                          /*list of nodes connected to this node*/
}node_t;

typedef struct link{
  interface_t *if_self;    /*pointer to the node's interface*/
  interface_t *if_conn;    /*pointer to the interface of the node connected with*/
  unsigned int cost;       /*cost of the link*/
}link_t;

typedef struct graph{
  gchar topology[MAX_TP_NAME];    /*name of the topology*/
  GList *node_list;               /*list of nodes*/
}graph_t;

/*create a new graph*/
graph_t * create_new_graph(gchar * topology);

/*create a new node*/
node_t * create_new_graph_node(graph_t *graph, gchar * name);

/*create a link between nodes*/
gboolean create_link_between_nodes(node_t * from_node, node_t * to_node,
        gchar * from_if_name, gchar * to_if_name, unsigned int cost);
#endif
