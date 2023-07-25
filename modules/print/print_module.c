#include <linux/init.h>
#include <linux/module.h>

int count = 1;
module_param(count, int, 0644);

int print_module_init(void)
{
    int i;
    printk(KERN_ALERT "In func -> %s\n", __FUNCTION__);

    for(i = 0; i < count; i++)
    {
        printk(KERN_ALERT "Iter(%d)in func -> %s\n", i, __FUNCTION__);
    }

    return 0;
}

void print_module_exit(void)
{
    printk(KERN_ALERT "In func -> %s\n", __FUNCTION__);
}


module_init(print_module_init);
module_exit(print_module_exit);

MODULE_LICENSE("GPL");