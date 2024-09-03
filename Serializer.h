#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <map>
#include <string>
#include <vector>


class Serializer
{
public:
	std::string getData();

	void save( const std::string &str );
	void save( const void *data, uint64_t nbytes );
	void save( const std::string &name, const void *data, uint64_t nbytes );


	template <typename T>
	void save( const T &t )
	{
		saveBlock<T>( nonamed, t );
	}

	template <typename T>
	void save( const std::string &name, const T &t )
	{
		named[ name ] = toString<T>( t );
	}

	template <typename T>
	void save( const std::vector<T> &array )
	{
		saveArrayBlock<T>( nonamed, array.data(), array.size() );
	}

	template <typename T>
	void save( const std::string &name, const std::vector<T> &array )
	{
		uint64_t nbytes = array.size() * sizeof(T);
		named[ name ] = toString( array.data(), nbytes );
	}


protected:
	void saveStringBlock( std::string &dst, const std::string &block );
	std::string namedToData();
	std::string toString( const void *obj, uint64_t nbytes );


	template <typename T>
	void saveBlock( std::string &dst, const T &t )
	{
		const uint64_t num = 1;
		saveArrayBlock<T>( dst, &t, num );
	}

	template <typename T>
	void saveArrayBlock( std::string &dst, const T *array, uint64_t num )
	{
		uint64_t nbytes = num * sizeof(T);
		std::string nbytesStr = toString<uint64_t>( nbytes );
		dst.append( nbytesStr );
		std::string blockDataStr( toString( array, nbytes ) );
		dst.append( blockDataStr );
	}

	template <typename T>
	std::string toString( const T &t )
	{
		return std::string( reinterpret_cast<const char*>( &t ), sizeof( T ) );
	}


	std::string nonamed;
	std::map<std::string, std::string> named; // name to data
};


#endif // SERIALIZER_H
