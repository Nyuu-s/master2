/*!**********************************************************************
    2  *
    3  * @copyright Copyright (C) 2016 Siemens Aktiengesellschaft.\n
    4  *            All rights reserved.
    5  *
    6  *************************************************************************
    7  *
    8  * @file     definitions.h
    9  * @date     Jul 28, 2016
   10  * @brief    Definitions module header file.
   11  *
   12  * General definitions are stored in this header file.
   13  *
   14  ************************************************************************/
   15 
   16 #ifndef DEFINITIONS_H_
   17 #define DEFINITIONS_H_
   18 
   19 // MAX value of an mcl_size_t can have :
   20 // The expression below is portable and safe.
   21 #define MCL_SIZE_MAX ((mcl_size_t) - 1)
   22 
   23 // MCL_NULL Definition. Refer to C-FAQ Q5.2 - Q5.17 (http://c-faq.com/null/safermacs.html):
   24 #define MCL_NULL ((void *)0)
   25 
   26 #define MCL_NULL_CHAR '\0'
   27 #define MCL_NULL_CHAR_SIZE 1
   28 
   29 #define NONCE_SIZE 16
   30 
   31 // TODO: version size assumed 36 instead of 255 like in document and DEFAULT_ID_SIZE is used. Change later after deciding.
   32 // These sizes come from "Interface Specification MindConnect API V 0.1". Sizes increased by 1 for null termination.
   33 #define DEFAULT_META_TYPE_SIZE                  6
   34 #define DEFAULT_PAYLOAD_TYPE_SIZE               20
   35 #define DEFAULT_QUALITY_CODE_SIZE               9
   36 #define DEFAULT_DATE_SIZE                       23
   37 #define DEFAULT_TIMESTAMP_SIZE                  25
   38 #define DEFAULT_ID_SIZE                         37
   39 #define DEFAULT_VALUES_COUNT                    5
   40 
   41 // TODO: value size is 255 in document. if char [255] -> unnecessary memory use:
   42 #define DEFAULT_VALUE_SIZE                      11
   43 
   44 #define MAXIMUM_HOST_NAME_LENGTH           256
   45 #define MAXIMUM_PROXY_USER_NAME_LENGTH     32
   46 #define MAXIMUM_PROXY_PASSWORD_LENGTH      32
   47 #define MAXIMUM_PROXY_DOMAIN_LENGTH        256
   48 #define MAXIMUM_USER_AGENT_LENGTH          512
   49 
   50 // The practical minimum is about 400 bytes since libcurl uses a buffer of this size as a scratch area.
   51 #define MIN_HTTP_PAYLOAD_SIZE 400
   52 
   53 // 16K is default payload size for libcurl since it performs better with this value.
   54 #define DEFAULT_HTTP_PAYLOAD_SIZE 16384
   55 
   56 // 300 seconds is default http request timeout value.
   57 #define DEFAULT_HTTP_REQUEST_TIMEOUT (300)
   58 
   59 // JWT used in authorization header has an expiration time of 24 hours.
   60 #define JWT_EXPIRATION_TIME 86400
   61 
   62 #define MCL_FILE_EXCHANGE_ENABLED 1
   63 
   64 #define MCL_ERROR_RETURN_POINTER(return_value, ...) \
   65     MCL_ERROR(__VA_ARGS__); \
   66     DEBUG_LEAVE("retVal = <%p>", (return_value)); \
   67     return (return_value);
   68 
   69 #define MCL_ERROR_RETURN(return_value, ...) \
   70     MCL_ERROR(__VA_ARGS__); \
   71     DEBUG_LEAVE("retVal = <%d>", (return_value)); \
   72     return (return_value);
   73 
   74 #define ASSERT(condition) \
   75     if(!(condition)) \
   76     { \
   77         MCL_ERROR_STRING("Assertion failed for condition = <" #condition ">."); \
   78         DEBUG_LEAVE("retVal = <%p>", MCL_NULL); \
   79         return MCL_NULL; \
   80     }
   81 
   82 #define ASSERT_MESSAGE(condition, ...) \
   83     if(!(condition)) \
   84     { \
   85         MCL_ERROR_STRING("Assertion failed for condition = <" #condition ">."); \
   86         MCL_ERROR_RETURN_POINTER(MCL_NULL, __VA_ARGS__); \
   87     }
   88 
   89 #define ASSERT_STATEMENT_MESSAGE(condition, statement, ...) \
   90     if(!(condition)) \
   91     { \
   92         MCL_ERROR_STRING("Assertion failed for condition = <" #condition ">."); \
   93         (statement); \
   94         MCL_ERROR_RETURN_POINTER(MCL_NULL, __VA_ARGS__); \
   95     }
   96 
   97 #define ASSERT_CODE(condition, return_code) \
   98     if(!(condition)) \
   99     { \
  100         MCL_ERROR_STRING("Assertion failed for condition = <" #condition ">."); \
  101         DEBUG_LEAVE("retVal = <%d>", (return_code)); \
  102         return (return_code); \
  103     }
  104 
  105 #define ASSERT_CODE_MESSAGE(condition, return_code, ...) \
  106     if(!(condition)) \
  107     { \
  108         MCL_ERROR_STRING("Assertion failed for condition = <" #condition ">."); \
  109         MCL_ERROR_RETURN(return_code, __VA_ARGS__); \
  110     }
  111 
  112 #define ASSERT_STATEMENT_CODE(condition, statement, return_code) \
  113     if(!(condition)) \
  114     { \
  115         MCL_ERROR_STRING("Assertion failed for condition = <" #condition ">."); \
  116         (statement); \
  117         DEBUG_LEAVE("retVal = <%d>", (return_code)); \
  118         return (return_code); \
  119     }
  120 
  121 #define ASSERT_STATEMENT_CODE_MESSAGE(condition, statement, return_code, ...) \
  122     if(!(condition)) \
  123     { \
  124         MCL_ERROR_STRING("Assertion failed for condition = <" #condition ">."); \
  125         (statement); \
  126         MCL_ERROR_RETURN(return_code, __VA_ARGS__); \
  127     }
  128 
  129 #define ASSERT_NOT_NULL(argument) \
  130     if(MCL_NULL == argument) \
  131     { \
  132         MCL_ERROR_RETURN(MCL_TRIGGERED_WITH_NULL, "Null function argument (" #argument ")."); \
  133     }
  134 
  135 #define STRING_CONSTANT(s) {s, sizeof(s)/sizeof(s[0]) - 1, MCL_STRING_NOT_COPY_NOT_DESTROY}
  136 
  137 #endif //DEFINITIONS_H_
