cmake_minimum_required(VERSION 2.8.9)

set(PROJECTNAME force-reconstruction)
project(${PROJECTNAME})

find_package(YARP REQUIRED)
find_package(Gurls REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${ICUB_MODULE_PATH})
include(YarpInstallationHelpers)

find_package(ICUBcontrib)
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})
include(ICUBcontribHelpers)
include(ICUBcontribOptions)
icubcontrib_set_default_prefix()


include_directories(${YARP_INCLUDE_DIRS} ${Gurls_INCLUDE_DIRS} )

add_definitions(${YARP_DEFINES}) # add yarp definitions - this contains also -D_REENTRANT

# Search for application files
file(GLOB APP_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/applications/*.xml)
# Search for ini files
file(GLOB APP_CONF
                ${CMAKE_CURRENT_SOURCE_DIR}/contexts/${PROJECTNAME}/*.ini
                ${CMAKE_CURRENT_SOURCE_DIR}/contexts/${PROJECTNAME}/*.xml)


yarp_install(FILES ${APP_SCRIPTS} DESTINATION ${ICUBCONTRIB_APPLICATIONS_INSTALL_DIR})
yarp_install(FILES ${APP_CONF} DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${PROJECTNAME})


icubcontrib_add_uninstall_target()


set(HEADERS src/forcereconstruction.h )

set(SOURCES  src/main.cpp src/forcereconstruction.cpp ${HEADERS})

set( CMAKE_BUILD_TYPE Debug CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel." FORCE )




add_executable(${PROJECTNAME} ${SOURCES})

target_link_libraries(${PROJECTNAME} ${YARP_LIBRARIES} ${Gurls_LIBRARIES})

install(TARGETS ${PROJECTNAME} DESTINATION bin)

# Figure it out later
install(DIRECTORY ./contexts/
  DESTINATION share/ICUBcontrib/contexts/${PROJECTNAME})










	
