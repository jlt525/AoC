#include <stdio.h>
#include <stdlib.h>

int main()
{
	char input_line[15], string_num1[6], string_num2[6];
	long int  num1, num2, list1[1000], list2[1000];
	int list_position = 0;
	char *endptr;

	FILE *file_pointer;
	file_pointer = fopen("input", "r");


	while(fgets(input_line, 15, file_pointer))
	{
		int i;
		for(i = 0; i < 5; i++)
		{
			string_num1[i] = input_line[i];
			string_num1[5] = '\0';
		}

		for(i = 12; i > 7; i--)
		{
			string_num2[i - 8] = input_line[i];
			string_num2[5] = '\0';
		}

		list1[list_position] = strtol(string_num1, &endptr, 10);
		list2[list_position] = strtol(string_num2, &endptr, 10);

		list_position++;
	}

	fclose(file_pointer);

	return 0;
}
