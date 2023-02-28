#ifndef __MJPEG_H
#define __MJPEG_H 
#include "stdio.h" 
#include <cdjpeg.h> 
#include <system.h> 
#include <setjmp.h>



struct my_error_mgr {
  struct jpeg_error_mgr pub;	
  jmp_buf setjmp_buffer;		//for return to caller 
}; 
typedef struct my_error_mgr * my_error_ptr;

u8 mjpegdec_init(u16 offx,u16 offy);
void mjpegdec_free(void);
u8 mjpegdec_decode(u8* buf,u32 bsize);

#endif

