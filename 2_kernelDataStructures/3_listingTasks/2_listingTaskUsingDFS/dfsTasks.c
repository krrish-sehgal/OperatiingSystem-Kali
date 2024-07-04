#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple example to list all processes using DFS");
MODULE_VERSION("0.1");

static int __init list_tasks_init(void);
static void __exit list_tasks_exit(void);
static void dfs(struct task_struct *task);

static int __init list_tasks_init(void) {
    printk(KERN_INFO "Loading list_tasks module...\n");

    dfs(&init_task); // Start DFS traversal from init_task

    return 0;
}

static void dfs(struct task_struct *task) {
    struct task_struct *childTask;
    struct list_head *list;

    printk(KERN_INFO "PID: %d \n",task->pid);

    // Traverse child processes
    list_for_each(list, &task->children) {
        childTask = list_entry(list, struct task_struct, sibling);
        dfs(childTask); // Recursively traverse child processes
    }
}

static void __exit list_tasks_exit(void) {
    printk(KERN_INFO "Unloading list_tasks module...\n");
}

module_init(list_tasks_init);
module_exit(list_tasks_exit);
