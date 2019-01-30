#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/current.h>

#include "io_header.h"

#define CHAR_NAME "IO_LED"

static dev_t first;
static int minor = 0;
static int count = 1;
static struct cdev *mydev;
static struct class *cl;
static int inuse = 0;
static int gpio;
static int gpio_out;
static int gpio_in;

static int open(struct inode *inode, struct file *filp)
{
	inuse++;
	printk(KERN_INFO "This device is open by these many users->%d\n",
	       inuse);
	printk(KERN_INFO "The Majorno->%d and Minorno->%d\n",
	       imajor(inode), iminor(inode));
	printk(KERN_INFO "The Process name->%s and Process id->%d\n",
	       current->comm, current->pid);
	printk(KERN_INFO "The Refno->%d\n", module_refcount(THIS_MODULE));
	return 0;
}

static long ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int nbytes;
	int vl, vlout;
	int value;
	bool vlin;

	switch (cmd) {
	case set_gpio_pin:
		nbytes = copy_from_user(&vl, (int *) arg, sizeof(int));
		gpio = vl;
		if (!(gpio_is_valid(gpio))) {
			printk(KERN_ERR "This gpio%d is not valid\n",
			       gpio);
			return -ENODEV;
		}
		printk(KERN_INFO "This gpio%d is valid\n", gpio);
		gpio_request(gpio, "sysfs");
		gpio_export(gpio, 1);
		printk(KERN_INFO "This gpio%d is exported\n", gpio);
		break;
	case set_gpio_dir_out:
		nbytes = copy_from_user(&vl, (int *) arg, sizeof(int));
		gpio_out = vl;
		gpio_direction_output(gpio_out, 1);
		printk(KERN_INFO
		       "This gpio%d is set the direction to output\n",
		       gpio_out);
		break;
	case set_gpio_dir_in:
		nbytes = copy_from_user(&vl, (int *) arg, sizeof(int));
		gpio_in = vl;
		gpio_direction_input(gpio_in);
		break;
	case set_gpio_value:
		nbytes = copy_from_user(&vl, (int *) arg, sizeof(int));
		value = vl;
		if (value == 0) {
			gpio_set_value(gpio_out, value);
		} else {
			gpio_set_value(gpio_out, value);
		}
		printk(KERN_INFO "The gpio%d value is %d\n", gpio_out,
		       value);
		break;
	case get_gpio_value:
		vlout = gpio_get_value(gpio_out);
		nbytes = copy_to_user((int *) arg, &vlout, sizeof(int));
		printk(KERN_INFO "The gpio%d value is set to out\n",
		       vlout);
		break;
	case set_gpio_unexport:
		nbytes = copy_from_user(&vl, (int *) arg, sizeof(int));
		gpio = vl;
		gpio_unexport(gpio);
		printk(KERN_INFO "The gpio%d is unexported\n", gpio);
		break;
	case set_gpio_free:
		nbytes = copy_from_user(&vl, (int *) arg, sizeof(int));
		gpio = vl;
		gpio_free(gpio);
		printk(KERN_INFO "The gpio%d is freed\n", gpio);
		break;
	case get_gpio_in:
		gpio_set_debounce(gpio_in, 200);
		vlin = gpio_get_value(gpio_in);
		nbytes = copy_to_user((int *) arg, &vlin, sizeof(int));
		break;
	default:
		break;
	}

	return 0;

}

static int close(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "This device is done the job\n");
	return 0;
}

static struct file_operations f_ops = {
	.owner = THIS_MODULE,
	.open = open,
	.unlocked_ioctl = ioctl,
	.release = close,
};

static int __init start(void)
{
	if (alloc_chrdev_region(&first, minor, count, CHAR_NAME) < 0) {
		printk(KERN_ERR
		       "This device is not allocated in the driver\n");
		return -1;
	}
	if (!(mydev = cdev_alloc())) {
		unregister_chrdev_region(first, count);
		printk(KERN_ERR
		       "This device is not allocated with the cdev\n");
		return -1;
	}
	cdev_init(mydev, &f_ops);
	if (cdev_add(mydev, first, count) < 0) {
		cdev_del(mydev);
		unregister_chrdev_region(first, count);
		printk(KERN_ERR
		       "This device is not added with the cdev\n");
		return -1;
	}
	cl = class_create(THIS_MODULE, "My_device");
	device_create(cl, NULL, first, NULL, "%s", CHAR_NAME);
	printk(KERN_INFO "This device is created with the name->%s\n",
	       CHAR_NAME);
	printk(KERN_INFO "The Majorno->%d and Minorno->%d\n", MAJOR(first),
	       MINOR(first));
	printk(KERN_INFO "The Process name->%s and Process id->%d\n",
	       current->comm, current->pid);
	return 0;
}

static void __exit stop(void)
{
	gpio_set_value(gpio_out, 0);
	gpio_unexport(gpio_out);
	gpio_unexport(gpio_in);
	gpio_free(gpio_out);
	gpio_free(gpio_in);
	device_destroy(cl, first);
	class_destroy(cl);
	cdev_del(mydev);
	unregister_chrdev_region(first, count);
	printk(KERN_INFO
	       "This device is successfully removed from the driver and the gpio's are unexported and freed\n");
}

module_init(start);
module_exit(stop);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION("0.1");
MODULE_AUTHOR("sriram");
