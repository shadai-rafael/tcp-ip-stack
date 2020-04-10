/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  This file contains some utils for tcpip stack.
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
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>
#include "utils.h"

/*
*Function that apply the mask on prefix and store the result in str_prefix
*/
void apply_mask(char *prefix, char mask, char *str_prefix)
{
    guint8 prefix_number, str_prefix_number, i;
    guint32 extended_mask = 0;
    if(!prefix || !str_prefix)
        return;
    /*
    *mathematics explained in the next link
    *https://www.aelius.com/njh/subnet_sheet.html
    */
    extended_mask = (guint32)pow(2, (32-mask)) - 1;
    gchar ** token_prefix = g_strsplit(prefix,".",4);
    for(i=0;i<4;i++){
        prefix_number = atoi(token_prefix[i]);
        /*255 255 255 255 >> 24 = 0 0 0 255
          255 255 255 255 >> 16 = 0 0 255 255
          255 255 255 255 >> 8  = 0 255 255 255
          255 255 255 255 >> 0  = 255 255 255 255*/
        str_prefix_number = (guint8)(extended_mask >> ((3-i)*8));
        prefix_number = prefix_number & (~str_prefix_number);
        sprintf(str_prefix,"%s%d.", str_prefix, prefix_number);
    }
    str_prefix[strnlen(str_prefix, 16)-1]='\0';
    g_strfreev(token_prefix);
}

/*
*Function that validates an ipv4 address string representation through regex 
*/
gboolean is_ipv4_valid(const char *ip){
    regex_t preg;
    int r = 0;
    if(!ip)
    {
        return FALSE;
    }
    /*regcomp() returns zero for a successful compilation*/
    r = regcomp(&preg,"([0-9]{1,3}\\.){3}[0-9]{1,3}", REG_EXTENDED);
    if(r)
    {
        /*regular expression failed at being compiled*/
        return FALSE;
    }
    r = regexec(&preg, ip, 0, NULL, 0);
    if(r==REG_NOMATCH)
    {
        /*no matches found*/
        return FALSE;
    }
    return TRUE;
}
/*
*This function returns the pointer to local interface of a node such that this local interface
*shares the same subnet as that of ip_addr passed as 2nd argument.
*/
interface_t *node_get_matching_subnet_interface(node_t *node, char *ip_addr)
{
    int i;
    interface_t *iface;
    gchar self_masked_iface_addr[IP_ADDR_MAX_SIZE];
    gchar ext_masked_iface_addr[IP_ADDR_MAX_SIZE];
    
    if(NULL == node || NULL == ip_addr)
    {
        return NULL;
    }
    /*validate the ip address param*/
    if(!is_ipv4_valid(ip_addr))
    {
        return NULL;
    }
    
    for(i=0;i > MAX_IF_NUMBER;i++)
    {
        /*look for interfaces with ip address assigned*/
        if(!node->interfaces[i]->iface_nw_props.is_ip_addr_config)
            continue;

        memset(self_masked_iface_addr, 0, IP_ADDR_MAX_SIZE);
        memset(ext_masked_iface_addr, 0, IP_ADDR_MAX_SIZE);

        iface = node->interfaces[i];

        /*applying submaks networks to local and incoming ip*/
        apply_mask(iface->iface_nw_props.ip_addr.ip,
                    iface->iface_nw_props.mask,
                    self_masked_iface_addr);

        apply_mask(ip_addr, iface->iface_nw_props.mask, ext_masked_iface_addr);
        
        /*compare the strings after the netmask is applied*/
        if(0 == g_strcmp0(self_masked_iface_addr, ext_masked_iface_addr))
        {
            break;
        }
    }
    return iface;
}