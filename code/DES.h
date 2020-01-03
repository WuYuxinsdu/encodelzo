#define DES_ENCRYPT     1
#define DES_DECRYPT     0

#define ERR_DES_INVALID_INPUT_LENGTH              -0x0002 /**< The data input has an invalid length. */

//#define MBEDTLS_DES_KEY_SIZE    8
#define DES_KEY_SIZE         (8)
#define DES3_KEY2_SIZE       (16)
#define DES3_KEY3_SIZE       (24)

#include <stdint.h>

typedef struct
{
    uint32_t sk[32];            /*!<  DES subkeys       */  //DES×ÓÃÜÔ¿
}des_context;

/**
 * \brief          Triple-DES context structure
 */
typedef struct
{
    uint32_t sk[96];            /*!<  3DES subkeys      */   //3DES×ÓÃÜÔ¿
}des3_context;
