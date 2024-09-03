#include "Serializer.h"

using namespace std;


string Serializer::getData()
{
	string data;
	data.append( namedToData() );
	data.append( nonamed );
	return data;
}

void Serializer::save( const string &str )
{
	saveStringBlock( nonamed, str );
}

void Serializer::save( const void *data, uint64_t nbytes )
{
	const uint8_t* dataBytes = reinterpret_cast<const uint8_t*>( data );
	saveArrayBlock<uint8_t>( nonamed, dataBytes, nbytes );
}

void Serializer::save( const string &name, const void *data, uint64_t nbytes )
{
	named[ name ] = toString( data, nbytes );
}

void Serializer::saveStringBlock( string &dst, const string &block )
{
	string nbytesStr = toString<uint64_t>( block.size() );
	dst.append( nbytesStr );
	dst.append( block );
}

string Serializer::namedToData()
{
	string namedSaved;

	uint64_t nameNumber = named.size();
	saveBlock<uint64_t>( namedSaved, nameNumber );

	for( auto it = named.begin(); it != named.end(); ++it ){
		saveStringBlock( namedSaved, it->first );
		saveStringBlock( namedSaved, it->second );
	}

	return namedSaved;
}

string Serializer::toString( const void *obj, uint64_t nbytes )
{
	return string( reinterpret_cast<const char*>( obj ), nbytes );
}

