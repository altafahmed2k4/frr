/*
 * PIM for IPv6 FRR
 * Copyright (C) 2022  Vmware, Inc.
 *		       Mobashshera Rasool <mrasool@vmware.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; see the file COPYING; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <zebra.h>

#include "lib/json.h"
#include "command.h"
#include "if.h"
#include "prefix.h"
#include "zclient.h"
#include "plist.h"
#include "hash.h"
#include "nexthop.h"
#include "vrf.h"
#include "ferr.h"

#include "pimd.h"
#include "pim6_cmd.h"
#include "pim_vty.h"
#include "lib/northbound_cli.h"
#include "pim_errors.h"
#include "pim_nb.h"
#include "pim_cmd_common.h"

#ifndef VTYSH_EXTRACT_PL
#include "pimd/pim6_cmd_clippy.c"
#endif

DEFPY (ipv6_pim_joinprune_time,
       ipv6_pim_joinprune_time_cmd,
       "ipv6 pim join-prune-interval (1-65535)$jpi",
       IPV6_STR
       PIM_STR
       "Join Prune Send Interval\n"
       "Seconds\n")
{
	return pim_process_join_prune_cmd(vty, jpi_str);
}

DEFPY (no_ipv6_pim_joinprune_time,
       no_ipv6_pim_joinprune_time_cmd,
       "no ipv6 pim join-prune-interval [(1-65535)]",
       NO_STR
       IPV6_STR
       PIM_STR
       "Join Prune Send Interval\n"
       IGNORED_IN_NO_STR)
{
	return pim_process_no_join_prune_cmd(vty);
}

DEFPY (ipv6_pim_spt_switchover_infinity,
       ipv6_pim_spt_switchover_infinity_cmd,
       "ipv6 pim spt-switchover infinity-and-beyond",
       IPV6_STR
       PIM_STR
       "SPT-Switchover\n"
       "Never switch to SPT Tree\n")
{
	return pim_process_spt_switchover_infinity_cmd(vty);
}

DEFPY (ipv6_pim_spt_switchover_infinity_plist,
       ipv6_pim_spt_switchover_infinity_plist_cmd,
       "ipv6 pim spt-switchover infinity-and-beyond prefix-list WORD$plist",
       IPV6_STR
       PIM_STR
       "SPT-Switchover\n"
       "Never switch to SPT Tree\n"
       "Prefix-List to control which groups to switch\n"
       "Prefix-List name\n")
{
	return pim_process_spt_switchover_prefixlist_cmd(vty, plist);
}

DEFPY (no_ipv6_pim_spt_switchover_infinity,
       no_ipv6_pim_spt_switchover_infinity_cmd,
       "no ipv6 pim spt-switchover infinity-and-beyond",
       NO_STR
       IPV6_STR
       PIM_STR
       "SPT_Switchover\n"
       "Never switch to SPT Tree\n")
{
	return pim_process_no_spt_switchover_cmd(vty);
}

DEFPY (no_ipv6_pim_spt_switchover_infinity_plist,
       no_ipv6_pim_spt_switchover_infinity_plist_cmd,
       "no ipv6 pim spt-switchover infinity-and-beyond prefix-list WORD",
       NO_STR
       IPV6_STR
       PIM_STR
       "SPT_Switchover\n"
       "Never switch to SPT Tree\n"
       "Prefix-List to control which groups to switch\n"
       "Prefix-List name\n")
{
	return pim_process_no_spt_switchover_cmd(vty);
}

void pim_cmd_init(void)
{
	if_cmd_init(pim_interface_config_write);

	install_element(CONFIG_NODE, &ipv6_pim_joinprune_time_cmd);
	install_element(CONFIG_NODE, &no_ipv6_pim_joinprune_time_cmd);
	install_element(CONFIG_NODE, &ipv6_pim_spt_switchover_infinity_cmd);
	install_element(CONFIG_NODE, &ipv6_pim_spt_switchover_infinity_plist_cmd);
	install_element(CONFIG_NODE, &no_ipv6_pim_spt_switchover_infinity_cmd);
	install_element(CONFIG_NODE, &no_ipv6_pim_spt_switchover_infinity_plist_cmd);
}
