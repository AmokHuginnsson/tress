/* Read tress/LICENSE.md file for copyright and licensing information. */

#include <TUT/tut.hpp>
#include <yaal/tools/util.hxx>

#include "tut_yaal_hconsole_testwindow.hxx"
M_VCSID( "$Id: " __ID__ " $" )
#include <yaal/hconsole/hdatewidget.hxx>
#include <yaal/hconsole/htimewidget.hxx>
#include <yaal/tools/keycode.hxx>

#include "tut_yaal_hconsole_testset.hxx"

using namespace yaal;
using namespace yaal::hcore;
using namespace yaal::tools;
using namespace yaal::hconsole;
using namespace yaal::hconsole::list_widget_helper;
using namespace yaal::dbwrapper;

namespace tress {

HTestWindow::HTestWindow( const char* title_, yaal::dbwrapper::HDataBase::ptr_t const& db_ )
	: HWindow( title_ )
	, _db( db_ )
	, _names()
	, _list( nullptr )
	, _editableList( nullptr )
	, _edit( nullptr )
	, _name( nullptr )
	, _logPad( nullptr ) {
	M_PROLOG
	register_postprocess_handler( KEY_CODE::DELETE, nullptr, call( &HTestWindow::handler_delete, this, _1 ) );
	register_postprocess_handler( '\r', nullptr, call( &HTestWindow::handler_enter, this, _1 ) );
	return;
	M_EPILOG
}

HTestWindow::~HTestWindow ( void ) {
	M_PROLOG
	return;
	M_DESTRUCTOR_EPILOG
}

void HTestWindow::do_init( void ) {
	M_PROLOG
	HWindow::do_init();
	_name = create_widget<HComboboxWidget>( this, -16, 1, 9, 24, "&Name",
			HComboboxWidgetAttributes()
				.none_text( "-?-" )
				.dropped_width( 32 )
				.max_string_size( 128 )
				.mask( "^[a-zA-ZąĄćĆęĘłŁńŃóÓśŚźŹżŻ \\._@?-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED )
				.up<HComboboxWidgetAttributes>()
				.searchable( true )
	);
	_name->enable( true );
	HQuery::ptr_t q( _db->prepare_query( "SELECT * FROM test_dict;" ) );
	HRecordSet::ptr_t dict( q->execute() );
	HAsIsValueListModel<>::ptr_t controler = _name->get_model();
	int index( 0 );
	for ( HRecordSet::values_t const& row : *dict ) {
		int id( lexical_cast<int>( *row[0] ) );
		HString const& name( *row[1] );
		_names[id] = make_pair( index ++, name );
		HInfoItem item( 1 );
		item[ 0 ].set_integer( id );
		item[ 0 ].set_string( name );
		controler->add_tail( item );
	}
	_list = create_widget<HListWidget>( this, 1, 1, -17, -1, "&Test data", HListWidgetAttributes().checkable( true ).searchable( true ) );
	_list->enable( true );
	_list->set_focus();
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Name", 16, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING, "", _name ) );
	HWidget* control( nullptr );
	_list->add_column(
		-1, make_resource<HListWidget::HColumnInfo>(
			"Text", 32, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING, "",
			control = create_widget<HEditWidget>(
				this, -16, 27, 1, -1, "Te&xt",
				HEditWidgetAttributes()
					.max_string_size( 256 )
					.mask( "^[a-zA-ZąĄćĆęĘłŁńŃóÓśŚźŹżŻ !,\\.-]*$" )
					.text( "some very long text, way longer then widget visible space, I mean, really, really absurdly long line of text..." )
					.label_position( HWidget::LABEL::POSITION::STACKED )
			)
		)
	);
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Int", 8, HWidget::BITS::ALIGN::RIGHT, TYPE::INT_LONG_LONG, "",
			control = _edit = create_widget<HEditWidget>( this, -13, 1, 1, 18, "&Int",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.mask( "^[0-9]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Real", 20, HWidget::BITS::ALIGN::RIGHT, TYPE::DOUBLE_LONG, "",
			control = create_widget<HEditWidget>( this, -13, 21, 1, 24, "&Real",
				HEditWidgetAttributes()
				.max_string_size( 32 )
				.mask( "^[0-9\\.-]*$" )
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Date", 11, HWidget::BITS::ALIGN::CENTER, TYPE::HTIME, "",
			control = create_widget<HDateWidget>( this, -13, 47, "&Date",
				HWidgetAttributes()
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->add_column( -1, make_resource<HListWidget::HColumnInfo>( "Time", 11, HWidget::BITS::ALIGN::CENTER, TYPE::HTIME, "",
			control = create_widget<HTimeWidget>( this, -13, 61, "T&ime",
				HWidgetAttributes()
				.label_position( HWidget::LABEL::POSITION::STACKED ) ) ) );
	control->enable( true );
	_list->set_label_position( HWidget::LABEL::POSITION::STACKED );
	_list->register_event_listener( call( &HTestWindow::on_sel_change, this, _1 ) );
/*	_widgets.exchange( 1, 6 );
	_widgets.exchange( 2, 6 );
	_widgets.exchange( 3, 6 ); */
	HTestSet rs( _db );
	HRecordSet::ptr_t r = rs.get_records();
	HAsIsValueListModel<>::ptr_t mC = _list->get_model();
	HInfoItem row( 6 );
	for ( int i( 0 ), rn( 1 ); i < 3; ++ i ) {
		for ( HRecordSet::iterator it = r->begin(); it != r->end(); ++ it ) {
			rs.sync( it );
			row[ 0 ].set_integer( _names[static_cast<int>( rs._idName )].first );
			row[ 0 ].set_string( _names[static_cast<int>( rs._idName )].second + " " + util::ordinal( rn ) );
			row[ 1 ].set_string( rs._vText );
			row[ 2 ].set_string( rs._vInt + rn );
			row[ 3 ].set_string( rs._vReal );
			row[ 4 ].set_time( rs._vDate );
			row[ 5 ].set_time( rs._vTime );
			mC->add_tail( row );
			++ rn;
		}
	}
	_editableList = create_widget<HListWidget>( this, -10, 1, -3, 50, "&Edit test",
			HListWidgetAttributes()
			.editable( true )
			.searchable( true )
			.label_position( HWidget::LABEL::POSITION::STACKED ) );
	_editableList->add_column( -1, make_resource<HListWidget::HColumnInfo>( "text", 1, HWidget::BITS::ALIGN::LEFT, TYPE::HSTRING ) );
	_editableList->add_column( -1, make_resource<HListWidget::HColumnInfo>( "integer", 1, HWidget::BITS::ALIGN::RIGHT, TYPE::INT_LONG_LONG ) );
	_editableList->add_column( -1, make_resource<HListWidget::HColumnInfo>( "real", 1, HWidget::BITS::ALIGN::RIGHT, TYPE::DOUBLE_LONG ) );
	_editableList->enable( true );
	_logPad = create_widget<HLogPad>( this, -10, 52, -3, -1, "&Log pad", HWidgetAttributes().label_decoration( HWidget::LABEL::DECORATION::AUTO ).label_position( HWidget::LABEL::POSITION::STACKED ) );
	_logPad->add( "Color test:\n" );
	_logPad->add( COLOR::FG_RED, "red" );
	_logPad->add( COLOR::FG_GREEN, " green" );
	_logPad->add( COLOR::FG_BLUE, " blue\n" );
	_logPad->add( COLOR::FG_BRIGHTRED, "brightred" );
	_logPad->add( COLOR::FG_BRIGHTGREEN, " brightgreen" );
	_logPad->add( COLOR::FG_BRIGHTBLUE, " brightblue\n" );
	_logPad->add( COLOR::FG_CYAN, "cyan" );
	_logPad->add( COLOR::FG_BRIGHTCYAN, " brigthcyan\n" );
	_logPad->add( COLOR::FG_MAGENTA, "magenta" );
	_logPad->add( COLOR::FG_BRIGHTMAGENTA, " brigthmagenta\n" );
	_logPad->add( COLOR::FG_BROWN, "brown" );
	_logPad->add( COLOR::FG_YELLOW, " yellow\n" );
	_logPad->add( COLOR::FG_GRAY, "gray" );
	_logPad->add( COLOR::FG_LIGHTGRAY, " lightgray" );
	_logPad->add( COLOR::FG_WHITE, " white" );
	_logPad->enable( true );
	M_ENSURE( _widgets.get_widget_by_no( 9 ) == _logPad, "get_widget_by_no(9) failed" );
	M_ENSURE( _widgets.get_widget_by_no( 8 ) == _editableList, "get_widget_by_no(8) failed" );
	M_ENSURE( _widgets.get_widget_by_no( 4 ) == _edit, "get_widget_by_no(4) failed" );
	M_ENSURE( _widgets.get_widget_by_no( 2 ) == _list, "get_widget_by_no(2) failed" );
	M_ENSURE( _widgets.get_widget_by_no( 1 ) == _name, "get_widget_by_no(1) failed" );
	paint();
	return;
	M_EPILOG
}

bool HTestWindow::on_sel_change( yaal::hconsole::HEvent const& ) {
	list_widget_helper::HAbstractRow& current( _list->get_current_row() );
	status_bar()->message( "cursor position: %d, %d", _name->get_cursor_position(), static_cast<int>( current[0].get_integer() ) );
	return ( true );
}

bool HTestWindow::handler_delete( yaal::hconsole::HEvent const& ) {
	M_PROLOG
	if ( _list->has_focus() && _list->get_row_count() ) {
		_list->remove_current_row();
	}
	return ( true );
	M_EPILOG
}

bool HTestWindow::handler_enter( yaal::hconsole::HEvent const& ) {
	M_PROLOG
//	if ( _list->get_row_count() )
//		_list->set_current_row_cell( 2, _edit->get() );
	return ( true );
	M_EPILOG
}

}

