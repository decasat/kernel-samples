/********************************************************************\
 *      Filename: showmm.c
 *
 *	Description 	: Show memory details of process	
 *     Author		: Sateesh Kumar G <skg@decanetsystems.com>
 *     date begun	: 17 JUL 2017
\********************************************************************/

#include <linux/module.h>	// for init_module()
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/mm.h>

char modname[] = "showmm";


char buf[1024];

int get_mm_info(void)
{
	struct task_struct *tsk = current;
	struct mm_struct *mm = tsk->mm;
	unsigned long stack_size = (mm->stack_vm << PAGE_SHIFT);
	unsigned long down_to = mm->start_stack - stack_size;
	int len;

	len = sprintf(buf, "\nInfo from the Memory Management structure ");
	len += sprintf(buf + len, "for task \'%s\' ", tsk->comm);
	len += sprintf(buf + len, "(pid=%d) \n", tsk->pid);
	len +=
	    sprintf(buf + len, "   pgd=%08lX  ", (unsigned long) mm->pgd);
	len +=
	    sprintf(buf + len, "mmap=%08lX  ", (unsigned long) mm->mmap);
	len += sprintf(buf + len, "map_count=%d  ", mm->map_count);
	len += sprintf(buf + len, "mm_users=%d  ", mm->mm_users.counter);
	len += sprintf(buf + len, "mm_count=%d  ", mm->mm_count.counter);
	len += sprintf(buf + len, "\n");
	len +=
	    sprintf(buf + len, "    start_code=%08lX  ", mm->start_code);
	len += sprintf(buf + len, " end_code=%08lX\n", mm->end_code);
	len +=
	    sprintf(buf + len, "    start_data=%08lX  ", mm->start_data);
	len += sprintf(buf + len, " end_data=%08lX\n", mm->end_data);
	len += sprintf(buf + len, "     start_brk=%08lX  ", mm->start_brk);
	len += sprintf(buf + len, "      brk=%08lX\n", mm->brk);
	len += sprintf(buf + len, "     arg_start=%08lX  ", mm->arg_start);
	len += sprintf(buf + len, "  arg_end=%08lX\n", mm->arg_end);
	len += sprintf(buf + len, "     env_start=%08lX  ", mm->env_start);
	len += sprintf(buf + len, "  env_end=%08lX\n", mm->env_end);
	len +=
	    sprintf(buf + len, "   start_stack=%08lX  ", mm->start_stack);
	len += sprintf(buf + len, "  down_to=%08lX ", down_to);
	len += sprintf(buf + len, " <--- stack grows downward \n");
	len += sprintf(buf + len, "\n");

	printk("%s\n", buf);
	return len;


}


static int __init my_init(void)
{
	pr_info("Installing \'%s\' module\n", modname);

	//shows some info from a task's memory-management structure
	get_mm_info();  // show mm_struct 

	return 0;		// SUCCESS
}


static void __exit my_exit(void)
{
	pr_info("Removing \'%s\' module\n", modname);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SATEESH KG <skg@decanetsystems.com>");
MODULE_DESCRIPTION("Details:");
