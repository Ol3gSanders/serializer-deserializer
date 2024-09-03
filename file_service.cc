#include <fstream>

#include "file_service.h"

using std::string;



string get_dir_path( string file_path )
{
	string dir_path = ".";
	if( file_path.compare( "./" ) ){
		unsigned found_pos = file_path.find_last_of( "/" );
		if( found_pos != string::npos ){
			dir_path = file_path.substr( 0, found_pos + 1 );
		}
	}

	return dir_path;
}

string get_file_name( string file_path )
{
	string file_name = "xxx";
	if( file_path.compare( "./" ) ){
		unsigned found_pos = file_path.find_last_of( "/" );
		if( found_pos != string::npos ){
			file_name = file_path.substr( found_pos + 1, file_path.size() );
		}
	}

	return file_name;
}

uint32_t file_load( const char *file_name, void *data, uint32_t data_nbytes )
{
	uint32_t file_nbytes = get_file_nbytes( file_name );
	if( file_nbytes >= data_nbytes ){
		file_nbytes = data_nbytes;
	}
	if( file_nbytes != 0 ){
		FILE *fptr = fopen( file_name, "rb" );
		fread( data, file_nbytes, 1, fptr );
		fclose( fptr );
	}

	return file_nbytes;
}

string file_load( const char *file_name )
{
	std::ifstream in( file_name, std::ios::in | std::ios::binary );
	string data;
	if( in ){
		in.seekg( 0, std::ios::end );
		data.resize( in.tellg() );
		in.seekg( 0, std::ios::beg );
		in.read( &data[0], data.size() );
		in.close();
	}
	return data;
}

bool file_save( const char *file_name, const void *data, uint32_t data_nbytes )
{
	bool file_saved = false;
	FILE *fptr = fopen( file_name, "wb" );
	if( fptr != 0 ){
		fwrite( data, data_nbytes, 1, fptr );
		fclose( fptr );
		file_saved = true;
	}

	return file_saved;
}

uint32_t get_file_nbytes( const char* file_name )
{
	uint32_t file_nbytes = 0;
	FILE *fptr = fopen( file_name, "rb" );
	if( fptr ){
		fseek( fptr, 0, SEEK_END );
		file_nbytes = ftell( fptr );
		fclose( fptr );
	}

	return file_nbytes;
}
