/*
 * =====================================================================================
 *
 *       Filename:  net.h
 *
 *    Description:  This file contains the network definitions.
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
#ifndef __NET__
#define __NET__
#include <glib.h>


#define MAC_MAX_SIZE 48
#define IP_ADDR_MAX_SIZE 16

//forward declaration
typedef struct graph graph_t;
typedef struct interface interface_t;
typedef struct node node_t;


typedef struct mac_add {
    unsigned char mac[MAC_MAX_SIZE];    /*mac address buffer*/
} mac_add_t;


typedef struct ip_add {
    unsigned char ip[IP_ADDR_MAX_SIZE];    /*ip address buffer*/
} ip_add_t;

typedef struct node_nw_prop {
    guint16 flags;                   /*node nw flag*/
    gboolean is_lb_ip_addr_config;   /*loopback ip address flag*/ 
    ip_add_t lb_ip_addr;             /*loopback ip address of the node*/
} node_nw_prop_t;

typedef struct intf_nw_props {

    /*L2 properties*/
    mac_add_t mac_addr;             /*mac address*/ 

    /*L3 properties*/
    gboolean is_ip_addr_config;    /*ip address flag*/ 
    ip_add_t ip_addr;              /*ip address*/
    char mask;                     /*ip mask*/
} intf_nw_props_t;

static inline void init_intf_nw_props(intf_nw_props_t *nw_prop){
    memset(nw_prop->mac_addr.mac,0,MAC_MAX_SIZE);
    nw_prop->is_ip_addr_config = FALSE;
    memset(nw_prop->ip_addr.ip,0,IP_ADDR_MAX_SIZE);
    nw_prop->mask = 0;
}
/*************************** PROTOTYPE FUNC************************************/
gboolean node_set_looback_address(node_t *node, gchar * ip_addr );
gboolean node_set_intf_ip_address(node_t *node, gchar * local_if, gchar *ip_addr, char mask);
gboolean node_unset_intf_ip_address(node_t *node, gchar * local_if);
#endif