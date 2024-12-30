#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("ERIC MWANGI"); 
MODULE_DESCRIPTION("My first dynamically loadable kernel module"); 

static struct proc_dir_entry * custom_proc_node; 

static ssize_t eric_driver_read(struct file * file_pointer,
                        char *user, 
                        size_t count, 
                        loff_t * offset)
{
    printk("Eric Driver read function \n"); 


    char msg[] = "ACK!! Honors Champ \n"; 
    size_t len = strlen(msg); 

     if(*offset >= len)
        return 0; 


    int result; 

    result = copy_to_user(user, msg, len); 

    // if(!result){
    //     return -1; 
    // }
    *offset += len; 

   
    return len;
}

struct proc_ops driver_proc_ops = {
    .proc_read = eric_driver_read
}; 

static int eric_module_init(void)
{
    printk("Hello, World from Eric inside the module: entry\n");

    custom_proc_node = proc_create("Eric_Driver", 
                                    0, 
                                    0, 
                                    &driver_proc_ops); 
    
    printk("Eric module init exit \n"); 
    return 0;
} 



static void eric_module_exit(void)
{
    printk("Good, bye! from nush in the kernel: Entry "); 
    proc_remove(custom_proc_node);


    printk("Good bye module: Exit \n");    
    
}

module_init(eric_module_init); 
module_exit(eric_module_exit); 