#include <linux/init.h>
#include <linux/module.h>
#include <linux/mutex.h>

static struct mutex mutex;

static int __init xxx_init(void)
{
	printk("xxx_init\n");

	mutex_init(&mutex);

	mutex_lock(&mutex);
	mutex_unlock(&mutex);

	printk("mutex lock interruptible :%d\n", mutex_lock_interruptible(&mutex));
	printk("mutex trylock :%s\n", mutex_trylock(&mutex) ? "success" : "failure");
	mutex_unlock(&mutex);
	
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

