#include <linux/init.h> 
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("InPyjama Piyush");
MODULE_DESCRIPTION("Our first dynamically loadable kernel module");

static ssize_t pyjama_read(struct file *, char __user *, size_t, loff_t *);

static struct proc_dir_entry *custom_proc_entry;

struct proc_ops driver_proc_ops = {
    .proc_read = pyjama_read
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
    printk("pyjama_read\n");

    const char msg[] = "ACK!\n";
    const size_t len = strlen(msg);
    
    // offset value is zero on the first call and we can update it for the next call
    // check if buffer already read
    if(len <= *offset) {
        return 0; // cat stop calling the read function
    }

    if(0 != copy_to_user(user_space_buffer, msg, len)) {
        printk("pyjama_read : copy to user call failed\n");
        return -1;
    }

    *offset += len;

    return len; // len > 0; cat call read function again
}
