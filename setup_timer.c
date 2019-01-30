#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
struct timer_list my_timer;

void my_callback(struct timer_list *t)
{
	/* do your timer stuff here */
	pr_info("Hello timer callback\n");
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(500));
}


int init_module(void)
{
	int flags = 0;
	timer_setup(&my_timer, &my_callback, flags);
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(500));
	return 0;
}

void cleanup_module(void)
{
	/* remove kernel timer when unloading module */
	del_timer(&my_timer);
	pr_info("Timer removed\n");
}
