#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int count_safe_lines(char *input_file);
bool line_is_safe(int (*line)[], int line_length);
bool problem_dampener(int (*line)[], int line_length);

int main(int argc, char *argv[])
{
	printf("safe_lines: %d\n", count_safe_lines(argv[1]));
	return 0;
}

int count_safe_lines(char *input_file)
{
	int line = 1, safe_lines = 0, c, i, int_line_position, int_line[100];
	char input_line[100], string_num[5];
	char *endptr;
	FILE *file_pointer;
	file_pointer = fopen(input_file, "r");

	while(fgets(input_line, 100, file_pointer))
	{
		//printf("%s", input_line);
		
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

		printf("line: %d\n", line);
		if(line_is_safe(&int_line, int_line_position))
		{
			safe_lines++;
			printf("line %5d safe\n", line);
			printf("total safe lines: %d\n\n", safe_lines);
		} else if(problem_dampener(&int_line, int_line_position))
		{
			safe_lines++;
			printf("line %5d dampened\n", line);
			printf("total safe line: %d\n\n", safe_lines);
		} else {
			printf("line %5d unsafe\n\n", line);
		}
		line++;
	}

	(void)fclose(file_pointer);

	return safe_lines;
}

bool line_is_safe(int (*line)[], int line_length)
{
	int c, i, prev_direction, direction, diff, differences[100];
	bool one_direction = true, close_diffs = true, no_0_diff = true;

	for(i = 0; i < line_length; i++)
	{
		printf("\t%d", (*line)[i]);
	}

	for(i = 0; i < (line_length - 1); i++)
	{
		differences[i] = (*line)[i + 1] - (*line)[i];
	}

	printf("\n");
	
	for(c = 0; c < i; c++)
	{
		printf("\t%5d", differences[c]);
	}

	printf("\n");

	if(differences[0] < 0)
	{
		printf("\tdir: decr\n");
		prev_direction = 0;
	} else if(differences[0] > 0) {
		printf("\tdir: incr\n");
		prev_direction = 1;
	} else {
		printf("\tdir: none\n");
		return false;
	}

	for(c = 0; c < i; c++)
	{
		if((abs(differences[c]) < 1) || (3 < abs(differences[c])))
		{
			printf("\tclose_diffs\n");
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
			printf("\tone_direction\n");
			return false;
		}
	}

	return true;
}

bool problem_dampener(int (*line)[], int line_length)
{
	int i, element_to_skip, new_line[100], new_line_length;

	for(element_to_skip = 0; element_to_skip < line_length; element_to_skip++)
	{
		new_line_length = 0;

		for(i = 0; i < line_length ; i++)
		{
			if(i != element_to_skip)
			{
				new_line[new_line_length] = (*line)[i];
				printf("%d ", new_line[new_line_length]);
				new_line_length++;
			}
		}
		printf("\n");

		if(line_is_safe(&new_line, new_line_length))
		{
			return true;
		}
	}

	return false;
}
