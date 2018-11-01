/*********************************************************************\
*	Filename: pram-module.c 
* 
*	Description: Module prameter passing
*	programmer: Sateesh Kumar G 
*	date begun: 04 DEC 2007
\*********************************************************************/

#include <linux/module.h>	// for init_module() 
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/slab.h>

char modname[] = "pram-module";


static short int myshort = 1;
static int myint = 555;
static long int mylong = 99999;
static char *mystring = "HELLO";
static int myintArray[2] = { -1, -1};
static int arr_argc = 0;

//module_param(name, type, mode) 

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort,"A short integer");

module_param(myint, int , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myint, "An integer");

module_param(mylong , long , S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");

module_param(mystring, charp, 0600);
MODULE_PARM_DESC(mystring, "A character string");

module_param_array(myintArray, int , &arr_argc, 0600);
MODULE_PARM_DESC(myintArray, "An array of integers");

static int __init my_init( void )
{
	int i;
	pr_info("Installing \'%s\' module\n", modname );
	
	printk(KERN_INFO " Module param demonstration5\n ===========================\n");
	printk(KERN_INFO "myshort is short integer: %d\n", myshort);
	printk(KERN_INFO "myint is integer : %d\n", myint);
	printk(KERN_INFO "mylong is long integer %ld\n", mylong);
	printk(KERN_INFO "mystring is character string %s \n", mystring);
	for(i = 0; i < (sizeof myintArray/sizeof(int)); i++)
	{
		printk(KERN_INFO "myintArray[%d] = %d \n", i , myintArray[i]);
	}
	printk(KERN_INFO "got %d arguments for myintArray. \n", arr_argc);
	return 0;
}
static void __exit my_exit( void )
{
	pr_info( "Removing \'%s\' module\n", modname );
}

module_init( my_init );
module_exit( my_exit );


/*kernel module licensing with GPL */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SATEESH KG");
MODULE_DESCRIPTION("Details:");


