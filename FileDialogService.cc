#include "FileDialogService.h"
#include  <QString>
#include  <QFileInfo>
#include  <QFileDialog>
#include "qt_macros.h"
#include "Deserializer.h"
#include "Serializer.h"
#include "file_service.h"


FileDialogService::FileDialogService()
{

}

bool FileDialogService::saveDialog( string _data )
{
	bool isFileSaved = false;
	string path = saveDialog();

	if( path.size() ){
		 isFileSaved = file_save( data.saveFilePath.c_str(), _data.c_str(), _data.size() );
	}

	return isFileSaved;
}

std::string FileDialogService::saveDialog()
{
	QString path( data.saveFilePath.c_str() );
	QString absolutePath = "";
	if( path.size() ){
		QFileInfo fileInfo( path );
		absolutePath = fileInfo.absolutePath();
	}

	path = QFileDialog::getSaveFileName( nullptr, UCS("Сохранить файл"), absolutePath);
	if( path.size() ){
		data.saveFilePath = path.toStdString();;
	}

	return path.toStdString();
}

bool FileDialogService::loadDialog( Data &dataBuf )
{
	bool isLoad = false;
	string path = loadDialog();
	if( path.size() ){
		unsigned fileNbytes = get_file_nbytes( data.loadFilePath.c_str() );
		Data fileData( fileNbytes );
		fileNbytes = file_load( data.loadFilePath.c_str(), fileData.get_data(), fileNbytes );
		if( fileNbytes != 0 ){
			isLoad = true;
			dataBuf = fileData;
		}
	}

	return isLoad;
}

std::string FileDialogService::loadDialog()
{
	QString path( data.loadFilePath.c_str() );
	QString absolutePath = "";
	if( path.size() ){
		QFileInfo fileInfo( path );
		absolutePath = fileInfo.absolutePath();
	}

	path = QFileDialog::getOpenFileName( nullptr, UCS("Открыть файл"), absolutePath );
	if( path.size() ){
		data.loadFilePath = path.toStdString();;
	}

	return  path.toStdString();
}


void FileDialogService::deserialize( const std::string &src )
{
	load( src );
}

std::string FileDialogService::serialize()
{
		string savedData = save();

		return savedData;
}

void FileDialogService::load(const std::string &src)
{
	Deserializer deser( src );
	data.loadFilePath = deser.load();
	data.saveFilePath = deser.load();
}

std::string FileDialogService::save()
{
	Serializer ser;
	ser.save( data.loadFilePath );
	ser.save( data.saveFilePath);

	return ser.getData();
}

