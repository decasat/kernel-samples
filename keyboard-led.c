/*********************************************************************\
*	Filename: keyboard-led.c 
* 
*	Description: Blink keyboard leds until the module is unloaded.
*		     (modified for 4.19.x)
*	programmer: Sateesh Kumar G <skg@decanetsystems.com>
*	date begun: 28 JAN 2019
\*********************************************************************/


#include <linux/module.h>
#include <linux/configfs.h>
#include <linux/init.h>
#include <linux/tty.h>		/* For fg_console, MAX_NR_CONSOLES */
#include <linux/kd.h>		/* For KDSETLED */
#include <linux/vt.h>
#include <linux/console_struct.h>	/* For vc_cons */
#include <linux/vt_kern.h>
#include <linux/timer.h>


char modname[] = "keyboard-led";

struct timer_list my_timer;
struct tty_driver *my_driver;
int kbledstatus = 0;

#define BLINK_DELAY   HZ/5
#define ALL_LEDS_ON   0x07
#define RESTORE_LEDS  0xFF
/*
 *   Function my_timer_func blinks the keyboard LEDs periodically by invoking
 *   command KDSETLED of ioctl() on the keyboard driver. To learn more on virtual
 *   terminal ioctl operations, please see file:
 *      /usr/src/linux/drivers/char/vt_ioctl.c, function vt_ioctl().
 *
 * The argument to KDSETLED is alternatively set to 7 (thus causing the led
 * mode to be set to LED_SHOW_IOCTL, and all the leds are lit) and to 0xFF
 * (any value above 7 switches back the led mode to LED_SHOW_FLAGS, thus
 *the LEDs reflect the actual keyboard status). To learn more on this,
 * please see file:
 *    /usr/src/linux/drivers/char/keyboard.c, function setledstate().
 *
 **/


void my_timer_func(struct timer_list *t)
{
	int *pstatus=0;
	pstatus = &kbledstatus;
	if (*pstatus == ALL_LEDS_ON)
		*pstatus = RESTORE_LEDS;
	else
		*pstatus = ALL_LEDS_ON;
	(my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,
				 *pstatus);
        mod_timer(&my_timer, jiffies + BLINK_DELAY);
}




static int __init my_init( void )
{
	int i;
 	int flags = 0;
	
	pr_info("Installing \'%s\' module\n", modname );


	printk(KERN_INFO "kbleds: loading\n");
	printk(KERN_INFO "kbleds: fgconsole is %x\n", fg_console);
	for (i = 0; i < MAX_NR_CONSOLES; i++) {
		if (!vc_cons[i].d)
			break;
		printk(KERN_INFO
		       "skg_console: console[%i/%i] #%i, tty %lx\n", i,
		       MAX_NR_CONSOLES, vc_cons[i].d->vc_num,
		       (unsigned long) vc_cons[i].d->port.tty);
	}
	printk(KERN_INFO "kbleds: finished scanning consoles\n");
	my_driver = vc_cons[fg_console].d->port.tty->driver;
	printk(KERN_INFO "kbleds: tty driver magic %x\n",
	       my_driver->magic);
	/*
	 * set up the LED blink timer the first time
	 *                   */
        timer_setup(&my_timer, &my_timer_func, flags);
        mod_timer(&my_timer, jiffies + BLINK_DELAY);

	return	0;  // SUCCESS
}


static void __exit my_exit( void )
{
	pr_info( "Removing \'%s\' module\n", modname );
		printk(KERN_INFO "kbleds: unloading...\n");
	del_timer(&my_timer);
	(my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,
				 RESTORE_LEDS);

}

module_init( my_init );
module_exit( my_exit );

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SATEESH KG <skg@decanetsystems.com>");
MODULE_DESCRIPTION("Details:Key Board LED blinking");

