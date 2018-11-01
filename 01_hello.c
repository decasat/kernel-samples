#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/version.h>

#define DRVNAME "first drvier"


static int __init start(void)
{
	printk(KERN_DEBUG "Hello world driver\n");
	pr_info("Hello world\n");
	return 0;
}

static void __exit stop(void)
{
	printk(KERN_INFO "Good bye driver\n");
}


module_init(start);
module_exit(stop);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAteeshKG");
MODULE_DESCRIPTION("This is demo module");




