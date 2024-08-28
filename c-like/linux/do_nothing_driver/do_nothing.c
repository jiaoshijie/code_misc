#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiaoshijie");
MODULE_DESCRIPTION("Do nothing linux kernel module");

// Buffer for data
static char buffer[255];
static int buffer_pointer;

// Variables for device and device class
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME  "do_nothing"
#define DRIVER_CLASS "do_nothing_class"

/*
 * @brief Read data out of the buffer
 * */
static ssize_t driver_read(struct file *File, char *user_buf, size_t count, loff_t *offs) {
    int to_copy, not_copied, delta;

    to_copy = umin(count, buffer_pointer);

    not_copied = copy_to_user(user_buf, buffer, to_copy);

    delta = to_copy - not_copied;

    return delta;
}

/*
 * @brief Write data to buffer
 * */
static ssize_t driver_write(struct file *File, const char *user_buf, size_t count, loff_t *offs) {
    int to_copy, not_copied, delta;

    to_copy = umin(count, sizeof(buffer));

    not_copied = copy_from_user(buffer, user_buf, to_copy);
    buffer_pointer = to_copy;

    delta = to_copy - not_copied;

    return delta;
}

/*
 * @brief This function is called, when the device file is opened
 * */
static int driver_open(struct inode *device_file, struct file *instance) {
    printk("dev_nr - open was called!\n");
    return 0;
}


/*
 * @brief This function is called, when the device file is closed
 * */
static int driver_close(struct inode *device_file, struct file *instance) {
    printk("dev_nr - close was called!\n");
    return 0;
}


static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .read = driver_read,
    .write = driver_write,
};


// #define MYMAJOR 300
/*
 * @brief This function is called, when the module is loaded into the kernel
 * */
static int __init module_init_(void) {
    // int retval;

    printk("Hello, Kernel!\n");
    // register device nr.
    // retval = register_chrdev(MYMAJOR, "my_dev_nr", &fops);
    // if (retval == 0) {
    //     printk("dev_nr - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
    // } else if (retval > 0) {
    //     printk("dev-nr - registered Device number Major: %d, Minor: %d\n", retval >> 20, retval & 0xfffff);
    // } else {
    //     printk("Could not register device number\n");
    //     return -1;
    // }

    // Allocate a device number
    if (alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
        printk("Device Nr. could not be allocated!!!\n");
        return -1;
    }
    printk("read_write - Device Nr. Major: %d, Minor: %d was registered!\n", my_device_nr >> 20, my_device_nr && 0xfffff);

    // Create device class
    if ((my_class = class_create(DRIVER_CLASS)) == NULL) {
        printk("Device class can not be created!\n");
        goto ClassError;
    }
    printk("do_nothing: my_class = %p\n", my_class);

    // create device file
    if (device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
        printk("Can not create device file!\n");
        goto FileError;
    }

    // Initializze device file
    cdev_init(&my_device, &fops);

    // Registering device to kernel
    if (cdev_add(&my_device, my_device_nr, 1) < 0) {
        printk("Registering of device to kernel failed!\n");
        goto AddError;
    }
    printk("do_nothing is successfully created!!!\n");
AddError:
    device_destroy(my_class, my_device_nr);
FileError:
    class_destroy(my_class);
ClassError:
    unregister_chrdev(my_device_nr, DRIVER_NAME);
    return 0;
}

/*
 * @brief This function is called, when the module is removed from the kernel
 * */
static void __exit module_exit_(void) {
    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev(my_device_nr, DRIVER_NAME);
    // unregister_chrdev(MYMAJOR, "my_dev_nr");
    printk("Goodbye, kernel!\n");
}

module_init(module_init_);
module_exit(module_exit_);
