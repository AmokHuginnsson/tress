/*
---           booker.h 0.0.0 (c) 1978 by Marcin 'Amok' Konarski            ---

  testwindow.hxx - this file is integral part of booker.h project.

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

#ifndef TRESS_YAAL_HCONSOLE_TESTWINDOW_HXX_INCLUDED
#define TRESS_YAAL_HCONSOLE_TESTWINDOW_HXX_INCLUDED

#include <yaal/hcore/hhashmap.hxx>
#include <yaal/dbwrapper/hdatabase.hxx>
#include <yaal/hconsole/hwindow.hxx>
#include <yaal/hconsole/hevent.hxx>
#include <yaal/hconsole/hcomboboxwidget.hxx>

namespace tress {

class HTestWindow : public yaal::hconsole::HWindow {
protected:
	/*{*/
	typedef yaal::hcore::HHashMap<int, yaal::hcore::HPair<int, yaal::hcore::HString>> names_t;
	yaal::dbwrapper::HDataBase::ptr_t _db;
	names_t _names;
	yaal::hconsole::HListWidget* _list;
	yaal::hconsole::HListWidget* _editableList;
	yaal::hconsole::HEditWidget* _edit;
	yaal::hconsole::HComboboxWidget* _name;
	/*}*/
public:
	/*{*/
	HTestWindow( const char*, yaal::dbwrapper::HDataBase::ptr_t const& );
	virtual ~HTestWindow( void );
	/*}*/
protected:
	/*{*/
	virtual void do_init( void );
	bool handler_delete( yaal::hconsole::HEvent const& );
	bool handler_enter( yaal::hconsole::HEvent const& );
	bool on_sel_change( yaal::hconsole::HEvent const& );
	/*}*/
private:
	/*{*/
	HTestWindow( const HTestWindow& );
	HTestWindow& operator = ( const HTestWindow& );
	/*}*/
};

}

#endif /* TRESS_YAAL_HCONSOLE_TESTWINDOW_HXX_INCLUDED */
