/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2022/11/24 16:07:20 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int main(int ac, char  **av) {
    if (ac < 2) {
        fprintf(stderr, "ping: usage error: Destination address required\n");
        exit(EXIT_FAILURE);
    }
    t_options   opt;
    char        *option;
    char        *options[] = {
        "h",
        "v",
        NULL
    };
    option = ft_getopt(av, options);
    ft_handleopt(&opt, option);
    free(option);
    return (0);
}