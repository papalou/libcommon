#ifndef __CRC_H__
#define __CRC_H__

//Needed to use this header file with C++ source code
#ifdef __cplusplus
	#warning "Lib used in C++"
	extern "C" {
#endif

uint8_t crc_compute_crc8(void * message, uint32_t length);

#ifdef __cplusplus
}
#endif
