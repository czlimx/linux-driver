#include <linux/init.h>
#include <linux/module.h>
#include <linux/spinlock.h>

static int value;
static spinlock_t spinlock;

static int __init xxx_init(void)
{
	unsigned long flags;

	printk("xxx_init\n");

	spin_lock_init(&spinlock);

	spin_lock(&spinlock);
	value++;
	spin_unlock(&spinlock);

	spin_lock_irqsave(&spinlock, flags);
	value--;
	spin_unlock_irqrestore(&spinlock, flags);
	
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

