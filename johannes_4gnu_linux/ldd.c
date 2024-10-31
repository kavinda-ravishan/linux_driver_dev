#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("kavinda");
MODULE_DESCRIPTION("simple linux driver - sls");

#define DRIVER_NAME "sls_dev"
#define DRIVER_CLASS "sls_module_class"

/* variables for device and device class */
static dev_t sls_device_num;
static struct class *sls_device_class;
static struct cdev sls_device; 

/**
 * @brief buffer for data
 */
static char buffer[255];
static unsigned int buffer_pointer; // number of bytes filled

/**
 * @brief read/write functions
 */
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
    static unsigned int to_copy, not_copied, delta;

    to_copy = min(count, buffer_pointer);

    not_copied = copy_to_user(user_buffer, buffer, to_copy);

    delta = to_copy - not_copied;

    return delta;
}

static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
    static unsigned int to_copy, not_copied, delta;

    to_copy = min(count, sizeof(buffer));
    buffer_pointer = to_copy;

    not_copied = copy_from_user(buffer, user_buffer, to_copy);

    delta = to_copy - not_copied;

    return delta;
}

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

/* file operations */
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .read = driver_read,
    .write = driver_write
};

/**
 * @brief Module init and exit functions
 */
static int __init ModuleInit(void) {
    printk("module_sls init call\n");

    /* allocate a the device number */
    if(0 > alloc_chrdev_region(&sls_device_num, 0, 1, DRIVER_NAME)) {
        printk("Device number could not be allocated!\n");
        return -1;
    }

    printk("SLS - device number. Major : %d, Minor: %d was registerd\n", MAJOR(sls_device_num), MINOR(sls_device_num));

    /* create device class */
    sls_device_class = class_create(DRIVER_CLASS);
    
    if(NULL == sls_device_class) {
        printk("Device class cannot be created!\n");
        goto ClassError;
    }

    /* create device file */
    if(NULL == device_create(sls_device_class, NULL, sls_device_num, NULL, DRIVER_NAME)) {
        printk("Unable to create the device file!\n");
        goto FileError;
    }

    /* Initialize device file */
    cdev_init(&sls_device, &fops);

    /* registering device to kernal*/
    if(-1 == cdev_add(&sls_device, sls_device_num, 1)) {
        printk("Registering of device to kernal failed!\n");
        goto AddError;
    }

    return 0;

AddError:
    device_destroy(sls_device_class, sls_device_num);
FileError:
    class_destroy(sls_device_class);
ClassError:
    unregister_chrdev(sls_device_num, DRIVER_NAME);

    return -1;
}

static void __exit ModuleExit(void) {

    cdev_del(&sls_device);
    device_destroy(sls_device_class, sls_device_num);
    class_destroy(sls_device_class);
    unregister_chrdev(sls_device_num, DRIVER_NAME);

    printk("module_sls exit call\n");
}

/**
 * @brief Register the module init and exit functions
 */
module_init(ModuleInit);
module_exit(ModuleExit);
