/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:55:07 by alilin            #+#    #+#             */
/*   Updated: 2022/11/07 17:04:31 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char *ft_getopt(int ac, char **av, char **options) {
    (void)ac;
    (void)av;
    for(int j = 0; options[j]; j++) {
        printf("%s\n", options[j]);
    }
    return (NULL);
}
