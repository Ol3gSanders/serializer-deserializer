#include "MainWindow.h"
#include "file_service.h"

MainWindow::MainWindow( QWidget *parent )
	: QMainWindow( parent )
{
	createWidgets();
	placeWidgets();
	connectSignals();
	loadFile();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createWidgets()
{
	serDeserWgt = new SerDeserWgt();
	textInfo = new QPlainTextEdit();
	textInfo->setFixedSize( 200, 100 );
	textInfo->setReadOnly( true );
	textInfo->setPlaceholderText( "Нажмите кнопку \"Вывести значения\" " );

	exitButton = new QPushButton( "Выход" );
	printButton = new QPushButton( "Вывести значения" );
	saveButton = new QPushButton( "Сохранить" );
	loadButton = new QPushButton( "Загрузить" );
}

void MainWindow::placeWidgets()
{
	auto *mainGB = new QGroupBox( "MainWindow" );
	auto *mainLay = new QGridLayout();
	mainGB->setLayout( mainLay );

	mainLay->addWidget( serDeserWgt, 0, 0 );
	mainLay->addWidget( textInfo, 0, 1 );
	mainLay->addWidget( saveButton, 1, 0 );
	mainLay->addWidget( loadButton, 2, 0 );
	mainLay->addWidget( printButton, 1, 1 );
	mainLay->addWidget( exitButton, 2, 1 );

	setCentralWidget( mainGB );
}

void MainWindow::connectSignals()
{
	connect( printButton, SIGNAL(clicked()), this, SLOT(onPrintButtonClicked()) );
	connect( exitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()) );
	connect( saveButton, SIGNAL(clicked()), this, SLOT(onSaveButtonClicked()) );
	connect( loadButton, SIGNAL(clicked()), this, SLOT(onLoadButtonClicked()) );
}

void MainWindow::saveFile()
{
	std::string data = serDeserWgt->serialize();
	file_save( this->filePath.c_str(), data.c_str(), data.size() );
}


void MainWindow::loadFile()
{
	std::string str = file_load( this->filePath.c_str() );
	if( str.size() ){
		serDeserWgt->deserialize( str );
	}
}

void MainWindow::onPrintButtonClicked()
{
	std::string infoStr = serDeserWgt->toStr();
	textInfo->setPlainText( infoStr.c_str() );
}

void MainWindow::onExitButtonClicked()
{
	saveFile();
	close();
}

void MainWindow::onSaveButtonClicked()
{
	std::string str = serDeserWgt->serialize();

	string filePath = fileDialogService.saveDialog();
	if( !filePath.empty() ){
		file_save( filePath.c_str(), str.c_str(), str.size() );
	}
}

void MainWindow::onLoadButtonClicked()
{
	string filePath = fileDialogService.loadDialog();

	string str = file_load( filePath.c_str() );
	if( str.size() ){
		serDeserWgt->deserialize( str );
	}
}

void MainWindow::closeEvent( QCloseEvent *event )
{
	saveFile();
}

