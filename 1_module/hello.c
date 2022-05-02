#include <linux/init.h>
#include <linux/module.h>

static int __init xxx_init(void)
{
	printk("xxx_init\n");
	return 0;
}

static void __exit xxx_exit(void)
{
	printk("xxx_exit\n");
}

module_init(xxx_init);
module_exit(xxx_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("czlimx@163.com");

