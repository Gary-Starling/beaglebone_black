#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gary-Starling");
MODULE_DESCRIPTION("Test char driver");
MODULE_VERSION("0.1");

#define CHAR_BUFF_SIZE (1024)
static char chardrv_buff[CHAR_BUFF_SIZE];

/* prototypes */
int chardrv_open(struct inode *pinode, struct file *pfile);
ssize_t chardrv_read(struct file *pfile, char __user *buff, size_t len, loff_t *offset);
ssize_t chardrv_wrie(struct file *pfile, const char __user *buff, size_t len, loff_t *offset);
int chardrv_close(struct inode *pinode, struct file *pfile);
loff_t chardrv_llseek(struct file *pfile, loff_t offset, int pos);

/* fops for driver */
const struct file_operations chardrv_foper = {
    .owner = THIS_MODULE,
    .open = chardrv_open,
    .llseek = chardrv_llseek,
    .read = chardrv_read,
    .write = chardrv_wrie,
    .release = chardrv_close,
};

/* */
static struct cdev cdev_chardrv;
dev_t dev_numb;
static struct class *dev_class;

int chardrv_open(struct inode *pinode, struct file *pfile)
{
    printk(KERN_ALERT "In func -> %s\n", __FUNCTION__);
    return 0;
}

ssize_t chardrv_read(struct file *pfile, char __user *buff, size_t len, loff_t *offset)
{
    printk(KERN_ALERT "In func -> %s\n", __FUNCTION__);

    //if (len - 1 < CHAR_BUFF_SIZE)
    //{
        copy_to_user(buff, chardrv_buff, CHAR_BUFF_SIZE);
        printk(KERN_INFO "Data read.\n");
        printk(KERN_INFO ": %s\n", chardrv_buff);
    //}

    return 0;
}

ssize_t chardrv_wrie(struct file *pfile, const char __user *buff, size_t len, loff_t *offset)
{
    printk(KERN_ALERT "In func -> %s\n", __FUNCTION__);
    if (len - 1 < CHAR_BUFF_SIZE)
    {
        copy_from_user(chardrv_buff, buff, len);
        chardrv_buff[len - 1] = '0';
        printk(KERN_INFO "Data write.\n");
    }
    else
        printk(KERN_INFO "Data size > CHAR_BUFF_SIZE \n");

    return len;
}

int chardrv_close(struct inode *pinode, struct file *pfile)
{
    printk(KERN_ALERT "In func -> %s\n", __FUNCTION__);
    return 0;
}

loff_t chardrv_llseek(struct file *pfile, loff_t offset, int pos)
{
    return 0;
}

int chardrv_module_init(void)
{
    int res; // result alloc_chrdev_region

    printk(KERN_ALERT "In func -> %s\n", __FUNCTION__);

    /* dynamicl alloc         :devn: firrs_minor: cnt:  name*/
    res = alloc_chrdev_region(&dev_numb, 0, 4, "chardrv");
    if (res < 0)
    {
        printk(KERN_ERR "Error getting major number.\n");
        return res;
    }

    printk(KERN_INFO "Major = %d Minor = %d.\n", MAJOR(dev_numb), MINOR(dev_numb));

    /* init cdev str */
    cdev_chardrv.owner = THIS_MODULE;
    cdev_init(&cdev_chardrv, &chardrv_foper);

    /* reg cdev */
    if (cdev_add(&cdev_chardrv, dev_numb, 1) < 0)
    {
        printk(KERN_ERR "Error add cdev to system.\n");
        goto error_dev;
    }

    /* creating class */
    if ((dev_class = class_create(THIS_MODULE, "chardrv_class")) == NULL)
    {
        printk(KERN_ERR "Error creating class.\n");
        goto error_dev;
    }

    /* creat device */
    if ((device_create(dev_class, NULL, dev_numb, NULL, "chardrv")) == NULL)
    {
        printk(KERN_INFO "Error create device.\n");
        goto error_class;
    }

    printk(KERN_INFO "Chardriver init : OK.\n");
    return 0;

error_class:
    class_destroy(dev_class);
error_dev:
    unregister_chrdev_region(dev_numb, 1);

    return -1;
}

void chardrv_module_exit(void)
{
    printk(KERN_ALERT "In func -> %s\n", __FUNCTION__);
    device_destroy(dev_class, dev_numb);
    class_destroy(dev_class);
    cdev_del(&cdev_chardrv);
    unregister_chrdev_region(dev_numb, 1);
    printk(KERN_INFO "Chardriver deinit : OK.\n");
}

module_init(chardrv_module_init);
module_exit(chardrv_module_exit);
