#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void process_input_file(char *input_file);

int main(int argc, char *argv[])
{
	process_input_file(argv[1]);
	return 0;
}

void process_input_file(char *input_file)
{
	int c, i, int_line_position, int_line[100];
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

		for(i = 0; i < int_line_position; i++)
		{
			printf("%d ", int_line[i]);
		}

		printf("\n");
	}

	(void)fclose(file_pointer);
}
