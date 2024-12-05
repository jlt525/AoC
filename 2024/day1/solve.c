#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void generate_lists(char* input_file, int (*list1)[], int (*list2)[]);
void bubble_sort_list(int (*list)[]);

int main(int argc, char *argv[])
{
	int i, c, counter, similarity_score, list1[1000], list2[1000], total_distance;
	
	generate_lists(argv[1], &list1, &list2);
	bubble_sort_list(&list1);
	bubble_sort_list(&list2);

	for(i = 0; i < 1000; i++)
	{
		counter = 0;
		for(c = 0; c < 1000; c++)
		{
			if(list1[i] == list2[c])
			{
				counter++;
			}
		}
		
		similarity_score += list1[i] * counter;
		total_distance += abs(list1[i] - list2[i]);
	}
	
	printf("|%-20s|%-20s|\n", "total distance", "similarity score");
	printf("|%-20d|%-20d|\n", total_distance, similarity_score);

	return 0;
}

void generate_lists(char input_file[6], int (*list1)[], int (*list2)[])
{
	int list_position = 0;
	char input_line[15], string_num1[6], string_num2[6];
	char *endptr;
	FILE *file_pointer;
	file_pointer = fopen(input_file, "r");

	while(fgets(input_line, 15, file_pointer))
	{
		int i;
		for(i = 0; i < 5; i++)
		{
			string_num1[i] = input_line[i];
			string_num2[i] = input_line[i + 8];
			string_num2[5] = string_num1[5] = '\0';
		}

		(*list1)[list_position] = (int)strtol(string_num1, &endptr, 10);
		(*list2)[list_position] = (int)strtol(string_num2, &endptr, 10);

		list_position++;
	}

	(void)fclose(file_pointer);
}

void bubble_sort_list(int (*list)[])
{
	int list_length = 1000, list_position, tmp_int = 0;
	bool sorted = false;

	while(sorted != true)
	{
		for(list_position = 0; list_position < list_length - 1; list_position++)
		{
			if((*list)[list_position] > (*list)[list_position + 1])
			{
				tmp_int = (*list)[list_position];
				(*list)[list_position] = (*list)[list_position + 1];
				(*list)[list_position + 1] = tmp_int;
			}
		}
		sorted = true;

		for(list_position = 0; list_position < list_length - 1; list_position++)
		{
			if((*list)[list_position] > (*list)[list_position + 1])
			{
				sorted = false;
			}
		}
	}
}
