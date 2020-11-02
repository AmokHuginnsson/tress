/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <cstdio>
#include <cstdlib>
#ifdef __GNUC__
#include <unistd.h>
#endif /* #ifdef __GNUC__ */
#include <TUT/tut.hpp>

#include <yaal/hcore/hsocket.hxx>
#include <yaal/tools/hiodispatcher.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::hcore::system;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_network : public tress::tut_yaal_tools_hhuginn_base {
	static int const OBSCURE_PORT = 61930;
	void play_scenario( yaal::hcore::HString const&, HSocket::ptr_t );
	tut_yaal_tools_hhuginn_network( void )
		: tress::tut_yaal_tools_hhuginn_base() {
		::unlink( "/tmp/TUT_huginn_socket" );
		errno = 0;
	}
	virtual ~tut_yaal_tools_hhuginn_network( void ) {}
};

TUT_TEST_GROUP( tut_yaal_tools_hhuginn_network, "yaal::tools::HHuginn.Network" );

TUT_UNIT_TEST( "resolve" )
	hcore::HString res(
		execute(
			"import Network as net;"
			"main(){"
			"return(net.resolve(\"localhost\"));"
			"}"
		)
	);
	ENSURE( "Network.resolve falied", ( res == "\"127.0.0.1\"" ) || ( res == "\"0.0.0.0\"" ) );
TUT_TEARDOWN()

TUT_UNIT_TEST( "resolve invalid" )
	ENSURE_IN(
		"resolve of invalid hostname succeeded",
		execute_except(
			"import Network as net;"
			"main(){"
			"return(net.resolve(\"invalid.example.com\"));"
			"}"
		),
	  std::vector<hcore::HString>({
			"*anonymous stream*:1:48: Uncaught NetworkException: No such host is known: invalid.example.com",
			"*anonymous stream*:1:48: Uncaught NetworkException: No address associated with hostname: invalid.example.com",
			"*anonymous stream*:1:48: Uncaught NetworkException: hostname nor servname provided, or not known: invalid.example.com",
			"*anonymous stream*:1:48: Uncaught NetworkException: Name or service not known: invalid.example.com",
			"*anonymous stream*:1:48: Uncaught NetworkException: Name does not resolve: invalid.example.com",
			"*anonymous stream*:1:48: Uncaught NetworkException: node name or service name not known: invalid.example.com"
		})
	);
TUT_TEARDOWN()

void tut_yaal_tools_hhuginn_network::play_scenario( yaal::hcore::HString const& code_, HSocket::ptr_t serv_ ) {
	HThread serverRunner;
	HIODispatcher iod( 11, 1000 );
	iod.register_file_descriptor_handler(
		serv_,
		HIODispatcher::callback_t(
			[&iod, &serv_]( HIODispatcher::stream_t&, IO_EVENT_TYPE ) {
				clog << "ENTER: acceptor" << endl;
				HSocket::ptr_t client( serv_->accept() );
				iod.register_file_descriptor_handler(
					client,
					HIODispatcher::callback_t(
						[&iod]( HIODispatcher::stream_t& stream_, IO_EVENT_TYPE ) {
							clog << "ENTER: message hangler" << endl;
							hcore::HString line;
							if ( stream_->read_until( line ) > 0 ) {
								clog << "serv got: [" << line << "]" << endl;
								reverse( line.begin(), line.end() );
								*stream_ << line << endl;
							} else {
								iod.unregister_file_descriptor_handler( stream_ );
							}
							clog << "LEAVE: message hangler" << endl;
						}
					),
					IO_EVENT_TYPE::READ
				);
				clog << "LEAVE: acceptor" << endl;
			}
		),
		IO_EVENT_TYPE::READ
	);
	serverRunner.spawn(
		HThread::call_t(
			[&iod]() -> void {
				try {
					clog << "ENTER: server" << endl;
					iod.run();
					clog << "LEAVE: server" << endl;
				} catch ( HException const& e ) {
					cerr << "exception caught: " << e.what() << endl;
				} catch ( std::exception const& e ) {
					cerr << "exception caught: " << e.what() << endl;
				} catch ( ... ) {
					cerr << "unknown exception type" << endl;
				}
			}
		)
	);
	ENSURE_EQUALS( "Network.connect failed", execute( code_ ), "\"!tseb si nniguH\\n\"" );
	iod.stop();
	serverRunner.finish();
}

TUT_UNIT_TEST( "connect[plain]" )
	HSocket::ptr_t serv( make_pointer<HSocket>( HSocket::TYPE::NETWORK | HSocket::TYPE::BLOCKING, 1 ) );
	serv->listen( "127.0.0.1", OBSCURE_PORT );
	play_scenario(
		"import Network as net;\n"
		"main() {\n"
		"s = net.connect( net.CONNECTION_TYPE.PLAIN, \"127.0.0.1\", 61930 );\n"
		"s.write_line( \"Huginn is best!\\n\" );\n"
		"return ( s.read_line() );\n"
		"}\n",
		serv
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "connect[ssl]" )
	HSocket::ptr_t serv( make_pointer<HSocket>( HSocket::TYPE::NETWORK | HSocket::TYPE::BLOCKING | HSocket::TYPE::SSL, 1 ) );
	serv->listen( "127.0.0.1", OBSCURE_PORT );
	play_scenario(
		"import Network as net;\n"
		"main() {\n"
		"s = net.connect( net.CONNECTION_TYPE.SSL, \"127.0.0.1\", 61930 );\n"
		"s.write_line( \"Huginn is best!\\n\" );\n"
		"return ( s.read_line() );\n"
		"}\n",
		serv
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "connect[file]" )
	HSocket::ptr_t serv( make_pointer<HSocket>( HSocket::TYPE::FILE | HSocket::TYPE::BLOCKING, 1 ) );
	serv->listen( "/tmp/TUT_huginn_socket" );
	play_scenario(
		"import Network as net;\n"
		"main() {\n"
		"s = net.connect( net.CONNECTION_TYPE.FILE, \"/tmp/TUT_huginn_socket\" );\n"
		"s.write_line( \"Huginn is best!\\n\" );\n"
		"return ( s.read_line() );\n"
		"}\n",
		serv
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "connect invalid port" )
	ENSURE_EQUALS(
		"Network.connect bad port ok",
		execute_except(
			"import Network as net;\n"
			"main() {\n"
			"net.connect( net.CONNECTION_TYPE.PLAIN, \"127.0.0.1\", -1 );\n"
			"}\n"
		),
		"*anonymous stream*:3:12: Uncaught NetworkException: Bad port: -1"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "connect to closed port" )
#ifdef __MSVCXX__
	char const errExpect[] = "No connection could be made because the target machine actively refused it";
#else
	char const errExpect[] = "Connection refused";
#endif
	ENSURE_EQUALS(
		"Network.connect failed connect not signaled",
		execute(
			"import Network as net;\n"
			"main() {\n"
			"try{"
			"net.connect( net.CONNECTION_TYPE.PLAIN, \"127.0.0.1\", 5 );\n"
			"}catch(NetworkException e){\n"
			"return(e.message());\n"
			"}\n"
			"}\n"
		),
		"\"*anonymous stream*:3:16: "_ys.append( errExpect ).append( ": 127.0.0.1:5\"" )
	);
TUT_TEARDOWN()

}

