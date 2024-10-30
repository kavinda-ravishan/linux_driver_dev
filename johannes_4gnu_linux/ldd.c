#include <linux/module.h>
#include <linux/init.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("kavinda");
MODULE_DESCRIPTION("simple example");

static int __init ModuleInit(void) {
    printk("module init call\n");
    return 0;
}

static void __exit ModuleExit(void) {
    printk("module exit call\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
