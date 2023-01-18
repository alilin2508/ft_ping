/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handleopt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:52:12 by alilin            #+#    #+#             */
/*   Updated: 2023/01/18 20:35:26 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void print_option_error(char *error) {
    fprintf(stderr, "ping: invalid option -- '%s'\n", error);
}

void print_usage(void) {
    printf("\nUsage\n");
    printf("  ping [options] <destination>\n");
    printf("\nOptions:\n");
    printf("  %-19s%s\n", "<destination>", "dns name or ip address");
    printf("  %-19s%s\n", "-h", "print help and exit");
    printf("  %-19s%s\n", "-v", "verbose output");
}

void init_opt(t_options *options) {
    options->h = false;
    options->v = false;
    options->error = false;
}

void ft_handleopt(t_options *options, char *option) {
    init_opt(options);
    
    if (option != NULL)
    {
        for (size_t i = 0; i < ft_strlen(option); i++)
        {
            switch (option[i]) // init the options that we found earlier
            {
                case 'h':
                    options->h = true;
                    break;
                case 'v':
                    options->v = true;
                    break;
                default:
                    options->error = true;
                    break;
            }
        }
    }
    if (options->h == true)
    {
        print_usage();
        free(option);
        exit(EXIT_FAILURE);
    }
    else if (options->error == true)
    {
        print_option_error(option);
        print_usage();
        free(option);
        exit(EXIT_FAILURE);
    }
    return;
}