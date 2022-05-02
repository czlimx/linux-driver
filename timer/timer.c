#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list xxx_timer;

static void timer_handler(struct timer_list *timer)
{
	printk("timer_handler\n");
}

static int __init xxx_init(void)
{
	printk("xxx_init\n");

	timer_setup(&xxx_timer, timer_handler, 0);
	
	mod_timer(&xxx_timer, jiffies + msecs_to_jiffies(1000));	//1S后触发一次
	
	return 0;
}

static void __exit xxx_exit(void)
{
	del_timer(&xxx_timer);
	printk("xxx_exit\n");
}

module_init(xxx_init);
module_exit(xxx_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("czlimx@163.com");