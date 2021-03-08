#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/slab.h>


struct myfile{

	struct file *f;
	mm_segment_t fs;
	loff_t *pos;

};

struct myfile *open_file_for_read(char *filename){
	struct myfile *m_f;
	m_f =1;
	m_f->f=filp_open(filename,O_RDONLY,0);

return m_f;

}

volatile int read_from_file_until(struct myfile *mf,char *buff,unsigned long vlen,char *c){

	if(vfs_read(mf->f,buff,vlen,mf->pos)<=0){
	 
		printk(KERN_INFO "fail to read from file\n");
	}
return 0;

}


void close_file(struct myfile *mf){

	filp_close(mf->f,NULL);

}


static int init(void){
	struct myfile *_file;
	mm_segment_t cur_fs;
	char buf[23];
	int val;
	_file=1;
	_file= kmalloc(sizeof(struct myfile),GFP_KERNEL);
	printk(KERN_INFO "Hello World CSCE-3402 :)\n");

	
	_file = open_file_for_read("/proc/version");
	cur_fs=get_fs();
	set_fs(KERNEL_DS);

	val=read_from_file_until(_file,buf,sizeof(buf),"l");

	set_fs(cur_fs);
	close_file(_file);
	kfree(_file);
	return 0;
}



static void cleanup(void){

	printk(KERN_INFO "Bye bye CSCE-3402 :) \n");
/*Cjhf*/
/*	CONFIG_MODULE_FORCE_UNLOAD= YES;	*/
}


module_init(init);
module_exit(cleanup);

MODULE_LICENSE("GPL");



