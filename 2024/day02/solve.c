#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void count_safe_lines(char *input_file);
bool line_is_safe(int line[], int line_length);
bool problem_dampener(int line[], int line_length);

int main(int argc, char *argv[])
{
	printf("day02:\n");
	count_safe_lines(argv[1]);
	return 0;
}

void count_safe_lines(char *input_file)
{
	int line = 1, safe_lines = 0, dampened_lines = 0, c, i, int_line_position, int_line[100];
	char input_line[100], string_num[5];
	char *endptr;
	FILE *file_pointer;
	file_pointer = fopen(input_file, "r");

	while(fgets(input_line, 100, file_pointer))
	{
		int_line_position = 0;
		c = i = 0;

		while(input_line[i] != '\0')
		{
			if(isdigit(input_line[i]))
			{
				string_num[c] = input_line[i];
				c++;
			} else {
				string_num[c] = '\0';
				int_line[int_line_position] = (int)strtol(string_num, &endptr, 10);
				c = 0;
				int_line_position++;
			}

			i++;
		}

		if(line_is_safe(int_line, int_line_position))
		{
			safe_lines++;
		} else if(problem_dampener(int_line, int_line_position))
		{
			dampened_lines++;
		}

		line++;
	}

	(void)fclose(file_pointer);

	printf("|%-20s|%-20s|%-20s|\n", "safe lines", "dampened lines", "total safe lines");
	printf("|%-20d|%-20d|%-20d|\n\n", safe_lines, dampened_lines, safe_lines + dampened_lines);
}

bool line_is_safe(int line[], int line_length)
{
	int c, i, prev_direction, direction, differences[100];

	for(i = 0; i < (line_length - 1); i++)
	{
		differences[i] = line[i + 1] - line[i];
	}

	if(differences[0] < 0)
	{
		prev_direction = 0;
	} else if(differences[0] > 0) {
		prev_direction = 1;
	} else {
		return false;
	}

	for(c = 0; c < i; c++)
	{
		if((abs(differences[c]) < 1) || (3 < abs(differences[c])))
		{
			return false;
		}

		if(differences[c] < 0)
		{
			direction = 0;
		} else if(differences[c] > 0){
			direction = 1;
		}

		if(direction != prev_direction)
		{
			return false;
		}
	}

	return true;
}

bool problem_dampener(int line[], int line_length)
{
	int i, element_to_skip, new_line[100], new_line_length;

	for(element_to_skip = 0; element_to_skip < line_length; element_to_skip++)
	{
		new_line_length = 0;

		for(i = 0; i < line_length ; i++)
		{
			if(i != element_to_skip)
			{
				new_line[new_line_length] = line[i];
				new_line_length++;
			}
		}

		if(line_is_safe(new_line, new_line_length))
		{
			return true;
		}
	}

	return false;
}
