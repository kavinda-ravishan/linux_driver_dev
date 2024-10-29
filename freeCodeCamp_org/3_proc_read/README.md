## 1_hello_world

* `make all`
* `sudo insmod ldd.ko` : load driver to kernal
* `sudo dmesg` : print messages to terminal
* `sudo dmesg -c` : print and clear
* `sudo rmmod ldd` : remove driver from kernal
* `modinfo ldd.ko` : print driver info
* `lsmod` : Show the status of modules in the Linux Kernel

### insmod module

1. calls `init_module` to hint the kernel that a module insertion is attempted.
2. Transfers control to the kernel.
3. kernel execute `sys_init_module`
4. Verifies permissions
5. `load_module` function is called
    1. Checks the sanity of the .ko
    2. Creates memory.
    3. Copies from user space to kernel space.
    4. Resolves sysmbols.
    5. Returns a reference to the Kernel
6. Adds the reference to a linked list that has all the loaded modules.
7. `module_init` listed function


### rmmod module

1. `rmmod` calls `delete_module()` which hints the kernel that a module is to be removed.
    1. Control is transferred to the kernel.
2. kernel executes `sys_delete_module()`
    1. Checks the permissions of the one requesting.
    2. Checks if any other loaded module needs the current module.
    3. Checks if the module is actually loaded!
    4. Executes the function provided in `module_exit` 
    5. `free_module()`
        1. removes references and kernel object reference. 
        2. performs any other cleanup.
        3. Unloads the module
        4. Changes the state in list
        5. Removes it from the list and frees the memory.

## 3_proc_read

* `cat /proc/pyjama_driver` : read from proc
* `sudo dmesg` : print log messages
