/*
 * demo-module.c
 * 
 * Compile with
 *  gcc -I/path-to-linux-tree/include -D__KERNEL__ -DMODULE -O2 \
 *     -Wall -Wstrict-prototypes -c -o demo-module.o demo-module.c
 * */

#include <linux/init.h>
#include <linux/module.h>

static int __init demo_init(void) {
	        printk("initializing..\n");
		        return 0;
}

static void __exit demo_exit(void) {
	        printk("goodbye!\n");
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
