cmake_minimum_required(VERSION 3.19)
include(FetchContent)
 set(DOWNLOAD_URL https://github.com/USCiLab/cereal/archive/refs/tags/v${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION}.tar.gz)
#set(DOWNLOAD_URL https://github.com/randombit/botan/archive/refs/tags/3.0.0.tar.gz)

file(
        DOWNLOAD
        ${DOWNLOAD_URL}
        STATUS download_status
)
if (NOT download_status EQUAL 0)
    message(FATAL_ERROR "Could not download Cereal tarball (status = ${download_status}): ${DOWNLOAD_URL}")
endif()

# Download the tarball
FetchContent_Declare(
        Cereal_upstream
        URL ${DOWNLOAD_URL}
        DOWNLOAD_EXTRACT_TIMESTAMP true
)

set(cereal_upstream_SKIP_PERFORMANCE_COMPARISON ON CACHE INTERNAL "")
set(cereal_upstream_SKIP_PERFORMANCE_COMPARISON ON CACHE INTERNAL "")
FETCHCONTENT_POPULATE(Cereal_upstream)


# Create target
add_library(cereal INTERFACE)

message(${cereal_upstream_SOURCE_DIR})

target_include_directories(
        cereal
        INTERFACE
        ${cereal_upstream_SOURCE_DIR}/include
)
