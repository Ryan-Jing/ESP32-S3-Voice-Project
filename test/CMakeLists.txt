cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS main ../include)

set(SDKCONFIG_DEFAULTS
    "../config/sdkconfig.defaults"
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(test)
