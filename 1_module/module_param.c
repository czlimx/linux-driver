#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

static unsigned int base[10];
static unsigned int number;
module_param_array(base, uint, &number, S_IRUSR);

static char *sender;
module_param(sender, charp, S_IRUSR);

static int __init xxx_init(void)
{
	unsigned int i = 0;
	
	printk("xxx_init\n");

	for (i = 0; i < number; i++){
		printk("base[%d] :%d\n", i, base[i]);
	}
	
	printk("sender :%s\n", sender);
	
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

