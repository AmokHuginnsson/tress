/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/hcore/hsocket.hxx>
#include <yaal/tools/hiodispatcher.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

#include "tut_yaal_tools_hhuginn_base.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace tress::tut_helpers;

namespace tut {

struct tut_yaal_tools_hhuginn_network : public tress::tut_yaal_tools_hhuginn_base {
	static int const OBSCURE_PORT = 61930;
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

TUT_UNIT_TEST( "connect" )
	HThread serverRunner;
	HIODispatcher iod( 11, 1000 );
	HSocket::ptr_t serv( make_pointer<HSocket>( HSocket::TYPE::NETWORK | HSocket::TYPE::BLOCKING, 1 ) );
	serv->listen( "127.0.0.1", OBSCURE_PORT );
	iod.register_file_descriptor_handler(
		serv,
		HIODispatcher::callback_t(
			[&iod, &serv]( HIODispatcher::stream_t& ) {
				clog << "ENTER: acceptor" << endl;
				HSocket::ptr_t client( serv->accept() );
				iod.register_file_descriptor_handler(
					client,
					HIODispatcher::callback_t(
						[&iod]( HIODispatcher::stream_t& stream_ ) {
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
					)
				);
				clog << "LEAVE: acceptor" << endl;
			}
		)
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
	ENSURE_EQUALS(
		"Network.connect failed",
		execute(
			"import Network as net;\n"
			"main() {\n"
			"s = net.connect( \"127.0.0.1\", 61930 );\n"
			"s.write_line( \"Huginn is best!\\n\" );\n"
			"return ( s.read_line() );\n"
			"}\n"
		),
		"\"!tseb si nniguH\n\""
	);
	iod.stop();
	serverRunner.finish();
TUT_TEARDOWN()

TUT_UNIT_TEST( "connect invalid port" )
	ENSURE_EQUALS(
		"Network.connect bad port ok",
		execute_except(
			"import Network as net;\n"
			"main() {\n"
			"net.connect( \"127.0.0.1\", -1 );\n"
			"}\n"
		),
		"*anonymous stream*:3:12: Uncaught NetworkException: Bad port: -1"
	);
TUT_TEARDOWN()

TUT_UNIT_TEST( "connect to closed port" )
#ifdef __MSVCXX__
	char const errExpect[] = "No connection could be made because the target machine actively refused it.\r\n";
#else
	char const errExpect[] = "Connection refused";
#endif
	ENSURE_EQUALS(
		"Network.connect failed connect not signaled",
		execute(
			"import Network as net;\n"
			"main() {\n"
			"try{"
			"net.connect( \"127.0.0.1\", 5 );\n"
			"}catch(NetworkException e){\n"
			"return(e.message());\n"
			"}\n"
			"}\n"
		),
		"\"*anonymous stream*:3:16: "_ys.append( errExpect ).append( ": 127.0.0.1:5\"" )
	);
TUT_TEARDOWN()

}

