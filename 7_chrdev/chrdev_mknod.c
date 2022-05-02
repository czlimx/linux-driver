#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

#define XXX_COUNTS	1
#define XXX_NAMES	"xxx"

struct xxx_cdev {
	int major;
	int minor;
	dev_t devid;
	struct cdev cdev;

	struct class *class;
	struct device *device;
};

static struct xxx_cdev xxx;

static ssize_t xxx_read(struct file *file, char __user *buffer, size_t size, loff_t *offset)
{
	printk("xxx_read\n");
	return size;
}

static ssize_t xxx_write(struct file *file, const char __user *buffer, size_t size, loff_t *offset)
{
	printk("xxx_write\n");
	return size;
}

static int xxx_open(struct inode *inode, struct file *file)
{
	printk("xxx_open\n");
	return 0;
}

static int xxx_release(struct inode *inode, struct file *file)
{
	printk("xxx_release\n");
	return 0;
}

static const struct file_operations xxx_fops = {
	.owner 		= THIS_MODULE,
	.read		= xxx_read,
	.write		= xxx_write,
	.open		= xxx_open,
	.release	= xxx_release,
};

static int __init xxx_init(void)
{
	int ret;
	printk("xxx_init\n");

	memset(&xxx, 0, sizeof(xxx));
	if (xxx.major){
		ret = register_chrdev_region(MKDEV(xxx.major, xxx.minor), XXX_COUNTS, XXX_NAMES);
		if (ret < 0)
			goto chrdev_failure;

		xxx.devid = MKDEV(xxx.major, xxx.minor);
	} else {
		ret = alloc_chrdev_region(&xxx.devid, 0, XXX_COUNTS, XXX_NAMES);
		if (ret < 0)
			goto chrdev_failure;

		xxx.major = MAJOR(xxx.devid);
		xxx.minor = MINOR(xxx.devid);
	}

	cdev_init(&xxx.cdev, &xxx_fops);
	ret = cdev_add(&xxx.cdev, xxx.devid, XXX_COUNTS);
	if (ret < 0)
		goto cdev_failure;

	xxx.class = class_create(THIS_MODULE, "my_class");
	if (IS_ERR(xxx.class)){
		ret = PTR_ERR(xxx.class);
		goto class_failure;
	}

	xxx.device = device_create(xxx.class, NULL, xxx.devid, NULL, "%s%d", XXX_NAMES, 0);
	if (IS_ERR(xxx.device)){
		ret = PTR_ERR(xxx.device);
		goto device_failure;
	}
	
	return 0;
device_failure:
	class_destroy(xxx.class);
class_failure:
	cdev_del(&xxx.cdev);
cdev_failure:
	unregister_chrdev_region(xxx.devid, XXX_COUNTS);
chrdev_failure:
	return ret;
}

static void __exit xxx_exit(void)
{
	device_destroy(xxx.class, xxx.devid);
	class_destroy(xxx.class);
	cdev_del(&xxx.cdev);
	unregister_chrdev_region(xxx.devid, XXX_COUNTS);
	printk("xxx_exit\n");
}

module_init(xxx_init);
module_exit(xxx_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("czlimx@163.com");

