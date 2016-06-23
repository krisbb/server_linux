#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#define DRIVER_AUTHOR "krisbb"
#define DRIVER_DESC "test sample driver"

static int __init lkm_init(void)
{
	printk( KERN_INFO "Hello world \n");

	return 0;
}

static void __exit lkm_exit(void)
{
	printk(KERN_INFO "Goodbye world \n");
}

module_init(lkm_init);
module_exit(lkm_exit);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

