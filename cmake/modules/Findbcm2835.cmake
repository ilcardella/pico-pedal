
# Build and install the bcm2835 library

set(BCM2835_REPO_PATH "/opt/bcm2835-1.69")
set(BCM2835_INSTALL_PATH "/usr/local")

# FIXME: The commented code below allows build and installation of the library
# at CMake "configure time". The benefit is that the library is built with the same
# toolchain used for the project itself. Currently this requires sudo permissions
# for the installation so it fails due to the build running in a Docker container
# with the current user IDs

# execute_process(COMMAND ./configure -host=arm -prefix=${BCM2835_INSTALL_PATH} CC=${CMAKE_C_COMPILER}
#                 WORKING_DIRECTORY ${BCM2835_REPO_PATH}
#                 RESULT_VARIABLE BCM2835_CONFIGURE_RESULT)
# if(NOT BCM2835_CONFIGURE_RESULT EQUAL "0")
#     message(FATAL_ERROR "bcm2835 configuration failed with: ${BCM2835_CONFIGURE_RESULT}")
# endif()

# execute_process(COMMAND make
#                 WORKING_DIRECTORY ${BCM2835_REPO_PATH}
#                 RESULT_VARIABLE BCM2835_INSTALL_RESULT)
# if(NOT BCM2835_INSTALL_RESULT EQUAL "0")
#     message(FATAL_ERROR "bcm2835 make failed with: ${BCM2835_MAKE_RESULT}")
# endif()

# execute_process(COMMAND make install
#                 WORKING_DIRECTORY ${BCM2835_REPO_PATH}
#                 RESULT_VARIABLE BCM2835_INSTALL_RESULT)
# if(NOT BCM2835_INSTALL_RESULT EQUAL "0")
#     message(FATAL_ERROR "bcm2835 installation failed with: ${BCM2835_INSTALL_RESULT}")
# endif()

# Configure a target for the library and make it findable

find_library(BCM2835_LIBRARY
              NAMES bcm2835 libbcm2835
              HINTS "${BCM2835_INSTALL_PATH}/lib")

find_path(BCM2835_INCLUDE_DIR
              NAMES bcm2835.h
              HINTS "${BCM2835_INSTALL_PATH}/include")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(bcm2835 DEFAULT_MSG
                                  BCM2835_LIBRARY
                                  BCM2835_INCLUDE_DIR)

mark_as_advanced(BCM2835_LIBRARY BCM2835_INCLUDE_DIR)

if(BCM2835_FOUND AND NOT TARGET bcm2835::bcm2835)
  add_library(bcm2835::bcm2835 STATIC IMPORTED)
  set_target_properties(
    bcm2835::bcm2835
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${BCM2835_INCLUDE_DIR}"
      IMPORTED_LOCATION ${BCM2835_LIBRARY})
endif()
