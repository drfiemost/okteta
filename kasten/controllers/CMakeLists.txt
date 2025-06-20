set( LIBFRAMESPRINT_REL_DIR ../../libs/framesprint )
set( KASTEN_REL_DIR ../../libs/kasten )
set( OKTETA_REL_DIR ../.. )

include_directories(
  ../gui
  ../gui/view
  ../gui/io
  ../gui/liboktetawidgets
  ../gui/system
  ../core
  ../core/io
  ../core/document
  ${KASTEN_REL_DIR}/gui
  ${KASTEN_REL_DIR}/gui/view
  ${KASTEN_REL_DIR}/gui/system
  ${KASTEN_REL_DIR}/gui/shell
  ${KASTEN_REL_DIR}/gui/controller
  ${KASTEN_REL_DIR}/core
  ${KASTEN_REL_DIR}/core/document
  ${KASTEN_REL_DIR}/core/entity
  ${KASTEN_REL_DIR}/core/io
  ${KASTEN_REL_DIR}/core/system
  view/libbytearraychecksum
  view/libbytearrayfilter
  view/libfinddialog
  ${LIBFRAMESPRINT_REL_DIR}
  ${OKTETA_REL_DIR}/gui
  ${OKTETA_REL_DIR}/gui/libcolumnsview
  ${OKTETA_REL_DIR}/core
)

set( DOCUMENTINFOCONTROLLER_SRCS
  document/info/bytearraymodeliodevice.cpp
  document/info/documentinfotool.cpp
  document/info/documentinfoview.cpp
  document/info/documentinfotoolview.cpp
)
set( OVERWRITEONLYCONTROLLER_SRCS
  document/overwriteonly/overwriteonlycontroller.cpp
)
set( OVERWRITEMODECONTROLLER_SRCS
  view/overwritemode/overwritemodecontroller.cpp
)
set( INFOCONTROLLER_SRCS
  view/info/createstatisticjob.cpp
  view/info/statistictablemodel.cpp
  view/info/infotool.cpp
  view/info/infoview.cpp
  view/info/infotoolview.cpp
  view/info/infotoolfactory.cpp
  view/info/infotoolviewfactory.cpp
)
kde4_add_kcfg_files( INFOCONTROLLER_SRCS view/info/infoviewsettings.kcfgc )

set( STRINGSEXTRACTCONTROLLER_SRCS
  view/stringsextract/extractstringsjob.cpp
  view/stringsextract/stringsextracttool.cpp
  view/stringsextract/containedstringtablemodel.cpp
  view/stringsextract/stringsextractview.cpp
  view/stringsextract/stringsextracttoolview.cpp
  view/stringsextract/stringsextracttoolfactory.cpp
  view/stringsextract/stringsextracttoolviewfactory.cpp
)

set( LIBCHECKSUM_SRCS
  view/libbytearraychecksum/abstractbytearraychecksumalgorithm.cpp
  view/libbytearraychecksum/abstractbytearraychecksumparameterset.cpp
  view/libbytearraychecksum/abstractbytearraychecksumparametersetedit.cpp
  view/libbytearraychecksum/bytearraychecksumalgorithmfactory.cpp
  view/libbytearraychecksum/bytearraychecksumparameterseteditfactory.cpp
  view/libbytearraychecksum/algorithm/crc32bytearraychecksumalgorithm.cpp
  view/libbytearraychecksum/algorithm/adler32bytearraychecksumalgorithm.cpp
  view/libbytearraychecksum/algorithm/modsum8bytearraychecksumalgorithm.cpp
  view/libbytearraychecksum/algorithm/modsum16bytearraychecksumalgorithm.cpp
  view/libbytearraychecksum/algorithm/modsum32bytearraychecksumalgorithm.cpp
  view/libbytearraychecksum/algorithm/modsum64bytearraychecksumalgorithm.cpp
## NEWCHECKSUM(start)
## Here add the names of your source files of your checksum algorithm,
## e.g.
##   view/libbytearraychecksum/algorithm/mybytearraychecksumalgorithm.cpp
## NEWCHECKSUM(end)
  view/libbytearraychecksum/algorithm/nobytearraychecksumparameterset.cpp
  view/libbytearraychecksum/algorithm/nobytearraychecksumparametersetedit.cpp
  view/libbytearraychecksum/algorithm/modsumbytearraychecksumparameterset.cpp
  view/libbytearraychecksum/algorithm/modsumbytearraychecksumparametersetedit.cpp
## NEWCHECKSUMPARAMETERSET(start)
## Here add the names of your source files of your checksum parameter set and
## of the widget to edit the checksum parameter set,
## e.g.
##   view/libbytearraychecksum/algorithm/mybytearraychecksumparameterset.cpp
##   view/libbytearraychecksum/algorithm/mybytearraychecksumparametersetedit.cpp
## NEWCHECKSUMPARAMETERSET(end)
)

set( CHECKSUMCONTROLLER_SRCS
  view/checksum/checksumcalculatejob.cpp
  view/checksum/checksumtool.cpp
  view/checksum/checksumview.cpp
  view/checksum/checksumtoolview.cpp
  view/checksum/checksumtoolfactory.cpp
  view/checksum/checksumtoolviewfactory.cpp
)
set( FINDDIALOG_LIB_SRCS
  view/libfinddialog/kabstractfinddialog.cpp
)
set( PODDECODERCONTROLLER_SRCS
  view/poddecoder/typecodecs/binary8codec.cpp
  view/poddecoder/typecodecs/octal8codec.cpp
  view/poddecoder/typecodecs/hexadecimal8codec.cpp
  view/poddecoder/typecodecs/uint8codec.cpp
  view/poddecoder/typecodecs/uint16codec.cpp
  view/poddecoder/typecodecs/uint32codec.cpp
  view/poddecoder/typecodecs/uint64codec.cpp
  view/poddecoder/typecodecs/sint8codec.cpp
  view/poddecoder/typecodecs/sint16codec.cpp
  view/poddecoder/typecodecs/sint32codec.cpp
  view/poddecoder/typecodecs/sint64codec.cpp
  view/poddecoder/typecodecs/float32codec.cpp
  view/poddecoder/typecodecs/float64codec.cpp
  view/poddecoder/typecodecs/char8codec.cpp
  view/poddecoder/typecodecs/utf8codec.cpp
  view/poddecoder/typeeditors/abstractvalue8editor.cpp
  view/poddecoder/typeeditors/binary8editor.cpp
  view/poddecoder/typeeditors/octal8editor.cpp
  view/poddecoder/typeeditors/hexadecimal8editor.cpp
  view/poddecoder/typeeditors/uintspinbox.cpp
  view/poddecoder/typeeditors/sintspinbox.cpp
  view/poddecoder/typeeditors/uint8editor.cpp
  view/poddecoder/typeeditors/uint16editor.cpp
  view/poddecoder/typeeditors/uint32editor.cpp
  view/poddecoder/typeeditors/uint64editor.cpp
  view/poddecoder/typeeditors/sint8editor.cpp
  view/poddecoder/typeeditors/sint16editor.cpp
  view/poddecoder/typeeditors/sint32editor.cpp
  view/poddecoder/typeeditors/sint64editor.cpp
  view/poddecoder/typeeditors/float32editor.cpp
  view/poddecoder/typeeditors/float64editor.cpp
  view/poddecoder/typeeditors/char8editor.cpp
  view/poddecoder/typeeditors/utf8editor.cpp
  view/poddecoder/poddata.cpp
  view/poddecoder/poddecodertool.cpp
  view/poddecoder/podtablemodel.cpp
  view/poddecoder/poddelegate.cpp
  view/poddecoder/podtableview.cpp
  view/poddecoder/poddecodertoolview.cpp
  view/poddecoder/poddecodertoolfactory.cpp
  view/poddecoder/poddecodertoolviewfactory.cpp
)
set( BYTETABLECONTROLLER_SRCS
  view/bytetable/bytetablemodel.cpp
  view/bytetable/bytetabletool.cpp
  view/bytetable/bytetableview.cpp
  view/bytetable/bytetabletoolview.cpp
  view/bytetable/bytetabletoolfactory.cpp
  view/bytetable/bytetabletoolviewfactory.cpp
)
kde4_add_kcfg_files( BYTETABLECONTROLLER_SRCS view/bytetable/bytetableviewsettings.kcfgc )

set( SEARCHCONTROLLER_SRCS
  view/search/ksearchdialog.cpp
  view/search/searchjob.cpp
  view/search/searchtool.cpp
  view/search/searchcontroller.cpp
)
set( REPLACECONTROLLER_SRCS
  view/replace/kreplacedialog.cpp
  view/replace/kreplaceprompt.cpp
  view/replace/replacetool.cpp
  view/replace/replacecontroller.cpp
)
set( LIBFILTER_SRCS
  view/libbytearrayfilter/abstractbytearrayfilter.cpp
  view/libbytearrayfilter/abstractbytearrayfilterparameterset.cpp
  view/libbytearrayfilter/abstractbytearrayfilterparametersetedit.cpp
  view/libbytearrayfilter/bytearrayfilterfactory.cpp
  view/libbytearrayfilter/bytearrayfilterparameterseteditfactory.cpp
  view/libbytearrayfilter/filter/nobytearrayfilterparameterset.cpp
  view/libbytearrayfilter/filter/operandbytearrayfilterparameterset.cpp
  view/libbytearrayfilter/filter/reversebytearrayfilterparameterset.cpp
  view/libbytearrayfilter/filter/rotatebytearrayfilterparameterset.cpp
## NEWFILTERPARAMETERSET(start)
## Here add the names of your source files of your filter parameter set,
## e.g.
##  view/libbytearrayfilter/filter/mybytearrayfilterparameterset.cpp
## NEWFILTERPARAMETERSET(end)
  view/libbytearrayfilter/filter/andbytearrayfilter.cpp
  view/libbytearrayfilter/filter/orbytearrayfilter.cpp
  view/libbytearrayfilter/filter/xorbytearrayfilter.cpp
  view/libbytearrayfilter/filter/invertbytearrayfilter.cpp
  view/libbytearrayfilter/filter/reversebytearrayfilter.cpp
  view/libbytearrayfilter/filter/rotatebytearrayfilter.cpp
  view/libbytearrayfilter/filter/shiftbytearrayfilter.cpp
## NEWFILTER(start)
## Here add the names of your source files of your filter,
## e.g.
##   view/libbytearrayfilter/filter/mybytearrayfilter.cpp
## NEWFILTER(end)
  view/libbytearrayfilter/filter/nobytearrayfilterparametersetedit.cpp
  view/libbytearrayfilter/filter/operandbytearrayfilterparametersetedit.cpp
  view/libbytearrayfilter/filter/reversebytearrayfilterparametersetedit.cpp
  view/libbytearrayfilter/filter/rotatebytearrayfilterparametersetedit.cpp
## NEWFILTERPARAMETERSET(start)
## Here add the names of your source files of your widget to edit the filter parameter set,
## e.g.
##   view/libbytearrayfilter/filter/mybytearrayfilterparametersetedit.cpp
## NEWFILTERPARAMETERSET(end)
)
set( FILTERCONTROLLER_SRCS
  view/filter/filterjob.cpp
  view/filter/filtertool.cpp
  view/filter/filterview.cpp
  view/filter/filtertoolview.cpp
  view/filter/filtertoolfactory.cpp
  view/filter/filtertoolviewfactory.cpp
)
set( CHARSETCONVERSIONTOOL_SRCS
  view/charsetconversion/charsetconversionjob.cpp
  view/charsetconversion/charsetconversiontool.cpp
  view/charsetconversion/charsetconversionview.cpp
  view/charsetconversion/charsetconversiontoolview.cpp
  view/charsetconversion/charsetconversiontoolfactory.cpp
  view/charsetconversion/charsetconversiontoolviewfactory.cpp
)
set( GOTOOFFSETCONTROLLER_SRCS
  view/gotooffset/gotooffsettool.cpp
  view/gotooffset/gotooffsetview.cpp
  view/gotooffset/gotooffsettoolview.cpp
  view/gotooffset/gotooffsetcontroller.cpp
)
set( SELECTRANGECONTROLLER_SRCS
  view/selectrange/selectrangetool.cpp
  view/selectrange/selectrangeview.cpp
  view/selectrange/selectrangetoolview.cpp
  view/selectrange/selectrangecontroller.cpp
)
set( BOOKMARKSCONTROLLER_SRCS
  view/bookmarks/bookmarkeditpopup.cpp
  view/bookmarks/bookmarkscontroller.cpp
)
set( BOOKMARKSTOOL_SRCS
  view/bookmarks/bookmarklistmodel.cpp
  view/bookmarks/bookmarkstool.cpp
  view/bookmarks/bookmarksview.cpp
  view/bookmarks/bookmarkstoolview.cpp
  view/bookmarks/bookmarkstoolfactory.cpp
  view/bookmarks/bookmarkstoolviewfactory.cpp
)

set( STRUCTVIEW_SRCS
  view/structures/allprimitivetypes.cpp
  view/structures/structurestoolfactory.cpp
  view/structures/structurestoolviewfactory.cpp
  view/structures/structuresmanager.cpp
  view/structures/structtool.cpp
  view/structures/structtreemodel.cpp
#   view/structures/modeltest.cpp
  view/structures/structview.cpp
  view/structures/structtoolview.cpp
  view/structures/structviewitemdelegate.cpp
  view/structures/structuredefinitionfile.cpp
  view/structures/settings/structureaddremovewidget.cpp
  view/structures/settings/structviewdisplaysettingswidget.cpp
  view/structures/settings/structuresmanagerview.cpp
  view/structures/datatypes/topleveldatainformation.cpp
  view/structures/datatypes/datainformation.cpp
  view/structures/datatypes/datainformationbase.cpp
  view/structures/datatypes/dummydatainformation.cpp
  view/structures/datatypes/datainformationwithchildren.cpp
  view/structures/datatypes/structuredatainformation.cpp
  view/structures/datatypes/taggeduniondatainformation.cpp
  view/structures/datatypes/uniondatainformation.cpp
  view/structures/datatypes/array/arraydatainformation.cpp
  view/structures/datatypes/array/abstractarraydata.cpp
  view/structures/datatypes/array/complexarraydata.cpp
  view/structures/datatypes/array/primitivearraydata.cpp
  view/structures/datatypes/primitive/pointerdatainformation.cpp
  view/structures/datatypes/primitive/chardatainformation.cpp
  view/structures/datatypes/primitive/doubledatainformation.cpp
  view/structures/datatypes/primitive/floatdatainformation.cpp
  view/structures/datatypes/primitive/sintdatainformation.cpp
  view/structures/datatypes/primitive/uintdatainformation.cpp
  view/structures/datatypes/primitive/booldatainformation.cpp
  view/structures/datatypes/primitive/flagdatainformation.cpp
  view/structures/datatypes/primitive/primitivedatainformation.cpp
  view/structures/datatypes/primitive/basicprimitivedatainformation.cpp
  view/structures/datatypes/primitive/bitfield/abstractbitfielddatainformation.cpp
  view/structures/datatypes/primitive/bitfield/boolbitfielddatainformation.cpp
  view/structures/datatypes/primitive/bitfield/signedbitfielddatainformation.cpp
  view/structures/datatypes/primitive/bitfield/unsignedbitfielddatainformation.cpp
  view/structures/datatypes/primitive/enumdatainformation.cpp
  view/structures/datatypes/primitive/enumdefinition.cpp
  view/structures/datatypes/primitivefactory.cpp
  view/structures/datatypes/primitivedatatype.cpp
  view/structures/datatypes/strings/stringdatainformation.cpp
  view/structures/datatypes/strings/stringdata.cpp
  view/structures/datatypes/strings/asciistringdata.cpp
  view/structures/datatypes/strings/latin1stringdata.cpp
  view/structures/datatypes/strings/utf8stringdata.cpp
  view/structures/datatypes/strings/utf16stringdata.cpp
  view/structures/datatypes/strings/utf32stringdata.cpp
  view/structures/script/scriptengineinitializer.cpp
  view/structures/script/scripthandler.cpp
  view/structures/script/scripthandlerinfo.cpp
  view/structures/script/scriptutils.cpp
  view/structures/script/scriptlogger.cpp
  view/structures/script/scriptloggerview.cpp
  view/structures/script/safereference.cpp
  view/structures/script/classes/defaultscriptclass.cpp
  view/structures/script/classes/arrayscriptclass.cpp
  view/structures/script/classes/primitivescriptclass.cpp
  view/structures/script/classes/enumscriptclass.cpp
  view/structures/script/classes/pointerscriptclass.cpp
  view/structures/script/classes/bitfieldscriptclass.cpp
  view/structures/script/classes/stringscriptclass.cpp
  view/structures/script/classes/structunionscriptclass.cpp
  view/structures/parsers/abstractstructureparser.cpp
  view/structures/parsers/osdparser.cpp
  view/structures/parsers/scriptfileparser.cpp
  view/structures/parsers/scriptvalueconverter.cpp
  view/structures/parsers/scriptvalueconverter_p.cpp
  view/structures/parsers/datainformationfactory.cpp
  view/structures/parsers/parserutils.cpp
)
configure_file( config-structtool.h.cmake  ${CMAKE_CURRENT_BINARY_DIR}/config-structtool.h )
if ( OKTETA_DEBUG_SCRIPT )
    message( STATUS "Okteta will be compiled with script debugging enabled" )
else( OKTETA_DEBUG_SCRIPT )
    message( STATUS "Okteta will be compiled without script debugging. (-DOKTETA_DEBUG_SCRIPT=1 to enable)" )
endif( OKTETA_DEBUG_SCRIPT )
kde4_add_kcfg_files( STRUCTVIEW_SRCS view/structures/settings/structviewpreferences.kcfgc )
kde4_add_ui_files( STRUCTVIEW_SRCS view/structures/settings/structviewdisplaysettingswidget.ui )

set( LIBFRAMESPRINT_SRCS
  ${LIBFRAMESPRINT_REL_DIR}/abstractframerenderer.cpp
  ${LIBFRAMESPRINT_REL_DIR}/framestopaperprinter.cpp
  ${LIBFRAMESPRINT_REL_DIR}/headerfooterframerenderer.cpp
)
set( PRINTCONTROLLER_SRCS
  ${LIBFRAMESPRINT_SRCS}
  view/print/printcontroller.cpp
  view/print/printtool.cpp
  view/print/printjob.cpp
  view/print/abstractcolumnframerenderer.cpp
  view/print/printcolumnstylist.cpp
  view/print/bytearrayframerenderer.cpp
)
set( VIEWCONFIGCONTROLLER_SRCS
  view/viewconfig/bytesperlinedialog.cpp
  view/viewconfig/bytespergroupdialog.cpp
  view/viewconfig/viewconfigcontroller.cpp
)
set( VIEWSTATUSCONTROLLER_SRCS
  view/viewstatus/viewstatuscontroller.cpp
)
set( VIEWMODECONTROLLER_SRCS
  view/viewmode/viewmodecontroller.cpp
)

set( VIEWPROFILESCONTROLLER_SRCS
  view/viewprofiles/viewprofileedit.cpp
  view/viewprofiles/viewprofileeditdialog.cpp
  view/viewprofiles/viewprofiletablemodel.cpp
  view/viewprofiles/viewprofilecontroller.cpp
)

set( VIEWPROFILESMANAGECONTROLLER_SRCS
  view/viewprofiles/viewprofilesmanagedialog.cpp
  view/viewprofiles/viewprofilesmanagecontroller.cpp
)

#structview and poddecoder sources are also needed for structures tool unit tests
#create a OBJECT library (http://www.cmake.org/Wiki/CMake/Tutorials/Object_Library)
#to prevent compiling these object files twice with exactly the same compile flags
#TODO remove once CMake >= 2.8.9 is required for building KDE
if ( CMAKE_VERSION VERSION_GREATER 2.8.8 AND NOT WIN32)
    #OBJECT libraries seem buggy with regard to automoc, have to call it manually
    automoc4( poddecoder_objs PODDECODERCONTROLLER_SRCS )
    automoc4( structview_objs STRUCTVIEW_SRCS )
    add_library( poddecoder_objs OBJECT ${PODDECODERCONTROLLER_SRCS} )
    add_library( structview_objs OBJECT ${STRUCTVIEW_SRCS} )
    set_target_properties(poddecoder_objs structview_objs PROPERTIES POSITION_INDEPENDENT_CODE ON)
    set( PODDECODER_OBJS $<TARGET_OBJECTS:poddecoder_objs>)
    set( STRUCTVIEW_OBJS $<TARGET_OBJECTS:structview_objs>)
else()
    #compile the sources twice for older CMake version
    set( PODDECODER_OBJS ${PODDECODERCONTROLLER_SRCS})
    set( STRUCTVIEW_OBJS ${STRUCTVIEW_SRCS})
endif()

set( OKTETA_KASTEN_CONTROLLERS_SRCS
#   ${OVERWRITEONLYCONTROLLER_SRCS}
  ${OVERWRITEMODECONTROLLER_SRCS}
  ${DOCUMENTINFOCONTROLLER_SRCS}
  ${LIBCHECKSUM_SRCS}
  ${CHECKSUMCONTROLLER_SRCS}
  ${STRINGSEXTRACTCONTROLLER_SRCS}
  ${BYTETABLECONTROLLER_SRCS}
  ${INFOCONTROLLER_SRCS}
  ${FINDDIALOG_LIB_SRCS}
  ${SEARCHCONTROLLER_SRCS}
  ${REPLACECONTROLLER_SRCS}
  ${LIBFILTER_SRCS}
  ${FILTERCONTROLLER_SRCS}
  ${CHARSETCONVERSIONTOOL_SRCS}
  ${GOTOOFFSETCONTROLLER_SRCS}
  ${SELECTRANGECONTROLLER_SRCS}
  ${PRINTCONTROLLER_SRCS}
  ${BOOKMARKSCONTROLLER_SRCS}
  ${BOOKMARKSTOOL_SRCS}
  ${VIEWCONFIGCONTROLLER_SRCS}
  ${VIEWSTATUSCONTROLLER_SRCS}
  ${VIEWMODECONTROLLER_SRCS}
  ${VIEWPROFILESCONTROLLER_SRCS}
  ${VIEWPROFILESMANAGECONTROLLER_SRCS}
  ${PODDECODER_OBJS}
  ${STRUCTVIEW_OBJS}
)

#structures view unit tests
if ( KDE4_BUILD_TESTS )
#static lib for unit tests (reuse the OBJECT library)
kde4_add_library ( structures-static STATIC ${PODDECODER_OBJS} ${STRUCTVIEW_OBJS} )
target_link_libraries ( structures-static
  ${QT_QTCORE_LIBRARY}
  ${QT_QTSCRIPT_LIBRARY}
  ${QT_QTXML_LIBRARY}
  ${QT_QTTEST_LIBRARY}
  ${KDE4_KDEUI_LIBS}
  ${KDE4_KCMUTILS_LIBS}
  ${oktetakastencore_LIB}
  ${oktetakastengui_LIB}
  ${oktetacore_LIB}
  ${KASTENCORE_LIBS}
  #${KASTENGUI_LIBS}
)

set_target_properties( structures-static PROPERTIES COMPILE_FLAGS -DOKTETAKASTENCONTROLLERS_EXPORT=)

macro(structures_unit_test _testtarget _testname)
    #message("ARGC='${ARGC}' ARGV='${ARGV}' ARGN='${ARGN}'")
    kde4_add_unit_test(${_testtarget} TESTNAME ${_testname} ${ARGN})
    target_link_libraries(${_testtarget} LINK_PRIVATE structures-static )
endmacro()

structures_unit_test( primitivearraytest "structures-primitive-array" test/primitivearraytest.cpp )
structures_unit_test( arraydatainformationtest "structures-array-datainformation" test/arraydatainformationtest.cpp )
structures_unit_test( basicdatainformationtest "structures-basic-datainformation" test/basicdatainformationtest.cpp )
structures_unit_test( primitivedatainformationtest "structures-primitive-datainformation" test/primitivedatainformationtest.cpp )
structures_unit_test( scriptclassestest "structures-script-classes" test/scriptclassestest.cpp )
structures_unit_test( uniondatainformationtest "structures-union-datainformation" test/uniondatainformationtest.cpp )
structures_unit_test( allprimitivetypestest "structures-all-primitive-types" test/allprimitivetypestest.cpp )
structures_unit_test( scriptvalueconvertertest "structures-scriptvalue-converter" test/scriptvalueconvertertest.cpp )
structures_unit_test( osdparsertest "structures-osd-parser" test/osdparsertest.cpp )
structures_unit_test( commonparsertest "structures-common-parser" test/commonparsertest.cpp )
structures_unit_test( jsparsertest "structures-js-parser" test/jsparsertest.cpp )
structures_unit_test( customtostringtest "structures-custom-to-string" test/customtostringtest.cpp )
structures_unit_test( locktooffsettest "structures-lock-to-offset" test/locktooffsettest.cpp )
set_target_properties( jsparsertest customtostringtest PROPERTIES COMPILE_DEFINITIONS SRCDIR=\"${CMAKE_CURRENT_SOURCE_DIR}\" )

endif ( KDE4_BUILD_TESTS )

set( okteta_kastencontrollers_LIB_HDRS
  oktetakastencontrollers_export.h
  view/print/printcontroller.h
  view/bookmarks/bookmarkscontroller.h
  view/bookmarks/bookmarkstool.h
  view/bookmarks/bookmarkstoolview.h
  view/bookmarks/bookmarkstoolfactory.h
  view/bookmarks/bookmarkstoolviewfactory.h
  view/overwritemode/overwritemodecontroller.h
  view/poddecoder/poddata.h
  view/poddecoder/poddecodertool.h
  view/poddecoder/poddecodertoolview.h
  view/poddecoder/poddecodertoolfactory.h
  view/poddecoder/poddecodertoolviewfactory.h
  view/viewconfig/viewconfigcontroller.h
  view/gotooffset/gotooffsetcontroller.h
  view/gotooffset/gotooffsettool.h
  view/gotooffset/gotooffsettoolview.h
  view/viewmode/viewmodecontroller.h
  view/checksum/checksumtool.h
  view/checksum/checksumtoolview.h
  view/checksum/checksumtoolfactory.h
  view/checksum/checksumtoolviewfactory.h
  view/info/infotool.h
  view/info/infotoolview.h
  view/info/infotoolfactory.h
  view/info/infotoolviewfactory.h
  view/bytetable/bytetabletool.h
  view/bytetable/bytetabletoolview.h
  view/bytetable/bytetabletoolfactory.h
  view/bytetable/bytetabletoolviewfactory.h
  view/filter/filtertool.h
  view/filter/filtertoolview.h
  view/filter/filtertoolfactory.h
  view/filter/filtertoolviewfactory.h
  view/charsetconversion/charsetconversiontoolfactory.h
  view/charsetconversion/charsetconversiontoolviewfactory.h
  view/selectrange/selectrangecontroller.h
  view/libfinddialog/kfinddirection.h
  view/replace/replacecontroller.h
  view/replace/replaceuserqueryable.h
  view/viewstatus/viewstatuscontroller.h
  view/viewprofiles/viewprofilecontroller.h
  view/viewprofiles/viewprofilesmanagecontroller.h
  view/stringsextract/containedstring.h
  view/stringsextract/stringsextracttool.h
  view/stringsextract/stringsextracttoolview.h
  view/stringsextract/stringsextracttoolfactory.h
  view/stringsextract/stringsextracttoolviewfactory.h
  view/search/searchcontroller.h
  view/search/searchuserqueryable.h
# structtool.h cannot be installed as it pulls (too) many private uninstalled headers
# KF5 TODO: any tools/controllers and views should be created by the resp. factories
# since some time, no more directly.
# So on next ABI change depublish tools/controllers & their views
# For now keeping all installed, in case someone is using them still/already.
#   view/structures/structtool.h
  view/structures/structtoolview.h
  view/structures/structurestoolfactory.h
  view/structures/structurestoolviewfactory.h
  document/info/documentinfotoolview.h
  document/info/documentinfotool.h
  document/overwriteonly/overwriteonlycontroller.h
)

kde4_add_library( ${oktetakastencontrollers_LIB}  SHARED ${OKTETA_KASTEN_CONTROLLERS_SRCS} )

target_link_libraries( ${oktetakastencontrollers_LIB}
  ${oktetakastengui_LIB}
  ${oktetakastencore_LIB}
  ${KASTENGUI_LIBS}
  ${KASTENCORE_LIBS}
  ${oktetagui_LIB}
  ${oktetacore_LIB}
  ${KDE4_KIO_LIBS}
  ${KDE4_KDEUI_LIBS}
  ${KDE4_KCMUTILS_LIBS}
  ${QT_QTSCRIPT_LIBRARY}
  ${QT_QTSCRIPTTOOLS_LIBRARY}
)

set_target_properties( ${oktetakastencontrollers_LIB}  PROPERTIES
  OUTPUT_NAME ${oktetakastencontrollers_LIB_NAME}
  VERSION     ${OKTETAKASTEN_LIB_VERSION}
  SOVERSION   ${OKTETAKASTEN_LIB_SOVERSION}
)

install( TARGETS ${oktetakastencontrollers_LIB}  ${INSTALL_TARGETS_DEFAULT_ARGS} )

install( FILES ${okteta_kastencontrollers_LIB_HDRS}
  DESTINATION ${OKTETAKASTEN_INCLUDE_INSTALL_DIR}
  COMPONENT Devel
)
install( FILES view/structures/kns/okteta-structures.knsrc  DESTINATION  ${CONFIG_INSTALL_DIR} )

set( elf_structure_FILES
  view/structures/examples/okteta/structures/elf/metadata.desktop
  view/structures/examples/okteta/structures/elf/main.osd
)
install( FILES ${elf_structure_FILES}  DESTINATION  ${DATA_INSTALL_DIR}/okteta/structures/elf )

set( png_structure_FILES
  view/structures/examples/okteta/structures/png/metadata.desktop
  view/structures/examples/okteta/structures/png/main.osd
)
install( FILES ${png_structure_FILES}  DESTINATION  ${DATA_INSTALL_DIR}/okteta/structures/png )
install( FILES view/structures/examples/okteta/structures/uuid.js  DESTINATION  ${DATA_INSTALL_DIR}/okteta/structures/ )
install( FILES view/structures/settings/structviewpreferences.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )

configure_file( view/structures/struct2osd.sh.in ${CMAKE_CURRENT_BINARY_DIR}/struct2osd.sh @ONLY)
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/struct2osd.sh DESTINATION ${BIN_INSTALL_DIR} )
install( FILES view/structures/gccxml-to-osd.xsl DESTINATION ${DATA_INSTALL_DIR}/okteta/structures/ )


if( KASTEN_BUILD_INTERNAL_TEMPLATES )
include_directories(
  view/libbytearrayfilter/filter
  view/libbytearraychecksum/algorithm
)
set( libfilter_templates_SRCS
  view/libbytearrayfilter/filter/template/template_bytearrayfilter.cpp
  view/libbytearrayfilter/filter/template/template_bytearrayfilterparameterset.cpp
  view/libbytearrayfilter/filter/template/template_bytearrayfilterparametersetedit.cpp
)
set( libchecksum_templates_SRCS
  view/libbytearraychecksum/algorithm/template/template_bytearraychecksumalgorithm.cpp
  view/libbytearraychecksum/algorithm/template/template_bytearraychecksumparameterset.cpp
  view/libbytearraychecksum/algorithm/template/template_bytearraychecksumparametersetedit.cpp
)

set( okteta_kastencontrollers_templates_SRCS
  ${libfilter_templates_SRCS}
  ${libchecksum_templates_SRCS}
)

kde4_add_library( oktetakastencontrollertemplates  STATIC ${okteta_kastencontrollers_templates_SRCS} )

endif( KASTEN_BUILD_INTERNAL_TEMPLATES )
