/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:55:07 by alilin            #+#    #+#             */
/*   Updated: 2022/11/08 15:02:59 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char *ft_getopt(int ac, char **av, char **options) {
    int i = 1;
    int j;
    int k;
    (void)ac;
    (void)options;
    
    while (av[i])
    {
        if (av[i][0] != '-')
            i++;
        else
        {
            j = 1;
            
        }
    }
    return (NULL);
}
