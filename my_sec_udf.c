#ifdef STANDARD
/* STANDARD is defined, don't use any mysql functions */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong;/* Microsofts 64 bit types */
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif /*__WIN__*/
#else
#include <my_global.h>
#include <my_sys.h>
#if defined(MYSQL_SERVER)
#include <m_string.h>/* To get strmov() */
#else
/* when compiled as standalone */
#include <string.h>
#define strmov(a,b) stpcpy(a,b)
#define bzero(a,b) memset(a,0,b)
#define memcpy_fixed(a,b,c) memcpy(a,b,c)
#endif
#endif
#include <mysql.h>
#include <ctype.h>
   
#ifdef HAVE_DLOPEN
   
#if !defined(HAVE_GETHOSTBYADDR_R) || !defined(HAVE_SOLARIS_STYLE_GETHOST)
static pthread_mutex_t LOCK_hostname;
#endif
   
#include <math.h>  

my_bool my_sec_udf_init(UDF_INIT* initid, UDF_ARGS* args, char* message);
void my_sec_udf_deinit(UDF_INIT *initid);
char *my_sec_udf(UDF_INIT* initid, UDF_ARGS* args, char* result,
	unsigned long* length, char* is_null, char* error);

	my_bool my_sec_udf_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
	{
   		if(!(args->arg_count == 1)) {
    		strcpy(message, "Input is expected to be a number of seconds, type INT");
    		return 1;
		}
		if(args->args[0] == NULL) {
			strcpy(message, "Input is expected to be a number of seconds, type INT");
			return 1;
		}
		if(!(args->arg_type[0] == INT_RESULT)) {
			strcpy(message, "Input is expected to be a number of seconds, type INT");
			return 1;
		}
 
 		args->arg_type[0] = INT_RESULT;
    	initid->max_length= 255; 
    	return 0;
	}

	void my_sec_udf_deinit(UDF_INIT *initid __attribute__((unused)))
	{
   	
	}

	char *my_sec_udf(UDF_INIT* initid, UDF_ARGS* args, char* result,
		unsigned long* length, char* is_null, char* error)
	{
   	 	longlong seconds = *((longlong*)(args->args[0]));
   	 	char str[255];
    	int hour = (seconds / 60) / 60;
    	int minute = (seconds / 60) % 60;
    	int second = (seconds % 60) % 60;
    
    	snprintf(str, 255, "h: %d, m: %d, s: %d", hour, minute, second);
    	*length = strlen(str);
    	memcpy(result, str, strlen(str));
    	return result; 
}

#endif /* HAVE_DLOPEN */