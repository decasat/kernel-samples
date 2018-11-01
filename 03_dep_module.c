/*********************************************************************\
*	Filename: dep-module-2.c 
* 
*	Description: Module dependance demo 2 program
*	programmer: Sateesh Kumar G 
*	date begun: 04 DEC 2007
\*********************************************************************/

#include <linux/module.h>	// for init_module() 
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>

char modname[] = "dep-module-2";

extern int sk_var;
extern void sk_func(void);

static int __init my_init( void )
{
	pr_info("Installing \'%s\' module\n", modname );
	printk("Filename : %s \n",__FILE__);
	printk("sk_val = %d\n", sk_var);
	sk_func();

	return	0;  // SUCCESS
}


static void __exit my_exit( void )
{
	pr_info( "Removing \'%s\' module\n", modname );
}

module_init( my_init );
module_exit( my_exit );

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SATEESH KG ");
MODULE_DESCRIPTION("Details:");
