# get_next_line Project
This project is an implementation of the get_next_line function in C. The function reads a single line from a file descriptor, ending with a newline character or EOF. The project is designed to help understand file reading, buffer management, and static variables.

## Usage
The function can be used in the following way:
```c
#include "get_next_line.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			printf("%s", line)
			free(line);
		}
		if (ret == -1)
			printf("An error occurred while reading the file\n");
		close(fd);
	}
	return (0);
}
```
## Learning Outcomes
This project helped me understand:
* How to read from a file descriptor
* The use of static variables
* Buffer management in C
## Limitations
The get_next_line function only supports reading from a single file descriptor at a time.
