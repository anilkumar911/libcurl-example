#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>

#define URL_SZ 256
#define BUF_SZ 10*1024

//long written = 0;

static int receive( void* buffer, size_t length, size_t size, void* data ) {
    size_t l = length * size;
    printf("l=%d\n", l);

    int *written = (int*)data;

    if ( l > 0 ) {
        if ( *written + l >= BUF_SZ ) {
            fprintf( stderr, "Buffer size exceeded.\n" );
            return 0;
        }
        memcpy( &( (char*) data )[ (*written) + sizeof(*written) ], buffer, l );
        (*written) += l;
        printf("%s\n", data);
    }

    return l;
}

int main( int argc, char** argv ) {
	int r = -1;
    char url[ URL_SZ ];
    char data[ BUF_SZ ];
  //written = 0;

    memset( url, 0, sizeof( url ) );
    memset( data, 0, BUF_SZ );

    sprintf( url, "%s%s", "http://localhost:8080", "/testapi");

	CURL* c = curl_easy_init();
	if ( ! c ) {
		return 1;
	}

	curl_easy_setopt( c, CURLOPT_URL, url );
	curl_easy_setopt( c, CURLOPT_WRITEFUNCTION, receive );
	curl_easy_setopt( c, CURLOPT_NOPROGRESS, 1 );
	curl_easy_setopt( c, CURLOPT_FAILONERROR, 1 );
	curl_easy_setopt( c, CURLOPT_WRITEDATA, data );
	curl_easy_setopt( c, CURLOPT_FOLLOWLOCATION, 1 );
	curl_easy_setopt( c, CURLOPT_TIMEOUT, 10 );

	r = curl_easy_perform( c );
	curl_easy_cleanup( c );
    if ( r != 0 ) {
        fprintf( stderr, "Curl Error: %d\n", r );
        return r;
    }

		printf("=====>%s<====\n", data+sizeof(int));

    return r;
}
