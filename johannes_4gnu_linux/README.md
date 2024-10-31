### build the project
* `make all`

* `sudo dmesg -c` : for clear the kernal logs

### load the device and create a node to /dev
* `sudo insmod ldd.ko`
* `sudo chmod 666 /dev/sls_dev` : change permission
* `ls /dev/sls_dev -al` : check added node to /dev/

### tests
* `echo "hello word" > /dev/sls_dev`
* `head -n 1 /dev/sls_dev`

### run user app
* `./app.out`

### cleanup
* `sudo rmmod ldd.ko`
* `make clean`
