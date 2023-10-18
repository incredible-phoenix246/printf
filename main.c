#include "test.h"

int main()
{
	char name[] = "Phoenix";
	char job[] = "cyber security analyst and frontend developer";
	int count = _printf("Name: %s\nJob: %s\nLocation: Kano Nigeria\n", name, job);
	printf("Number of characters printed: %d\n", count);
	return (0);
}
