/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:49:21 by rhasan            #+#    #+#             */
/*   Updated: 2025/03/06 00:24:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
#include <fcntl.h>
#include <unistd.h>

 
int	main(void) {
    // Open or create a file named "output.txt"
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return (1); // Return an error code if file could not be opened
    }

    // Use ft_putchar_fd to write the character 'A' to the file
    ft_putchar_fd('A', fd);

    // Close the file descriptor
    if (close(fd) < 0) {
        perror("close");
        return (1); // Return an error code if file could not be closed
    }

    return (0); // Return success
}*/
