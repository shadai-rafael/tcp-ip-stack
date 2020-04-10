/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:  This file contains the graph implementation.
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
#include <stdio.h>
#include "graph.h"
/*********************STATIC PROTOTYPE FUNC************************************/
static unsigned int get_free_interface(node_t * node);

static void fillup_the_interface(interface_t * interface, gchar * name,
        node_t *node);
/***************************FUNCTIONS*****************************************/

graph_t * create_new_graph(gchar * topology)
{
  graph_t *graph = (graph_t *) g_new0(graph_t, 1);
  strncpy(graph->topology, topology, MAX_TP_NAME);
  graph->topology[MAX_TP_NAME-1] = '\0';
  return graph;
}

node_t * create_new_graph_node(graph_t *graph, gchar * name)
{
  int i = 0;
  node_t *node = (node_t *)g_new0(node_t, 1);
  strncpy(node->name, name, MAX_NODE_NAME);
  node->name[MAX_NODE_NAME -1] = '\0';
  for(;i<MAX_IF_NUMBER;i++){
    node->interfaces[i]=NULL;
  }

  graph->node_list = g_list_append (graph->node_list,(gpointer)node);
  return node;
}

static unsigned int get_available_interface(node_t * node){
  unsigned int i = 0;
  while (node->interfaces[i] != NULL) {
    i++;
  }
  return i;
}

static void fillup_the_interface( interface_t * interface, gchar * name,
            node_t *node)
{
  interface = (interface_t *)g_new0(interface_t, 1);
  strncpy(interface->name, name, MAX_IF_NAME);
  interface->name[MAX_IF_NAME - 1] = '\0';
  interface->node = node;
  interface->link = (link_t *)g_new0(link_t, 1);
}

gboolean create_link_between_nodes(node_t * from_node, node_t * to_node,
          gchar * from_if_name, gchar * to_if_name, unsigned int cost)
{
  unsigned int from_index = 0;
  unsigned int to_index = 0;
  if(from_node == NULL || to_node ==NULL)
    return FALSE;
  from_index = get_available_interface(from_node);
  if(from_index == MAX_IF_NUMBER){
    printf("%s does not have interfaces available \n", from_node->name);
    return FALSE;
  }

  from_node->interfaces[from_index]->link->if_self = from_node->interfaces[from_index];
  from_node->interfaces[from_index]->link->cost = cost;

  to_index = get_available_interface(to_node);
  if(to_index == MAX_IF_NUMBER){
    printf("%s does not have interfaces available \n", to_node->name);
    return FALSE;
  }

  to_node->interfaces[to_index]->link->if_self = to_node->interfaces[to_index];
  to_node->interfaces[to_index]->link->cost = cost;

  from_node->interfaces[from_index]->link->if_conn = to_node->interfaces[to_index];
  to_node->interfaces[to_index]->link->if_conn = from_node->interfaces[from_index];
  return TRUE;
}
