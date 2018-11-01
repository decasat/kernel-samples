/*********************************************************************\
*	Filename: dep-module-1.c 
* 
*	Description: Module dependency Demo 1
*	programmer: Sateesh Kumar G <contact@sateeshkg.com>
*	date begun: 04 DEC 2017
\*********************************************************************/

#include <linux/module.h>	// for init_module() 
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>

static int sk_var = 100;
static void sk_func(void);

EXPORT_SYMBOL_GPL(sk_var);
EXPORT_SYMBOL_GPL(sk_func);


char modname[] = "dep-module-1";

static void sk_func(void) 
{
	printk("I am in func call..\n");
	sk_var++;
	printk("In func() -- sk_var = %d\n",sk_var);

}



static int __init my_init( void )
{
	pr_info("Installing \'%s\' module\n", modname );
	printk("sk_var = %d\n",sk_var);
	sk_func();
	printk("sk_var = %d\n",sk_var);

	return	0;  // SUCCESS
}


static void __exit my_exit( void )
{
	pr_info( "Removing \'%s\' module\n", modname );
}

module_init( my_init );
module_exit( my_exit );

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SATEESH KG <contact@sateeshkg.com>");
MODULE_DESCRIPTION("Details:");
