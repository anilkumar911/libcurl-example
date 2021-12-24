#The extra -I and -L are needed to use custom built curl
gcc -I ${CURL_DIR}/include/ -g -o curlTest curlTest.c -lcurl -L${CURL_DIR}/lib/.libs/

#To use curl installed on system
gcc -g -o curlTest curlTest.c -lcurl
