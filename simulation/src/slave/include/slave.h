#ifndef RTW_HEADER_slave_h_
#define RTW_HEADER_slave_h_
#include "rtwtypes.h"
#include <stddef.h>
#ifndef slave_COMMON_INCLUDES_
# define slave_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* slave_COMMON_INCLUDES_ */

/* Model Code Variants */
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#define slave_M                        (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_SlaveCommand_
#define DEFINED_TYPEDEF_FOR_SlaveCommand_

typedef enum {
    SLAVE_IDLE = 0,                    /* Default value */
    SLAVE_PUT,
    SLAVE_READ,
    SLAVE_IGNORE
} SlaveCommand;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Operation_
#define DEFINED_TYPEDEF_FOR_Operation_

typedef enum {
    OPERATION_READ = 1,                /* Default value */
    OPERATION_WRITE = 0
} Operation;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Log_
#define DEFINED_TYPEDEF_FOR_Log_

typedef enum {
    LOG_NOTHING = 0,                   /* Default value */
    LOG_SEND,
    LOG_RECEIVE,
    LOG_REPLY,
    LOG_BUTTON_PRESSED,
    LOG_RETRIEVE_STATE
} Log;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
    uint8_T button_old[8];             /* '<S1>/slave_chart' */
    uint8_T is_active_c1_slave;        /* '<S1>/slave_chart' */
    uint8_T is_c1_slave;               /* '<S1>/slave_chart' */
    uint8_T idle_clocks;               /* '<S1>/slave_chart' */
    boolean_T from_wait_bus;           /* '<S1>/slave_chart' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
    uint8_T received_data;             /* '<Root>/received_data' */
    boolean_T data_available;          /* '<Root>/data_available' */
    uint8_T physical_address;          /* '<Root>/physical_address' */
    uint8_T button[8];                 /* '<Root>/button' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
    Operation register_operation;      /* '<Root>/register_operation' */
    SlaveCommand command;              /* '<Root>/command' */
    uint8_T put_data;                  /* '<Root>/put_data' */
    uint8_T leds[8];                   /* '<Root>/leds' */
    Log log_type;                      /* '<Root>/log_type' */
    uint8_T log_data[3];               /* '<Root>/log_data' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
    const char_T *errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void slave_initialize(void);
extern void slave_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

#endif                                 /* RTW_HEADER_slave_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
