/*
 * =====================================================================================
 *
 *       Filename:  net.c
 *
 *    Description:  This file contains the network logic implementation.
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

#include "net.h"
#include "graph.h"
/*
*Function that sets the loopback address
*/
gboolean node_set_looback_address(node_t *node, gchar *ip_address ){

    if(!ip_address){
        return FALSE;
    }
    
    node->node_nw_props.is_lb_ip_addr_config = TRUE;
    strncpy(node->node_nw_props.lb_ip_addr.ip, ip_address, IP_ADDR_MAX_SIZE);

    return node->node_nw_props.is_lb_ip_addr_config;
}
/*
*Function that set the ip values to the first network interface available
*/
gboolean node_set_intf_ip_address(node_t *node, gchar * local_if, gchar *ip_address, char mask){
    int i = 0;
    interface_t *iface;
    if(!local_if || !ip_address){
        return FALSE;
    }
    while (FALSE != node->interfaces[i]->iface_nw_props.is_ip_addr_config && i < MAX_IF_NUMBER) 
    {
        i++;
    }
    if(i == MAX_IF_NUMBER){
        return FALSE;
    }
    node->interfaces[i] = (interface_t *) g_malloc (sizeof(interface_t));
    iface = node->interfaces[i];
    strncpy(iface->name,local_if,MAX_IF_NAME);
    strncpy(iface->iface_nw_props.ip_addr.ip, ip_address, IP_ADDR_MAX_SIZE);
    iface->iface_nw_props.mask = mask;
    iface->iface_nw_props.is_ip_addr_config = TRUE;
    return FALSE;
}

/*
*Function that cleans the interface idicated by local_if
*/
gboolean node_unset_intf_ip_address(node_t *node, gchar * local_if){
    int i = 0;
    interface_t *iface;
    if(!local_if){
        return FALSE;
    }
    while (0 == g_strcmp0(node->interfaces[i]->name, local_if)) 
    {
        i++;
    }
    if(i == MAX_IF_NUMBER){
        return FALSE;
    }
    g_free(node->interfaces[i]);
    return  TRUE;
}