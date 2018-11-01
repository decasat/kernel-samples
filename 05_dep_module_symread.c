/*********************************************************************\
*	Filename: dep-module-symread-4.c 
* 
*	Description: 
*	programmer: Sateesh Kumar G 
*	date begun: 04 DEC 2007
\*********************************************************************/

#include <linux/module.h>	// for init_module()
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>

char modname[] = "dep-module-symread-4";

static int *ptr;

static int __init my_init(void)
{
	pr_info("Installing \'%s\' module\n", modname);
	ptr = (int *) __symbol_get("sk_var");
	if (ptr) {

		*ptr = 777;
		__symbol_put("sk_var");
		return 0;
	} else {
		printk(KERN_INFO "symbol not available\n");
		return -1;
	}

	return 0;		// SUCCESS
}


static void __exit my_exit(void)
{
	pr_info("Removing \'%s\' module\n", modname);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SATEESH KG ");
MODULE_DESCRIPTION("Details:");
