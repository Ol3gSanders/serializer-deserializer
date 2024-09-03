#include <iostream>
#include <string.h>
#include <stdint.h>

#include "Data.h"

Data::Data( )
{
	data.reset();
}

Data::Data( uint32_t data_nbytes )
{
	set_data( nullptr, data_nbytes );
	memset( this->data.get(), 0, this->data_nbytes );
}

Data::Data( const void *data, size_t data_nbytes )
{
	set_data( data, data_nbytes );
}

const Data& Data::operator=( const Data &data )
{
	set_data( data.data.get(), data.data_nbytes );
	return *this;
}


const Data& Data::operator=( Data &&data )
{
	this->data_nbytes = data.data_nbytes;
	this->data = std::move( data.data );
	data.data_nbytes = 0;

	return *this;
}

Data::Data( Data &&data )
{
	this->data_nbytes = data.data_nbytes;
	this->data = std::move(data.data);
	data.data_nbytes = 0;
}

Data::Data( const Data &data )
{
	clear();
	set_data( data.data.get(), data.data_nbytes );
}

Data::~Data( )
{
	data_nbytes = 0;
}

void Data::clear( )
{
	data.reset();
	data_nbytes = 0;
}

void Data::set_data( const std::string &data )
{
	set_data( data.c_str(), data.size() );
}

void Data::set_data( const void *data, size_t data_nbytes )
{
	if( data_nbytes ){
		this->data = std::unique_ptr<uint8_t[]>( new uint8_t[data_nbytes] );
		if( this->data ){
			this->data_nbytes = data_nbytes;
			if( data ){
				memcpy( this->data.get(), data, data_nbytes );
			}
		}
	}
}

void Data::add_data( const Data &data )
{
	add_data( data.get_data(), data.get_data_nbytes() );
}

void Data::add_data( const void *data, size_t data_nbytes )
{
	if( data_nbytes ){
		size_t new_data_nbytes = this->data_nbytes + data_nbytes;
		uint8_t *new_data = new uint8_t[new_data_nbytes];
		if( this->data_nbytes ){
			memcpy( new_data, this->data.get(), this->data_nbytes );
		}
		memcpy( new_data + this->data_nbytes, data, data_nbytes );
		this->data.reset( new_data );
		this->data_nbytes = new_data_nbytes;
	}
}

uint8_t* Data::get_data( )
{
	return data.get();
}

uint8_t* Data::get_data( ) const
{
	return data.get();
}

uint32_t Data::get_data_nbytes( )
{
	return data_nbytes;
}

uint32_t Data::get_data_nbytes( ) const
{
	return data_nbytes;
}

std::string Data::serialize()
{
	return std::string( ( reinterpret_cast<char*>( this->data.get() ) ), data_nbytes );
}

void Data::deserialize( const std::string &data )
{
	set_data( data.data(), data.size() );
}
