cmake_minimum_required(VERSION 3.24)
project(cli-gpt)

include_directories("lib/openai/include/openai")
include_directories(/usr/local/opt/curl/include/)

set(CMAKE_CXX_STANDARD 23)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)


add_executable(cli-gpt main.cpp)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(cli-gpt ${CURL_LIBRARIES})
install(TARGETS cli-gpt DESTINATION /usr/local/bin)