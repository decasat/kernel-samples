/*********************************************************************\
*	Filename: First.c 
* 
*	Description: 
*	programmer: Sateesh Kumar G <contact@sateeshkg.com>
*	date begun: 04 DEC 2017
\*********************************************************************/

#include <linux/module.h>	// for init_module() 
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/version.h>

char modname[] = "First";


int __init init_module( void )
{
	pr_info("Installing \'%s\' module\n", modname );
	printk(KERN_INFO "Hello\n");

	return	0;  // SUCCESS
}


void __exit cleanup_module( void )
{
	pr_info( "Removing \'%s\' module\n", modname );
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("SATEESH KG <contact@sateeshkg.com>");
MODULE_DESCRIPTION("Details: This is my first module");





