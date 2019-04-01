#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

#include "proj2_call.h"

#define BUFFER 16

asmlinkage long sys_proj2_call(struct proj2_process_info *arr, uid_t userID)
{
	struct task_struct * task;
	int _i;
	uid_t uID;
	char temp[BUFFER];
	int _j;
	int _k;

	_i = 0;

	for_each_process(task) {
		if(task->cred->uid.val == userID)
		{
			copy_to_user(&((arr + _i)->PID),&(task->pid),sizeof(task->pid));


			for(_k = 0; _k < sizeof(temp); _k++)
			{
				temp[_k] = (char)NULL;
			}
			for(_j = 0; _j < sizeof(task->comm) && task->comm[_j] != '\0'; _j++)
			{
				temp[_j] = task->comm[_j];
			}

			copy_to_user(&((arr + _i)->name),&temp,sizeof(temp));

			copy_to_user(&((arr + _i)->priority),&(task->prio),sizeof(task->prio));

			copy_to_user(&((arr + _i)->schedulerClass),&(task->policy),sizeof(task->policy));

			_i = _i + 1;
		}
	}

	return 0;
	
}
