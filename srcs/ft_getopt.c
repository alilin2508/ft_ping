/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:55:07 by alilin            #+#    #+#             */
/*   Updated: 2023/01/23 19:25:40 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char	*ft_getopt(char **av, char **options) {
	int		i;
	int		j;
	bool		flag;
	char		*option;
    
	i = 1;
	flag = false;
	option = NULL;
	while (av[i])
	{
		if (av[i][0] != '-')
			i++;
		else
		{
			j = 1;
			while(av[i][j])
			{
				for(int k = 0; k < ft_tablen(options); k++)
				{
					if (!ft_strncmp(&av[i][j], "h", 1)) // if we find the h option we quit because it will always display the helper page
					{
						if (option != NULL)
							free(option);
						option = ft_strdup("h");
						return (option);
					}
					else if (!ft_strncmp(&av[i][j], options[k], ft_strlen(options[k]))) // here we find a valid option
					{
						if (option != NULL)
							option = ft_strjoin(option, options[k]);
						else
							option = ft_strdup(options[k]);
						flag = true;
					}
				}
				if (flag == false) // we only enter this if the option is not valid and return the error
				{
					if (option != NULL)
						free(option);
					option = ft_substr(av[i], j, 1);
					return (option);
				}
				flag = false;
				j++;
			}
			i++;
		}
	}
	return (option);
}
