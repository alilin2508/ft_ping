/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:10:52 by alilin            #+#    #+#             */
/*   Updated: 2022/11/08 14:43:43 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_setopt(int nboptions, ...)
{
    int i;
    va_list opt;
    
    char **options;
    if (!(options = (char **)malloc(sizeof(char *) * (nboptions + 1))))
        exit(EXIT_FAILURE);
    va_start(opt, nboptions);
    for(i = 0; i < nboptions; i++)
    {
        options[i] = ft_strdup(va_arg(opt, char *));
    }
    options[i] = NULL;
    va_end(opt);
    return(options);
}