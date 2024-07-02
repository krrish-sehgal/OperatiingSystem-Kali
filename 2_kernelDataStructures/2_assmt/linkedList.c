#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

// This macro defines and initializes the variable birthday_list which is of type list_head and will be used to identify the entire list
static LIST_HEAD(birthday_list);

// Called when the module is loaded
int simple_init(void) {
    printk(KERN_INFO "Loading Module\n");

    // Initialize instances of birthday
    struct birthday *person1, *person2, *person3;

    // Allocate memory for each person
    person1 = kmalloc(sizeof(struct birthday), GFP_KERNEL);
    person2 = kmalloc(sizeof(struct birthday), GFP_KERNEL);
    person3 = kmalloc(sizeof(struct birthday), GFP_KERNEL);

    if (!person1 || !person2 || !person3) {
        printk(KERN_ALERT "Memory allocation failed\n");
        return -ENOMEM;
    }

    // Assign values to each person
    person1->day = 4;
    person1->month = 10;
    person1->year = 2005;
    // Initializing list_head ensures that the internal pointers (next and prev) within the structure are properly set to NULL or to themselves, depending on the implementation.
    INIT_LIST_HEAD(&person1->list); // Initialize list head for person1

    person2->day = 5;
    person2->month = 10;
    person2->year = 2005;
    INIT_LIST_HEAD(&person2->list); // Initialize list head for person2

    person3->day = 6;
    person3->month = 10;
    person3->year = 2005;
    INIT_LIST_HEAD(&person3->list); // Initialize list head for person3

    // Link the nodes together
    // Nodes are linked based on the list_add_tail function calls, which adds each new node to the end (tail) of the list specified by &birthday_list. This ensures that the nodes are linked in the order they are added to the list.
    list_add_tail(&person1->list, &birthday_list);
    list_add_tail(&person2->list, &birthday_list);
    list_add_tail(&person3->list, &birthday_list);

    // Traverse the linked list and print each node
    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) {
        printk(KERN_INFO "Day: %d\n", ptr->day);
    }

    return 0;
}

// Called when the module is removed
void simple_exit(void) {
    struct birthday *ptr, *next;
    
    printk(KERN_INFO "Removing Module\n");

    // Traverse the list and free each node
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        list_del(&ptr->list); // Remove from the list
        kfree(ptr); // Free memory allocated for the node
    }
}

// Modules for registering module entry and exit points
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
