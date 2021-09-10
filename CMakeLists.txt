# cmake 
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.13)

IF (POLICY CMP0043)
   CMAKE_POLICY(SET CMP0043 NEW)
ENDIF (POLICY CMP0043)

PROJECT(QBUDGETBOOK)

#########################################################################################
# cmake sets
SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin" CACHE PATH "ExecutablePath")
SET(CMAKE_CXX_FLAGS "-O3 -Wall -pedantic -Wno-deprecated-declarations -Wno-dev -Wno-long-long -static-libgcc -static-libstdc++ -std=gnu++14" CACHE PATH "compiler flags" FORCE)
set(CMAKE_CXX_STANDARD 14)
#########################################################################################
# Tell CMake to run moc when necessary:
SET(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake to always look for includes there:
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# using Qt5 package
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
#########################################################################################
SET(QT_VERSION "${Qt5Core_VERSION}")
MESSAGE(STATUS "Version Qt " ${QT_VERSION} " GCC " ${GCC_VERSION})
MESSAGE(STATUS "Source " ${CMAKE_SOURCE_DIR})
#########################################################################################
# search directories WINDOWS
IF (CMAKE_HOST_WIN32)
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_BINARY_DIR}    
    ${QBUDGETBOOK_SOURCE_DIR}/src
    ${QBUDGETBOOK_SOURCE_DIR}/src/model
    ${QBUDGETBOOK_SOURCE_DIR}/src/gui/dialog
    ${QBUDGETBOOK_SOURCE_DIR}/src/gui/widget
    C:/Qt/Tools/mingw730_32/opt/include
    )
LINK_DIRECTORIES(
    C:/Qt/Tools/mingw730_32/opt/lib
    )    
ENDIF (CMAKE_HOST_WIN32)

# search directories LINUX
IF (CMAKE_HOST_UNIX)
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${QBUDGETBOOK}/include
    )
LINK_DIRECTORIES(
    ${QBUDGETBOOK}/lib
    )
ENDIF (CMAKE_HOST_UNIX)
#########################################################################################

# resource files like images
SET(SRC_RESOURCES_QBUDGETBOOK
    QBudgetBook.qrc
)

# user interface source
SET(SRC_UI_QBUDGETBOOK
   src/gui/widget/QBudgetBookMainWindow.ui
   src/gui/dialog/BookingDialog.ui
)
        
# usually C/C++ source files        
SET(SRC_BIN_QBUDGETBOOK
    src/main.cpp
    src/model/BookingModel.cpp
    src/gui/widget/QBudgetBookMainWindow.cpp
    src/gui/dialog/BookingDialog.cpp
)

# convert user interfaces to source code
QT5_WRAP_UI(SRC_FORMS_QBUDGETBOOK     ${SRC_UI_QBUDGETBOOK})

# integrate resources
QT5_ADD_RESOURCES(SRC_RCC_QBUDGETBOOK ${SRC_RESOURCES_QBUDGETBOOK})

# set the library 
IF (CMAKE_HOST_WIN32)
    SET(imagehlp imagehlp.lib)
ELSE (CMAKE_HOST_WIN32)
    SET(imagehlp "")
ENDIF (CMAKE_HOST_WIN32)

## compile everything

ADD_EXECUTABLE(QBudgetBook ${SRC_BIN_QBUDGETBOOK} ${SRC_RCC_QBUDGETBOOK} ${SRC_FORMS_QBUDGETBOOK})
QT5_USE_MODULES(QBudgetBook Widgets)
TARGET_LINK_LIBRARIES(QBudgetBook ${imagehlp})
