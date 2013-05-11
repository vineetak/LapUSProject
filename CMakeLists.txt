#
# $Id: vkhatuj1$
#
# (C) Copyright 2006-2011 Johns Hopkins University (JHU), All Rights
# Reserved.
#
# --- begin cisst license - do not edit ---
#
# This software is provided "as is" under an open source license, with
# no warranty.  The complete license can be found in license.txt and
# http://www.cisst.org/cisst/license.txt.
#
# --- end cisst license ---

cmake_minimum_required (VERSION 2.8)

project(LapUS)

# Find packages #

find_package (cisst REQUIRED)
find_package(Qt4 REQUIRED)
find_package(sawIntuitiveDaVinci)


include(${CISST_USE_FILE} ${QT_USE_FILE})


include_directories(${sawIntuitiveDaVinci_INCLUDE_DIR})
		
LINK_DIRECTORIES(${sawIntuitiveDaVinci_LIBRARY_DIR})

SET(LapUS_CPP LapUSMainWindow.cpp BrowserWidget.cpp PreopViewer.cpp USViewer.cpp LapUSUtil.cpp USBrowserListItem.cpp  LapUSMouse.cpp USBrowserList.cpp QsKineticScroller.cpp)
SET(LapUS_H LapUSMainWindow.h BrowserWidget.h PreopViewer.h USViewer.h LapUSUtil.h USBrowserListItem.h  LapUSMouse.h LapUSCallBacks.h LapUSCallBackSignals.h USBrowserList.h QsKineticScroller.h)
 
qt4_wrap_cpp(QT_CPP ${LapUS_H})

#include(LapUSMainWindow.h)
#qt4_wrap_cpp(QT_CPP_DV ${LapUS_H_DV})


add_executable (main_w_davinci main.cpp  ${LapUS_CPP} ${LapUS_H} ${QT_CPP})


target_link_libraries(main_w_davinci ${sawIntuitiveDaVinci_LIBRARIES} ${QT_LIBRARIES})

cisst_target_link_libraries (main_w_davinci cisstCommon cisstVector cisstOSAbstraction cisstMultiTask cisstStereoVision cisstQt cisstStereoVisionQt cisstParameterTypes)
#cisst_target_link_libraries (main_w_davinci cisstCommon cisstVector cisstOSAbstraction cisstMultiTask cisstStereoVision cisstQt cisstParameterTypes)
