/***************************rate_limit.c*****************************************\
 * Decscipetion : check the printk ratelimit value and print 			*
 *										*
 * $ cat /proc/sys/kernel/printk_ratelimit_burst				*
 * 10										*
 * $ cat /proc/sys/kernel/printk_ratelimit					*
 * 5 										*
\*******************************************************************************/

#include <linux/module.h>
#include <linux/kernel.h>


int rate_limit_init(void)
{
	int i;
	unsigned long j0, j1;

	j0 = jiffies;
	j1 = jiffies + 30 * HZ;

	for (i = 0; i < 20; i++) {
		if (printk_ratelimit()) {
			printk(KERN_INFO "Printing %d", i);
		}
	}

	return 0;
}

void rate_limit_exit(void)
{
	printk(KERN_INFO "Done");

}

module_init(rate_limit_init);
module_exit(rate_limit_exit);
