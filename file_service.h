#ifndef FILE_SERVICE_H_
#define FILE_SERVICE_H_

#include <stdint.h>
#include <stdio.h>
#include <string>

std::string get_dir_path( std::string file_path );
std::string get_file_name( std::string file_path );
uint32_t file_load( const char *file_name, void *data, uint32_t data_nbytes );
std::string file_load( const char *file_name );
bool file_save( const char *file_name, const void *data, uint32_t data_nbytes );
uint32_t get_file_nbytes( const char* file_name );

#endif /* FILE_SERVICE_H_ */
