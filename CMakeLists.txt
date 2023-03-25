cmake_minimum_required(VERSION 3.24)
project(cli-gpt)

include_directories("lib/openai/include/openai")

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
add_executable(cli-gpt main.cpp)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(cli-gpt ${CURL_LIBRARIES})


if(APPLE)
    install(TARGETS cli-gpt DESTINATION /usr/local/bin)
elseif(UNIX)
    install(TARGETS cli-gpt DESTINATION /usr/bin/)
endif()