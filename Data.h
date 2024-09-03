#ifndef DATA_H_
#define DATA_H_

#include <inttypes.h>
#include <memory>

class Data {
	public:
		Data( );
		Data( uint32_t data_nbytes );
		Data( const void *data, size_t data_nbytes );
		const Data& operator=( const Data &data );
		const Data& operator=( Data &&data );
		Data( const Data& data );
		Data( Data &&data );
		~Data( );
		operator Data*() { return this; }
		Data* operator->() { return this; }

		void clear();
		void set_data( const std::string &data );
		void set_data( const void *data, size_t data_nbytes );
		void add_data( const Data &data );
		void add_data( const void *data, size_t data_nbytes );

		uint8_t* get_data( );
		uint8_t* get_data( ) const;
		uint32_t get_data_nbytes();
		uint32_t get_data_nbytes() const;

		std::string serialize();
		void deserialize( const std::string &data );

		template <typename T> operator T*() const {
			return reinterpret_cast<T*>( data.get() );
		}
		template <typename T> operator T*() {
			return reinterpret_cast<T*>( data.get() );
		}

	private:
		std::unique_ptr<uint8_t[]> data;
		uint32_t data_nbytes = 0;
};

#endif /* DATA_H_ */
