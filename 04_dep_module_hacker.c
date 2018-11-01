/*********************************************************************\
*	Filename: dep-module-hack.c 
* 
*	Description: module hack symbols
*	programmer: Sateesh Kumar G 
*	date begun: 04 DEC 2007
\*********************************************************************/

#include <linux/module.h>	// for init_module() 
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>

char modname[] = "dep-module-hack";


int *ptr;
static int __init my_init( void )
{
	pr_info("Installing \'%s\' module\n", modname );
	//ptr = (int *)[...] ; /* ascertain actual address & insert */
	ptr = (int *)0xffffffffc02b6010; /* ascertain actual address & insert */
	*ptr = 999;

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

