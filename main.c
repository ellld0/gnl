/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:00 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/13 02:10:35 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	next_read_error;

size_t	mock_read(int fd, void *buf, size_t count)
{
	static int	malloc_attempt;
	int			force_failure_attempt;
	size_t		return_value;

	if (next_read_error)
	{
		write (1, "tentativa falha", 15);
		return (-1);
	}
	#undef read
	extern ssize_t read(int fd, void *buf, size_t count);
	return_value = read(fd, buf, count);
	#define read(fd, buffer, bytes) mock_read(fd, buffer, bytes);
	return (return_value);
}

void	*mock_malloc(size_t size)
{
	static int	malloc_attempt;
	int			force_failure_attempt;
	void		*return_ptr;

	malloc_attempt++;
	force_failure_attempt = 4;
	if (malloc_attempt == force_failure_attempt)
	{
		write (1, "tentativa falha", 15);
		return (NULL);
	}
	#undef malloc
	extern void *malloc(size_t);
	return_ptr = malloc(size);
	#define malloc(size) mock_malloc(size);
	return (return_ptr);
}

void	print_for_me(char *string)
{
	if (!(string))
	{
		printf("NULL!\n");
		return ;
	}
	printf("%s", string);
	fflush(stdout);
}

void	our_gnl_tester(int test_nb, int fd, char *expected_result)
{
	char	*result;
	int		string_cmp_result;

	printf("\n\nTest number: %d\n", test_nb);
	result = get_next_line(fd);
	if (result)
		printf("Output: %s", result);
	else
		printf("Output: %s\n", result);
	fflush(stdout);
	if (result && expected_result)
	{
		string_cmp_result = strcmp(result, expected_result);
		if (string_cmp_result)
			printf("Tivemos diferença do esperado para o que obtivemos.\n" \
				"O que obtivemos: %s\nO esperado: %s", result, expected_result);
		else
			printf("\033[32mOK!!!\033[0m");
	}
	else
		if (!(result) && !(expected_result))
			printf("\033[32mOK!!!\033[0m Ambos resultados foram nulos");
		else
		{
			if (!(result))
				printf("KO. Nosso resultado foi nulo, mas o esperado era: %s", expected_result);
			if (!(expected_result))
				printf("KO. Nosso resultado foi '%s', mas o esperado era nulo.", result);
		}
	free(result);
}

int	main(void)
{
	int		fd_0;
	int		fd_1;
	int		fd_2;
	int		fd_3;
	int		execution_counter;
	char	*result_string;

	printf("\n\n--- Iniciando ---\n\n");
	if (0)
	{
		fd_1 = open("text_files/multiple_nl.txt", O_RDONLY);
		if (!(fd_1))
		{
			printf("Não foi possível abrir o arquivo. Vamos encerrar o programa");
			return (0);
		}
		while (1)
		{
			result_string = get_next_line(fd_1);
			if (!(result_string))
			{
				printf("< Teste 1: Chegamos ao fim do arquivo ou tivemos um erro. >");
				return (0);
			}
			print_for_me(result_string);
			free(result_string);
		}
	}
	if (0)
	{
		fd_1 = open("text_files/poesia.txt", O_RDONLY);
		if (!(fd_1))
		{
			printf("Não foi possível abrir o arquivo. Vamos encerrar o programa");
			return (0);
		}
		int	control = 0;
		while (1)
		{
			result_string = get_next_line(fd_1);
			if (!(control))
				close(fd_1);
			control++;
			if (control == 2)
				fd_1 = open("text_files/poesia.txt", O_RDONLY);
			if (!(result_string) && control >= 4)
			{
				printf("< Teste 1: Chegamos ao fim do arquivo ou tivemos um erro. >");
				fflush(stdout);
				return (0);
			}
			print_for_me(result_string);
			free(result_string);
		}
	}
	if (0)
	{
		int	curr_fd;
		fd_1 = open("text_files/read_error.txt", O_RDONLY);
		fd_2 = open("text_files/lines_around_10.txt", O_RDONLY);
		execution_counter = 1;
		while (execution_counter <= 14)
		{
			if ((execution_counter == 1) || (execution_counter == 3) || \
				(execution_counter == 5) || (execution_counter == 7) || \
				(execution_counter == 9) || (execution_counter == 10) || \
				(execution_counter == 13) || (execution_counter == 14))
				curr_fd = fd_1;
			else
				curr_fd = fd_2;
			if (execution_counter == 7)
			{
				fd_1 = open("text_files/read_error.txt", O_RDONLY);
				curr_fd = fd_1;
			}
			result_string = get_next_line(curr_fd);
			if (execution_counter == 5)
			{
				printf("\n\nResult string deveria ser: NULL\n" \
					"Ela é:                     %s\n\n", result_string);
			}
			if (!(result_string) && (execution_counter == 4))
			{
				if (BUFFER_SIZE > 100)
				{
					do
					{
						result_string = get_next_line(fd_1);
						free(result_string);
					} while (result_string != NULL);
				}
				close(fd_1);
			}
			if (!(result_string))
			{
				printf("< Teste 1: Chegamos ao fim do arquivo ou tivemos um erro. >");
				fflush(stdout);
				return (0);
			}
			print_for_me(result_string);
			free(result_string);
			execution_counter++;
		}
	}
	if (0)
	{
		fd_0 = open("text_files/41_with_nl", O_RDONLY);
		fd_1 = open("text_files/42_with_nl", O_RDONLY);
		fd_2 = open("text_files/43_with_nl", O_RDONLY);
		fd_3 = open("text_files/nl", O_RDONLY);

		/* 1 */ our_gnl_tester(1, 1000, NULL);
		/* 2 */ our_gnl_tester(2, fd_0, "0123456789012345678901234567890123456789\n");

		/* 3 */ our_gnl_tester(3, 1001, NULL);
		/* 4 */ our_gnl_tester(4, fd_1, "01234567890123456789012345678901234567890\n");

		/* 5 */ our_gnl_tester(5, 1002, NULL);
		/* 6 */ our_gnl_tester(6, fd_2, "012345678901234567890123456789012345678901\n");

		/* 7 */ our_gnl_tester(7, 1003, NULL);
		/* 8 */ our_gnl_tester(8, fd_0, "0");

		/* 9 */ our_gnl_tester(9, 1004, NULL);
		/* 10 */ our_gnl_tester(10, fd_1, "1");

		/* 11 */ our_gnl_tester(11, 1005, NULL);
		/* 12 */ our_gnl_tester(12, fd_2, "2");

		/* 13 */ our_gnl_tester(13, fd_0, NULL);
		/* 14 */ our_gnl_tester(14, fd_1, NULL);
		/* 15 */ our_gnl_tester(15, fd_2, NULL);

		/* 16 */ our_gnl_tester(16, 1006, NULL);
		/* 17 */ our_gnl_tester(17, fd_3, "\n");
		/* 18 */ our_gnl_tester(18, 1007, NULL);
		/* 19 */ our_gnl_tester(19, fd_3, NULL);
	}
	if (1)
	{
		fd_0 = open("text_files/read_error.txt", O_RDONLY);
		/* 1 */ our_gnl_tester(1, fd_0, "aaaaaaaaaa\n");
		/* 2 */ our_gnl_tester(2, fd_0, "bbbbbbbbbb\n");
		// set the next read call to return -1
		next_read_error = 1;
		if (BUFFER_SIZE > 100) {
			char *temp;
			do {
				temp = get_next_line(fd_0);
				free(temp);
			} while (temp != NULL);
		}
		/* 3 */ our_gnl_tester(3, fd_0, NULL);
		next_read_error = 0;
		close(fd_0);
		 fd_0 = open("text_files/read_error.txt", O_RDONLY);
		 /* 4 */ our_gnl_tester(4, fd_0, "aaaaaaaaaa\n");
		/* 5 */ our_gnl_tester(5, fd_0, "bbbbbbbbbb\n");
		/* 6 */ our_gnl_tester(6, fd_0, "cccccccccc\n");
		/* 7 */ our_gnl_tester(7, fd_0, "dddddddddd\n");
		/* 8 */ our_gnl_tester(8, fd_0, NULL);
	}
	printf("\n\n--- Encerrando ---\n\n");
	return (0);
}
