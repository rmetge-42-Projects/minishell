/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:04:50 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/14 16:05:45 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_line_centered(char *line)
{
	int	len;
	int	spaces;
	struct winsize	ws;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	len = ft_strlen(line);
	spaces = (ws.ws_col - len) / 2;
	if (spaces < 0)
		spaces = 0;
	printf("%*s\033[1;38;5;205m%s\033[0m\n", spaces, "", line);
}

void	print_header(void)
{
	char			*l[8];
	int				i;

	l[0] = "                                  "
			"                                     _    ";
	l[1] = "        ,--.   ,--.,--.        ,--"
			".       ,--.            ,--.,--.   _( )_  ";
	l[2] = "        |   `.'   |`--',--,--, `--"
			"' ,---. |  ,---.  ,---. |  ||  |  (_ o _) ";
	l[3] = "   _    |  |'.'|  |,--.|      |,--"
			".(  .-' |  .-.  || .-. :|  ||  |   (_,_)  ";
	l[4] = " _( )_  |  |   |  ||  ||  ||  ||  "
			"|.-'  `)|  | |  ||   --.|  ||  |          ";
	l[5] = "(_ o _) `--'   `--'`--'`--''--'`--"
			"'`----' `--' `--' `----'`--'`--'          ";
	l[6] = " (_,_)                            "
			"                                          ";
	l[7] = "                                  "
			"                                          ";
	i = 0;
	while (i < 8)
		print_line_centered(l[i++]);
}
