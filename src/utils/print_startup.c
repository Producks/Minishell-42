/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_startup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:46:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/05 22:48:53 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../input/input.h"

static void	fetch(void)
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

void	print_startup(void)
{
	char	*user;

	user = getenv("USER");
	fetch();
	printf("Welcome %s to Minishell!\n", user);
}
