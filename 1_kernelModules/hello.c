//Example of creating a linux module

#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>


//caleed when the module is loaded
int simple_init(void){
    
    printk(KERN_INFO "Loading Module \n");
    return 0;
}

//Called when the module is removed
void simple_exit(void){
    printk(KERN_INFO "Removing Module\n");
}

//Modules for registering module entry and exit points
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


