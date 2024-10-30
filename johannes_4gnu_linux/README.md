### build the project
* `make all`

* `sudo dmesg -c` : for clear the kernal logs

### load the device and create a node to /dev
* `sudo insmod ldd.ko`
* `sudo mknod /dev/sls_dev c 90 0` : add loaded 'sls_dev' to /dev/ (c - char driver, 90 - major num, 0 - minor num)
* `ls /dev/sls_dev -al` : check added node to /dev/
* `sudo chmod 666 /dev/sls_dev` : change permission

### run user app
* `./app.out`

### cleanup
* `make clean`
* `sudo rm /dev/sls_dev`
* `sudo rmmod ldd.ko`
