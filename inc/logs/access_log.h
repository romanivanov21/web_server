/**
 *  Файл: access_error.h
 *
 *  Описание:
 */

class access_log
{
 public:
    access_log& get_instance( );

    void set_dir( std::string dir ) noexcept ;
    std::string get_dir( ) const noexcept;

    void create_log_file( );
    void write( const std::string &str );

    access_log( const access_log &copy ) = delete;
    access_log& operator=( const access_log &copy ) = delete;
 private:
    access_log( ) { }
    ~access_log( ) { }
};