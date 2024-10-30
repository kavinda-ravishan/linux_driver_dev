#include <linux/init.h> 
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("InPyjama Piyush");
MODULE_DESCRIPTION("Our first dynamically loadable kernel module");

static ssize_t pyjama_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t pyjama_write(struct file *, const char __user *, size_t, loff_t *);

static struct proc_dir_entry *custom_proc_entry;

struct proc_ops driver_proc_ops = {
    .proc_read = pyjama_read,
    .proc_write = pyjama_write
};

static int pyjama_module_init (void) {

    printk("pyjama_module_init: entry\n");

    custom_proc_entry = proc_create("pyjama_driver", 0, NULL, &driver_proc_ops);

    if(NULL == custom_proc_entry) {
        printk("pyjama_module_init: failed\n");
        return -1;
    }

    printk("pyjama_module_init: exit\n");
    
    return 0;
}

static void pyjama_module_exit (void) {
    printk("pyjama_module_exit: entry\n");
    proc_remove(custom_proc_entry);
    printk("pyjama_module_exit: exit\n");
}

module_init(pyjama_module_init);
module_exit(pyjama_module_exit);

static ssize_t pyjama_read(struct file* file_pointer, char __user* user_space_buffer, size_t count, loff_t* offset) {
    printk(KERN_INFO "pyjama_read : count : %li", count);
    return 0;
}

static ssize_t pyjama_write(struct file* file_pointer, const char __user* user_space_buffer, size_t count, loff_t* offset) {
    printk(KERN_INFO "pyjama_write : count : %li", count);
    return count;
}
