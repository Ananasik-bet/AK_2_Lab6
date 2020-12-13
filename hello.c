#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/ktime.h>


struct personal_list_head {
struct personal_list_head *next;
ktime_t time;
};

MODULE_AUTHOR("Vlad Diachenko <vlad.diachenko@ukr.net>");
MODULE_DESCRIPTION("Hello world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static struct personal_list_head *header;

static uint countOfRepeats = 1;
module_param(countOfRepeats,uint,S_IRUGO);
MODULE_PARM_DESC(countOfRepeats, "How many times to print hello world");

static int __init initter(void)
{
  uint i = 0;
  struct personal_list_head *first_variable, *second_variable;

  printk(KERN_INFO "countOfRepeats: %d\n", countOfRepeats);

  if(countOfRepeats == 0) {
    printk(KERN_WARNING "Warning: repeats number is 0");
  }else if(countOfRepeats >=5 && countOfRepeats <= 10) {
    printk(KERN_WARNING "Warning: repeats number is between 5 and 10");
  } else if(countOfRepeats > 10) {
    printk(KERN_ERR "Error: repeats number is greater than 10");
    return -EINVAL;
  }

  header = kmalloc(sizeof(struct personal_list_head *), GFP_KERNEL);
  first_variable = header;
  
  for(i = 0; i < countOfRepeats; i++){
  first_variable->next = kmalloc(sizeof(struct personal_list_head), GFP_KERNEL);
    first_variable->time = ktime_get();
    pr_info("Hello world!");
    second_variable = first_variable;
    first_variable = first_variable->next;
    }
    if (countOfRepeats != 0) {
      kfree(second_variable->next);
      second_variable->next = NULL;

  }
  printk(KERN_INFO "countOfRepeats: %d\n", countOfRepeats);
  return 0;
}

static void __exit exitter(void)
{
  struct personal_list_head *variable;
  while (header != NULL && countOfRepeats != 0) {
    variable = header;
    pr_info("Time : %lld", variable->time);
    header = variable->next;
    kfree(variable);
  }
  if (countOfRepeats == 0) {
    pr_info("Time 0 because no printing was used");
  }
  pr_info("");
}

module_init(initter);
module_exit(exitter);
