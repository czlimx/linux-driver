#include <linux/init.h>
#include <linux/module.h>
#include <linux/atomic.h>

static atomic_t atomic;

static int __init xxx_init(void)
{
	printk("xxx_init\n");

	atomic_set(&atomic, 10);
	printk("atomic value :%d\n", atomic_read(&atomic));

	atomic_add(3, &atomic);
	printk("atomic value :%d\n", atomic_read(&atomic));

	atomic_sub(5, &atomic);
	printk("atomic value :%d\n", atomic_read(&atomic));

	atomic_inc(&atomic);
	printk("atomic value :%d\n", atomic_read(&atomic));

	atomic_dec(&atomic);
	printk("atomic value :%d\n", atomic_read(&atomic));
	
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

