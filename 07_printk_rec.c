#include <linux/module.h>

int start(void)
{
	int i;
	for(i=0;i < 20 ;i++)
		pr_info("Hello\n");
	return 0;
}

void stop(void)
{
	pr_info("removed\n");
}
module_init(start);
module_exit(stop);

