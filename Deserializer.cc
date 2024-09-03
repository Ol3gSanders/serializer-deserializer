#include <string.h>

#include "Deserializer.h"

using namespace std;


Deserializer::Deserializer( const string &data ) : Deserializer()
{
	setData( data );
}

void Deserializer::setData( const string &data )
{
	pos = 0;
	uint64_t nameNumber = loadBlock<uint64_t>( data );

	for( uint64_t i = 0; i < nameNumber; ++i ){
		string name = loadStringBlock( data );
		string namedData = loadStringBlock( data );
		if( name.size() ){
			named[ name ] = namedData;
		}
	}

	nonamed = move( data.substr( pos ) );
	size_t namedDataNbytes = data.size() - nonamed.size();
	namedData = move( data.substr( 0, namedDataNbytes ) );
	pos = 0;
}

string Deserializer::getNotLoaded()
{
	return namedData + nonamed.substr( pos );
}

string Deserializer::load()
{
	return loadStringBlock( nonamed );
}

void Deserializer::load( string &dst )
{
	dst = move( loadStringBlock( nonamed ) );
}

void Deserializer::load( void *dst, uint64_t nbytes )
{
	string src = loadStringBlock( nonamed );
	if( src.size() ==  nbytes ){
		memcpy( dst, src.data(), nbytes );
	}
	else{
		err = true;
	}
}

void Deserializer::load( void *dst, const string &name, uint64_t nbytes )
{
	bool hasName = named.count( name ) > 0;
	if( hasName ){
		bool nbytesMatch = named[ name ].size() == nbytes;
		if( nbytesMatch ){
			const char* srcData = named[ name ].data();
			memcpy( dst, srcData, nbytes );
		}
		else{
			err = true;
		}
	}
}

bool Deserializer::getErr() const
{
	return err;
}

void Deserializer::resetErr()
{
	err = false;
}

string Deserializer::loadStringBlock( const string &src )
{
	string s;
	if( src.size() >= pos + sizeof( uint64_t ) ){
		uint64_t nbytes = fromString<uint64_t>( src );
		if( src.size() >= pos + nbytes ){
			s = move( src.substr( pos, nbytes ) );
			pos += nbytes;
		}
		else{
			err = true;
		}
	}
	else{
		err = true;
	}
	return move( s );
}
