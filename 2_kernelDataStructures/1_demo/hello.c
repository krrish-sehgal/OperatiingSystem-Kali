#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list; // this list_head is defined in types.h file
};

// This macro defines and initialises the variballe birthday_list which is of type list_head
static LIST_HEAD(birthday_list);

// caleed when the module is loaded
int simple_init(void) {
    printk(KERN_INFO "Loading Module \n");



    //initialising an instance of birthday: 
    struct birthday *person;

    //The kmalloc is kernel equivalent of user malloc, except that kernel memory is being allocated
    person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
    // The gfp kernel flag indiactes routine kernel memory allocation.

    person->day = 4;
    person->month = 10;
    person->year = 2005;

    //This macro initializes the list member in struct birthday. 
    INIT_LIST_HEAD(&person->list);

    // we can then add this instance to the end of the linked list: 
    list_add_tail(&person->list , &birthday_list);

    //TRAVERSING THE LINKED LIST
    // involves using the macro which accepts 3 params
    struct birthday *ptr;
    //pointer to iterate over the struct, pointer to the head of the list , name of the variable containing list_head 
    list_for_each_entry(ptr, &birthday_list, list) {
        // on each interation pointer ptr points to the next birthday struct
        printk(KERN_INFO "Day: %d\n", ptr->day);
    }

    return 0;
}

//Called when the module is removed
void simple_exit(void) {
    struct birthday *ptr, *next;
    
    printk(KERN_INFO "Removing Module\n");

    // Traverse the list and free each node
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        list_del(&ptr->list); // Remove from the list
        kfree(ptr); // Free memory allocated for the node
    }
}

//Modules for registering module entry and exit points
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
