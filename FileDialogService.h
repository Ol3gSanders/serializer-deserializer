#ifndef FILEDIALOGSERVICE_H
#define FILEDIALOGSERVICE_H

#include <string>
#include "Data.h"
using std::string;


class FileDialogService
{
public:
	FileDialogService();

	bool loadDialog( Data &dataBuf );
	std::string loadDialog( );
	bool saveDialog( std::string _data );
	std::string saveDialog( );

	void deserialize( const string &src );
	string serialize();

private:
	void load( const string &src );
	string save();

private:
	typedef struct data_s{
		std::string loadFilePath;
		std::string saveFilePath;
		data_s() :  loadFilePath( "./" ),  saveFilePath( "./" ) {}
	}data_t;
	data_t data;
Data fileData;

};

#endif // FILEDIALOGSERVICE_H
