#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple example to list all processes");
MODULE_VERSION("0.1");

static int __init list_tasks_init(void);
static void __exit list_tasks_exit(void);

static int __init list_tasks_init(void) {
    struct task_struct *task;

    printk(KERN_INFO "Loading list_tasks module...\n");

    for_each_process(task) {
        printk(KERN_INFO "Process: %s\tPID: %d\n", task->comm, task->pid);
    }

    return 0;
}

static void __exit list_tasks_exit(void) {
    printk(KERN_INFO "Unloading list_tasks module...\n");
}

module_init(list_tasks_init);
module_exit(list_tasks_exit);
