/*
---            `tress' 0.0.0 (c) 1978 by Marcin 'Amok' Konarski             ---

	tut_yaal_dbwrapper_hcruddescriptor.cxx - this file is integral part of `tress' project.

  i.  You may not make any changes in Copyright information.
  ii. You must attach Copyright information to any part of every copy
      of this software.

Copyright:

 You can use this software free of charge and you can redistribute its binary
 package freely but:
  1. You are not allowed to use any part of sources of this software.
  2. You are not allowed to redistribute any part of sources of this software.
  3. You are not allowed to reverse engineer this software.
  4. If you want to distribute a binary package of this software you cannot
     demand any fees for it. You cannot even demand
     a return of cost of the media or distribution (CD for example).
  5. You cannot involve this software in any commercial activity (for example
     as a free add-on to paid software or newspaper).
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE. Use it at your own risk.
*/

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
	d.set_filter( "id=2" );
	ENSURE_EQUALS( "set/get_filter failed", d.get_filter(), "id=2" );
	d.set_columns( "name" );
	ENSURE_EQUALS( "set/get_columns failed", d.get_columns(), "name" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "read" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::SELECT ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::SELECT ) );
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
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::SELECT ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::SELECT ) );
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
	d.set_filter( "id=2" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::SELECT ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::SELECT ) );
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
	d.set_filter( "id<=2" );
	d.set_sort( "id DESC" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::SELECT ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::SELECT ) );
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
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::SELECT ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::SELECT ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[0]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "onethreetwo" );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert (malformed)" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	ENSURE_THROW( "insert without fields succeeded", d.execute( HCRUDDescriptor::MODE::INSERT ), HCRUDDescriptorException );
	d.set_table( "crud" );
	ENSURE_THROW( "insert without fields succeeded", d.execute( HCRUDDescriptor::MODE::INSERT ), HCRUDDescriptorException );
TUT_TEARDOWN()

TUT_UNIT_TEST( "insert (auto fields)" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	d.execute( HCRUDDescriptor::MODE::SELECT );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::SELECT ) );
	d[1] = "extra"_ys;
	d.execute( HCRUDDescriptor::MODE::INSERT );
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
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::SELECT ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::SELECT ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "onetwothreeextra" );
	d[1] = "special"_ys;
	d.set_filter( "name=\"extra\"" );
	d.execute( HCRUDDescriptor::MODE::UPDATE );
TUT_TEARDOWN()

TUT_UNIT_TEST( "delete" )
	HLock dl( HMonitor::get_instance().acquire( "database" ) );
	HCRUDDescriptor d( util::connect( "sqlite3:///out/tress.sqlite" ) );
	d.set_table( "crud" );
	d.set_sort( "id ASC" );
	HRecordSet::ptr_t rs( d.execute( HCRUDDescriptor::MODE::SELECT ) );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::SELECT ) );
	HString res;
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "onetwothreespecial" );
	d.set_filter( "name=\"special\"" );
	d.execute( HCRUDDescriptor::MODE::DELETE );
	d.set_sort( "id ASC" );
	d.set_filter( "" );
	rs = d.execute( HCRUDDescriptor::MODE::SELECT );
	ENSURE_EQUALS( "bad mode", static_cast<int>( d.get_mode() ), static_cast<int>( HCRUDDescriptor::MODE::SELECT ) );
	res.clear();
	for ( HRecordSet::values_t values : *rs ) {
		res.append( *(values[0]) );
		res.append( *(values[1]) );
	}
	ENSURE_EQUALS( "no filter read failed", res, "1one2two3three" );
TUT_TEARDOWN()

}
