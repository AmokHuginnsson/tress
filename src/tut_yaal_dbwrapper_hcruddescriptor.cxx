/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>

#include <yaal/dbwrapper/dbwrapper.hxx>
#include <yaal/dbwrapper/hcruddescriptor.hxx>
#include <yaal/tools/hmonitor.hxx>
M_VCSID( "$Id: " __ID__ " $" )
#include "tut_helpers.hxx"

using namespace tut;
using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::dbwrapper;
using namespace tress::tut_helpers;

namespace tut {

TUT_SIMPLE_MOCK( tut_yaal_dbwrapper_hcruddescriptor );
TUT_TEST_GROUP( tut_yaal_dbwrapper_hcruddescriptor, "yaal::dbwrapper::HCRUDDescriptor" );

TUT_UNIT_TEST( "getters" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	ENSURE_EQUALS( "set/get_table failed", d.get_table(), "crud" );
	d.set_sort( "id DESC" );
	ENSURE_EQUALS( "set/get_sort failed", d.get_sort(), "id DESC" );
	d.set_filter( "id" );
	d.set_filter_value( "2" );
	ENSURE_EQUALS( "set/get_filter failed", d.get_filter(), "id = 2" );
	d.set_columns( "name" );
	ENSURE_EQUALS( "set/get_columns failed", d.get_columns(), "name" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::READ ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::READ ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[0]) );
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "1one2two3three" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read sort" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	d.set_sort( "id DESC" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::READ ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::READ ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[0]) );
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "3three2two1one" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read filter" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	d.set_filter( "id" );
	d.set_filter_value( "2" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::READ ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::READ ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[0]) );
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "2two" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read filter and sort" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	d.set_filter( "id", HCRUDDescriptor::MODE::READ, HCRUDDescriptor::OFilter::CONDITION::LESS_OR_EQUAL );
	d.set_filter_value( "2" );
	d.set_sort( "id DESC" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::READ ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::READ ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[0]) );
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "2two1one" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read columns" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	d.set_columns( "name" );
	d.set_sort( "name ASC" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::READ ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::READ ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[0]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "onethreetwo" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert (malformed)" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	ENSURE_THROW( "insert without fields succeeded", d.execute( HCRUDDescriptor::MODE::CREATE ), HCRUDDescriptorException );
	d.set_table( "crud" );
	ENSURE_THROW( "insert without fields succeeded", d.execute( HCRUDDescriptor::MODE::CREATE ), HCRUDDescriptorException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert (auto fields)" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	d.execute( HCRUDDescriptor::MODE::READ );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::READ ) );
	d[1] = "extra"_ys;
	d.execute( HCRUDDescriptor::MODE::CREATE );
TUT_TEARDOWN()

TUT_UNIT_TEST( "update (malformed)" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	ENSURE_THROW( "update without fields succeeded", d.execute( HCRUDDescriptor::MODE::UPDATE ), HCRUDDescriptorException );
	d.set_table( "crud" );
	ENSURE_THROW( "update without fields succeeded", d.execute( HCRUDDescriptor::MODE::UPDATE ), HCRUDDescriptorException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "update (auto fields)" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	d.set_sort( "id ASC" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::READ ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::READ ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "onetwothreeextra" );
	d[1] = "special"_ys;
	d.set_filter( "name", HCRUDDescriptor::MODE::UPDATE );
	d.set_filter_value( "extra" );
	d.execute( HCRUDDescriptor::MODE::UPDATE );
TUT_TEARDOWN()

TUT_UNIT_TEST( "delete" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	d.set_sort( "id ASC" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::READ ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::READ ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "onetwothreespecial" );
	d.set_filter( "name", HCRUDDescriptor::MODE::DELETE );
	d.set_filter_value( "special" );
	d.execute( HCRUDDescriptor::MODE::DELETE );
	d.set_sort( "id ASC" );
	rs = d.execute( HCRUDDescriptor::MODE::READ );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::READ ) );
	res.clear();
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[0]) );
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "1one2two3three" );
TUT_TEARDOWN()

}

