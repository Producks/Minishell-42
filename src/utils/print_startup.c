/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_startup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:46:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/14 17:09:46 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	fetch_mac(void)
{
	printf ("\n"
		GRN"                 ,xNMM.\n"
		"             .OMMMMo\n"
		"             lMM\n"
		"     .;loddo:.  .olloddol;.\n"
		"   cKMMMMMMMMMMNWMMMMMMMMMM0:\n"
		YEL" .KMMMMMMMMMMMMMMMMMMMMMMMWd.\n"
		" XMMMMMMMMMMMMMMMMMMMMMMMX.\n"
		RED";MMMMMMMMMMMMMMMMMMMMMMMM:\n"
		":MMMMMMMMMMMMMMMMMMMMMMMM:\n"
		".MMMMMMMMMMMMMMMMMMMMMMMMX.\n"
		" kMMMMMMMMMMMMMMMMMMMMMMMMWd.\n"
		PNK" 'XMMMMMMMMMMMMMMMMMMMMMMMMMMk\n"
		"  'XMMMMMMMMMMMMMMMMMMMMMMMMK.\n"
		BLU"    kMMMMMMMMMMMMMMMMMMMMMMd\n"
		"     ;KMMMMMMMWXXWMMMMMMMk.\n"
		"       \"cooc*\"    \"*cooc\"\n"
		RESET);
}

static void	fetch_linux(void)
{
	printf (
		GRN" ..............\n"
		"             ..,;:ccc,.\n"
		"           ......''';lxO.\n"
		" .....''''..........,:ld;\n"
		"            .';;;:::;,,.x,\n"
		GRN"       ..'''."DORNG"            0Xxoc:,.  ...\n"
		GRN"   ...."DORNG"                ,ONkc;,;cokOdc',.\n"
		GRN"  ."DORNG"                   OMo           ':dd$o.\n"
		DORNG"                     dMc               :OO;\n"
		"                     0M.                 .:o.\n"
		PNK"                     ;Wd\n"
		"                      ;XO,\n"
		"                        ,d0Odlc;,..\n"
		"                            ..',;:cdOOd::,.\n"
		BBLU"                                     .:d;.':;.\n"
		"                                          ;l   ..\n"
		"                                           .o\n"
		"                                             c\n"
		"                                             .'\n"
		"                                              .\n"RESET);
}

void	print_startup(void)
{
	char	*user;

	user = getenv("USER");
	if (OS == 0)
		fetch_mac();
	else if (OS == 1)
		fetch_linux();
	printf("Welcome %s to Minishell\n", user);
}
