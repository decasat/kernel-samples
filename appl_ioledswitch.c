#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "io_header.h"


int main(void)
{
	int fd;
	int gpio_out = 49;
	int gpio_in = 115;
	int in = 1, out = 0;
	unsigned int l;
	int get;

	fd = open("/dev/IO_LED", O_RDWR);
	if (fd < 0) {
		perror("open");
		_exit(1);
	}

	ioctl(fd, set_gpio_pin, &gpio_in);
	ioctl(fd, set_gpio_pin, &gpio_out);

	ioctl(fd, set_gpio_dir_out, &gpio_out);
	ioctl(fd, set_gpio_dir_in, &gpio_in);

	while (1) {

		ioctl(fd, get_gpio_in, &get);
		printf("%d\n", get);

		/*switch(get)
		   {
		   case 0:
		   ioctl(fd,set_gpio_value,&out);
		   break;
		   case 1:
		   ioctl(fd,set_gpio_value,&in);
		   break;
		   default:
		   ioctl(fd,set_gpio_value,&out);
		   break;
		   }
		 */

		if (get == 1) {
			ioctl(fd, set_gpio_value, &in);
		} else {
			ioctl(fd, set_gpio_value, &out);
		}
	}

	close(fd);
	_exit(0);
}
