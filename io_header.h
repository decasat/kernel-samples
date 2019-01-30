#ifndef    _IO_HEADER_H_
#define _IO_HEADER_H_

#include <asm/ioctl.h>

#define magic    'A'

#define    set_gpio_pin        _IOW(magic,1,uint)

#define set_gpio_dir_out    _IOW(magic,2,uint)

#define set_gpio_dir_in        _IOW(magic,3,uint)

#define set_gpio_value        _IOW(magic,4,uint)

#define get_gpio_value        _IOW(magic,5,uint)

#define set_gpio_unexport    _IOW(magic,6,uint)

#define set_gpio_free        _IOW(magic,7,uint)

#define get_gpio_in        _IOR(magic,8,bool)

#define max_cmd            8

#endif

