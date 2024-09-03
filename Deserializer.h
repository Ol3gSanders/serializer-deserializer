#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <map>
#include <cstring>
#include <string>
#include <vector>


class Deserializer
{
public:
	Deserializer() { err = false; }
	Deserializer( const std::string &data );
	void setData( const std::string &data );
	std::string getNotLoaded();
	std::string load();
	void load( std::string &dst );
	void load( void *dst, uint64_t nbytes );
	void load( void *dst, const std::string &name, uint64_t nbytes );

	template <typename T>
	void load( T &dst )
	{
		T tmp = loadBlock<T>( nonamed );
		memcpy( &dst, &tmp, sizeof(T) );
	}

	template <typename T>
	T load()
	{
		return loadBlock<T>( nonamed );
	}

	template <typename T>
	std::vector<T> loadArray()
	{
		return loadArrayBlock<T>( nonamed );
	}

	template <typename T>
	std::vector<T> loadArray( const std::string &name )
	{
		std::vector<T> array;
		if( named.count( name ) > 0 ){
			array = loadArrayBlock<T>( named[name] );
		}

		return array;
	}

	bool getErr() const;
	void resetErr();

protected:
	std::string loadStringBlock( const std::string &src );

	template <typename T>
	T loadBlock( const std::string &src )
	{
		uint64_t nbytes = 0;
		if( src.size() >= pos + sizeof(uint64_t) ){
			nbytes = fromString<uint64_t>( src );
		}

		T data;
		if( nbytes == sizeof(T) && src.size() >= pos + nbytes ){
			memcpy( &data, src.data() + pos, nbytes );
			pos += nbytes;
		}
		else{
			err = true;
			std::memset( &data, 0, sizeof(T) );
		}

		return data;
	}

	template <typename T>
	std::vector<T> loadArrayBlock( const std::string &src )
	{
		uint64_t nbytes = 0;
		if( src.size() >= pos + sizeof(uint64_t) ){
			nbytes = fromString<uint64_t>( src );
		}

		std::vector<T> array;
		if( src.size() >= pos + nbytes && nbytes % sizeof(T) == 0 ){
			uint64_t num = nbytes / sizeof(T);
			const T* dataBegin = reinterpret_cast<const T*>( src.data() + pos );
			array.assign( dataBegin, dataBegin + num );
			pos += nbytes;
		}

		return std::move( array );
	}

	template <typename T>
	T fromString( const std::string &src )
	{
		T data;
		memcpy( &data, src.data() + pos, sizeof(T) );
		pos += sizeof(T);
		return data;
	}

	std::string nonamed;
	std::string namedData;
	size_t pos;
	std::map<std::string, std::string> named; // name to data
	bool err;
};

#endif // DESERIALIZER_H
