/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2022/11/08 14:41:36 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int main(int ac, char  **av)
{
    if (ac < 2) {
        fprintf(stderr, "ping: usage error: Destination address required\n");
        exit(EXIT_FAILURE);
    }
    char *options[] = {
        "help",
        "h",
        "v",
        NULL
    };
    ft_getopt(ac, av, options);
    (void)av;
    return (0);
}