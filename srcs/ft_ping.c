/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2022/11/22 15:17:03 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int main(int ac, char  **av)
{
    char **options;
    char *option;
    if (ac < 2) {
        fprintf(stderr, "ping: usage error: Destination address required\n");
        exit(EXIT_FAILURE);
    }
    options = ft_setopt(2, "h", "v", "a");
    option = ft_getopt(av, options);
    printf("%s\n", option);
    free(options);
    return (0);
}