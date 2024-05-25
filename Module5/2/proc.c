#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#define SIZE 10
#define PROC_MODE 0
static int len,temp;
static char *msg;
 
ssize_t read_proc(struct file *filp, char *buf, size_t count, loff_t *offp ) {
    if(count > temp) {
        count = temp;
    }
    temp = temp - count;
     if (copy_to_user(buf, msg, count)) {
        return -EFAULT;
    }
    if(count == 0)
        temp = len;
    return count;
}
 
ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp) {
   if (copy_from_user(msg, buf, count)) {
        return -EFAULT;
    }
    len = count;
    temp = len;
    return count;
}
 
static const struct proc_ops proc_fops = {
    proc_read: read_proc,
    proc_write: write_proc,
};
 
void create_new_proc_entry(void) { 
    proc_create("funny_box", PROC_MODE, NULL, &proc_fops);
    msg = kmalloc(SIZE * sizeof(char), GFP_KERNEL);
}
 
int proc_init (void) {
    create_new_proc_entry();
    return 0;
}
 
void proc_cleanup(void) {
    remove_proc_entry("funny_box", NULL);
    kfree(msg);
}
 
MODULE_LICENSE("Alina");
MODULE_AUTHOR("Tereshkina");
module_init(proc_init);
module_exit(proc_cleanup);
