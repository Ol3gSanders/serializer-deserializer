#include "SerDeserWgt.h"
#include "Serializer.h"
#include "Deserializer.h"

#include <sstream>

SerDeserWgt::SerDeserWgt()
{
	this->setTitle( "SerDeserWgt" );
	createWidgets();
	placeWidgets();
	connectSignals();
	init();
}

std::string SerDeserWgt::toStr()
{
	data = widgetsToData();

	std::stringstream ss;

	ss << "параметр x: "<< data.x << "\n";
	ss << "параметр y: "<< data.y << "\n";
	ss << "параметр text: "<< data.text.c_str() << "\n";

	return ss.str();
}

void SerDeserWgt::init()
{
	xSpinBox->setValue( data.x );
	ySpinBox->setValue( data.y );
	textLineEdit->setText( data.text.c_str() );
}


std::string SerDeserWgt::serialize()
{
	data = widgetsToData();

	Serializer ser;
	ser.save( data.x );
	ser.save( data.y );
	ser.save( data.text );

	std::string savedData = ser.getData();
	return savedData;
}

void SerDeserWgt::deserialize( const std::string &str )
{
	Deserializer deser( str );
	data.x = deser.load<int>();
	data.y = deser.load<double>();
	data.text = deser.load();

	dataToWidgets( data );
}

void SerDeserWgt::createWidgets()
{
	xLabel = new QLabel( "x" );
	yLabel = new QLabel( "y" );
	textLabel = new QLabel( "text" );

	xSpinBox = new QSpinBox();
	ySpinBox = new QDoubleSpinBox();
	textLineEdit = new QLineEdit();
}

void SerDeserWgt::placeWidgets()
{
	auto *mainLay = new QGridLayout();

	mainLay->addWidget( xSpinBox, 0, 0 );
	mainLay->addWidget( xLabel, 0, 2 );
	mainLay->addWidget( ySpinBox, 1, 0 );
	mainLay->addWidget( yLabel, 1, 2 );
	mainLay->addWidget( textLineEdit, 2, 0 );
	mainLay->addWidget( textLabel, 2, 2 );

	this->setLayout( mainLay );
}

void SerDeserWgt::connectSignals()
{
	connect( xSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()) );
	connect( ySpinBox, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()) );
	connect( textLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onValueChanged()) );
}

data_t SerDeserWgt::widgetsToData()
{
	data.x = xSpinBox->value();
	data.y = ySpinBox->value();
	data.text = textLineEdit->text().toStdString();

	return data;
}

void SerDeserWgt::dataToWidgets( data_t data )
{
	xSpinBox->setValue( data.x );
	ySpinBox->setValue( data.y );
	textLineEdit->setText( data.text.c_str() );
}

void SerDeserWgt::onValueChanged()
{
	widgetsToData();
}
