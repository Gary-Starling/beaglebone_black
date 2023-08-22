#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gary-Starling");
MODULE_DESCRIPTION("Test char driver");
MODULE_VERSION("0.3");

// TODO: settings.h

/* size buffers */
#define BUFF_SIZE (32)
static char device_buff[BUFF_SIZE];

/* number minors */
#define MAX_MINOR (4)

static dev_t dev_numb;
static struct class *dev_class;

/* my struct */
struct chardrv_data
{
    struct mutex lock;
    struct cdev cdev_chardrv;
    unsigned long size;
    // some data
};

static struct chardrv_data devs[MAX_MINOR];

/* prototypes */
int chardrv_open(struct inode *pinode, struct file *pfile);
ssize_t chardrv_read(struct file *pfile, char __user *buff, size_t len, loff_t *offset);
ssize_t chardrv_write(struct file *pfile, const char __user *buff, size_t len, loff_t *offset);
int chardrv_close(struct inode *pinode, struct file *pfile);
loff_t chardrv_llseek(struct file *pfile, loff_t offset, int pos);

/* fops for driver */
const struct file_operations chardrv_foper = {
    .owner = THIS_MODULE,
    .open = chardrv_open,
    .llseek = chardrv_llseek,
    .read = chardrv_read,
    .write = chardrv_write,
    .release = chardrv_close,
};

/**
 * 1)ready? 2)init firs time 3)fill structure
 */
int chardrv_open(struct inode *pinode, struct file *pfile)
{
    struct chardrv_data *dev_data;

    dev_data = container_of(pinode->i_cdev, struct chardrv_data, cdev_chardrv);
    pfile->private_data = dev_data;

    /* init dev? */
    printk(KERN_INFO "In func -> %s\n", __FUNCTION__);
    return 0;
}

/**
 * copy data from device to user space.
 */
ssize_t chardrv_read(struct file *pfile, char __user *buff, size_t len, loff_t *offset)
{
    ssize_t cnt = 0;
    struct chardrv_data *data;
    data = (struct chardrv_data *)pfile->private_data;

    // lock

    printk(KERN_INFO "Debug info\n");
    printk(KERN_INFO "In func -> %s\n", __FUNCTION__);
    printk(KERN_INFO "size_t len, = %zu\n", len);
    printk(KERN_INFO "loff_t *offset = %llu\n", *offset);

    printk(KERN_INFO "Data read\n");

    if (len > BUFF_SIZE)
    {
        /* copy all data*/
        *offset = 0;
        len = BUFF_SIZE;

        if (copy_to_user(buff, &device_buff[*offset], BUFF_SIZE))
        {
            printk(KERN_ALERT "Error read data.\n");
            return -EFAULT;
        }
        cnt = 0;
    }
    else
    {
        if ((*offset + len) > BUFF_SIZE)
        {
            if (copy_to_user(buff, &device_buff[*offset], BUFF_SIZE - *offset))
            {
                printk(KERN_ALERT "Error read data.\n");
                return -EFAULT;
            }
            printk(KERN_INFO "->%.*s\n", (int)(BUFF_SIZE - *offset), &device_buff[*offset]);
            len -= (BUFF_SIZE - *offset);
            *offset = 0;
            cnt += (BUFF_SIZE - *offset);
        }

        if (copy_to_user(buff, &device_buff[*offset], len))
        {
            printk(KERN_ALERT "Error read data.\n");
            return -EFAULT;
        }
        cnt += len;
    }

    
    printk(KERN_INFO "->%.*s\n", (int)(len), &device_buff[*offset]);
    *offset += len;

    // unlock
    return cnt;
}

/**
 * copy data from user space to device
 */
ssize_t chardrv_write(struct file *pfile, const char __user *buff, size_t len, loff_t *offset)
{
    ssize_t res;
    // lock

    printk(KERN_INFO "In func -> %s\n", __FUNCTION__);
    printk(KERN_INFO "Debug info\n");
    printk(KERN_INFO "size_t len, = %zu\n", len);
    printk(KERN_INFO "size_t *offset, = %llu\n", *offset);

    /* case 1 : more data that we can strore at one time */
    if (len > BUFF_SIZE)
    {
        printk(KERN_ALERT "len write (%zu) byte > BUFF_SIZE (%d) byte\n", len, BUFF_SIZE);
        return -EFAULT;
    }

    /* case 2 : we can write to file, but we are at the end of buffer. We will record the firrst part at the end
    and second part to begin of the buffer*/
    if ((*offset + len) > BUFF_SIZE)
    {
        if ((res = copy_from_user(device_buff + *offset, buff, BUFF_SIZE - *offset)))
        {
            printk(KERN_ALERT "Error write data.\n");
            return res;
        }
        len -= (BUFF_SIZE - *offset);
        *offset = 0;
    }

    /* case 3: normal write */
    if ((res = copy_from_user(device_buff + *offset, buff, len)))
    {
        printk(KERN_ALERT "Error write data.\n");
        return res;
    }

    *offset += len;

    printk(KERN_INFO "Data write.\n");

    // unlock
    return len;
}

int chardrv_close(struct inode *pinode, struct file *pfile)
{
    // pinode->i_cdev;
    // pfile->private_data;KERN_ALERT__FUNCTION__);
    return 0;
}

loff_t chardrv_llseek(struct file *pfile, loff_t offset, int pos)
{
    return 0;
}

void chardrv_module_exit(void)
{
    int i;

    printk(KERN_INFO "In func -> %s\n", __FUNCTION__);
    device_destroy(dev_class, dev_numb);
    class_destroy(dev_class);

    for (i = 0; i < MAX_MINOR; i++)
        cdev_del(&devs[i].cdev_chardrv);

    unregister_chrdev_region(dev_numb, 1);
    printk(KERN_INFO "Chardriver deinit : OK.\n");
}

int chardrv_module_init(void)
{
    int res; // result alloc_chrdev_region
    int i;
    int error;

    printk(KERN_INFO "In func -> %s\n", __FUNCTION__);

    /* dynamicl alloc         :devn: firrs_minor: cnt:  name*/
    res = alloc_chrdev_region(&dev_numb, 0, 4, "chardrv");
    if (res < 0)
    {
        printk(KERN_ERR "Error getting major number.\n");
        return res;
    }

    /* init cdev structure */
    for (i = 0; i < MAX_MINOR; i++)
    {
        printk(KERN_INFO "Major = %d Minor = %d.\n", MAJOR(dev_numb), MINOR(dev_numb + i));
        cdev_init(&devs[i].cdev_chardrv, &chardrv_foper);
        devs[i].cdev_chardrv.owner = THIS_MODULE;
        devs[i].cdev_chardrv.ops = &chardrv_foper;
        /* reg cdev */
        error = cdev_add(&devs[i].cdev_chardrv, dev_numb + i, 1);
        if (error < 0)
        {
            printk(KERN_ERR "Error add cdev[%d] to system.\n ERROR=%d", i, error);
            goto error;
        }
    }

  /* creating class */
  if ((dev_class = class_create(THIS_MODULE, "chardrv_class")) == NULL)
  {
      printk(KERN_ERR "Error creating class.\n");
      goto error;
  }

  /*┌─ gary /dev 
└─ $ sudo mknod /dev/char1 c 507 1
┌─ gary /dev 
└─ $ sudo mknod /dev/char2 c 507 2
┌─ gary /dev 
└─ $ sudo mknod /dev/char3 c 507 3
┌─ gary /dev 
└─ $ sudo mknod /dev/char4 c 507 4
┌─ gary /dev 
└─ $ ls grep | char

to device_create(cl, NULL, MKNOD(MAJOR(first), MINOR(first) + i), NULL, "char%d", i);

buffer[0 1 2 3]*/

  /* creat device */
  if ((device_create(dev_class, NULL, dev_numb, NULL, "chardrv")) == NULL)
  {
      printk(KERN_INFO "Error create device.\n");
      goto error;
  }

    printk(KERN_INFO "Chardriver init : OK.\n");
    return 0;

error:
    chardrv_module_exit();

    return res;
}

module_init(chardrv_module_init);
module_exit(chardrv_module_exit);
