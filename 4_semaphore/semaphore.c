#include <linux/init.h>
#include <linux/module.h>
#include <linux/semaphore.h>

static struct semaphore sem;

static int __init xxx_init(void)
{
	printk("xxx_init\n");

	sema_init(&sem, 10);

	down(&sem);

	up(&sem);

	printk("down interrupt:%d\n", down_interruptible(&sem));

	printk("try get lock:%d\n", down_trylock(&sem));
	
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

