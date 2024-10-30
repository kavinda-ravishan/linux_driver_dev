#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("kavinda");
MODULE_DESCRIPTION("simple linux driver - sls");

/**
 * @brief driver open/close callback functions
 */
static int driver_open(struct inode *device_file, struct file *instance) {
    printk("dev_sls - open was called\n");
    return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
    printk("dev_sls - close was called\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close
};

#define SLS_MAJOR 90
#define SLS_CHAR_DEVICE_NAME "sls_dev"

/**
 * @brief Module init and exit functions
 */
static int __init ModuleInit(void) {
    printk("module_sls init call\n");

    /* register the device (get already registerd device numbers `cat /proc/devices`) */
    const int ret_val = register_chrdev(SLS_MAJOR, SLS_CHAR_DEVICE_NAME, &fops);

    if(ret_val == 0) {
        printk("dev_sls - Registerd device number Major: %d, Minor: %d\n", SLS_MAJOR, 0);
    } else if (ret_val > 0) {
        printk("dev_sls - Registerd device number Major: %d, Minor: %d\n", MAJOR(ret_val), MINOR(ret_val));
    } else {
        printk("Could not register device number!\n");
        return -1;
    }

    return 0;
}

static void __exit ModuleExit(void) {
    unregister_chrdev(SLS_MAJOR, SLS_CHAR_DEVICE_NAME);
    printk("module_sls exit call\n");
}

/**
 * @brief Register the module init and exit functions
 */
module_init(ModuleInit);
module_exit(ModuleExit);
