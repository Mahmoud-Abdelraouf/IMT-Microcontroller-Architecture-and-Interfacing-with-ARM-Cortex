/**
 * @file UART_interface.h
 * @brief Interface file for the UART driver.
 * @date 19 Jul 2023
 * @version V01
 * 
 * @details This file contains the function prototypes and definitions for the UART driver.
 * 
 * @author Mahmoud Abdelraouf Mahmoud
 * 
 * @see Some_Reference_to_Other_Code
 * 
 * @note This module requires the STM32Fxx microcontroller.
 * 
 * @attention Pay attention to some specific details.
 * 
 * @bug Known bug: The function XYZ does not handle edge cases properly.
 * 
 * @warning Be cautious when using this module.
 * 
 * @todo Implement the additional functionality.
 * 
 * @deprecated This module is deprecated and will be replaced in future versions.
 * 
 * @remarks Some additional remarks.
 * 
 * @defgroup UART_Driver UART Driver
 * @{
 */

#ifndef __UART_INTERFACE_H__
#define __UART_INTERFACE_H__

/**
 * @addtogroup UART_Configuration_Options
 * @{
 */

/**
 * @brief Enumeration for UART parity modes.
 *
 * This enumeration defines the possible parity modes for the UART driver.
 * PARITY_NONE: No parity bit is used.
 * PARITY_EVEN: Even parity is used.
 * PARITY_ODD: Odd parity is used.
 */
typedef enum
{
  UART_PARITY_NONE,  /**< No parity bit is used */
  UART_PARITY_EVEN,  /**< Even parity is used */
  UART_PARITY_ODD    /**< Odd parity is used */
} UART_Parity_t;

/**
 * @brief Enumeration for UART stop bit modes.
 *
 * This enumeration defines the possible stop bit modes for the UART driver.
 * STOP_BITS_1: 1 stop bit is used.
 * STOP_BITS_2: 2 stop bits are used.
 */
typedef enum
{
  UART_STOP_BITS_1,     /**< 1 stop bit is used */
  UART_STOP_BITS_2,     /**< 2 stop bits are used */
  UART_STOP_BITS_0_5,   /**< 0.5 stop bit is used */
  UART_STOP_BITS_1_5    /**< 1.5 stop bits are used */
} UART_StopBits_t;

/**
 * @brief Enumeration for UART data word lengths.
 *
 * This enumeration defines the possible data word lengths for the UART driver.
 * DATA_BITS_8: 8 data bits are used.
 * DATA_BITS_9: 9 data bits are used.
 */
typedef enum
{
  UART_WORD_LENGTH_8BIT,  /**< 8 data bits are used */
  UART_WORD_LENGTH_9BIT   /**< 9 data bits are used */
} UART_DataBits_t;

/**
 * @brief Enumeration for UART baud rate options.
 *
 * This enumeration defines the possible baud rate options for the UART driver.
 * BAUD_RATE_9600: Baud rate of 9600.
 * BAUD_RATE_115200: Baud rate of 115200.
 * BAUD_RATE_57600: Baud rate of 57600.
 * BAUD_RATE_38400: Baud rate of 38400.
 */
typedef enum
{
  BAUD_RATE_9600,     /**< Baud rate of 9600 */
  BAUD_RATE_115200,   /**< Baud rate of 115200 */
  BAUD_RATE_57600,    /**< Baud rate of 57600 */
  BAUD_RATE_38400     /**< Baud rate of 38400 */
} UART_BaudRate_t;

/**
 * @brief Enumeration of UART hardware flow control options.
 *
 * This enumeration defines the possible hardware flow control options that can be used in UART communication.
 * Hardware flow control helps manage the flow of data between the sender and receiver to prevent data overrun or loss.
 * The options include:
 *
 * - UART_HW_FLOW_CONTROL_NONE: No hardware flow control. Data transmission is not controlled by additional signals.
 * - UART_HW_FLOW_CONTROL_RTS: Request to Send (RTS) hardware flow control. The transmitter asserts the RTS signal
 *   to indicate that it is ready to send data, and the receiver uses RTS as an indication that it can receive data.
 *   Data transmission occurs only when RTS is asserted.
 * - UART_HW_FLOW_CONTROL_CTS: Clear to Send (CTS) hardware flow control. The receiver asserts the CTS signal to
 *   indicate that it is ready to accept data, and the transmitter uses CTS as an indication that it can start
 *   transmitting data. Data transmission occurs only when CTS is asserted.
 * - UART_HW_FLOW_CONTROL_RTS_CTS: RTS and CTS hardware flow control. Both RTS and CTS signals are used for flow control,
 *   allowing bidirectional control of data transmission. The transmitter uses RTS to indicate readiness, and the receiver
 *   uses CTS to indicate readiness to receive data.
 *
 * @note RTS (Request to Send): RTS is an output signal generated by the data sender (transmitter) to the data receiver.
 * When the transmitter has data to send and is ready to transmit, it asserts the RTS signal to inform the receiver
 * that it is ready to send data. The receiver uses the RTS signal as an indication that it can receive data.
 * Data transmission occurs only when the RTS signal is asserted.
 *
 * @note CTS (Clear to Send): CTS is an input signal generated by the data receiver to the data sender (transmitter).
 * When the receiver is ready to receive data, it asserts the CTS signal to inform the transmitter that it is ready
 * to accept data. The transmitter uses the CTS signal as an indication that it can start transmitting data.
 * Data transmission occurs only when the CTS signal is asserted.
 */
typedef enum
{
    UART_HW_FLOW_CONTROL_NONE,   /**< No hardware flow control */
    UART_HW_FLOW_CONTROL_RTS,    /**< Request to Send (RTS) hardware flow control */
    UART_HW_FLOW_CONTROL_CTS,    /**< Clear to Send (CTS) hardware flow control */
    UART_HW_FLOW_CONTROL_RTS_CTS /**< RTS and CTS hardware flow control */
} UART_HW_FlowControl_t;

typedef struct 
{
   u8 HwFlowControl:2;
   u8 ParityMode:2;
   u8 BaudRate:2;
   u8 StopBits:2;
   u8 WordLength:1;
}UART_Config_t;

/**
 * @}
 */

/**
 * @addtogroup UART_Functions
 * @{
 */

/**
 * @brief Get the base address of the specified USART peripheral.
 *
 * This function returns the base address of the specified USART peripheral.
 *
 * @param[in] usart The USART peripheral to get the base address for. Must be one of the following:
 *                      - USART1
 *                      - USART2
 *                      - USART3
 *
 * @return The base address of the specified USART peripheral.
 *
 * @note Example Usage:
 * @code
 * /**< Choose the USART peripheral you want to use (in this case, USART1)
 * USART_Selection_t usart_selected = USART1;
 *
 * /**< Get the base address of USART1 using the UART_GetUSARTBaseAddress function
 * USART_RegDef_t *usart1 = GetUSARTBaseAddress(usart_selected);
 *
 * /**< Now you can access USART1 registers and configure the UART communication
 * /**< For example, you can configure the baud rate, word length, stop bits, etc.
 *
 * /**< ... (add your UART configuration code here)
 * @endcode
 */
inline USART_RegDef_t *UART_GetUSARTBaseAddress(USART_Selection_t usart);

/**
 * @brief Configure the UART peripheral.
 *
 * This function configures the UART peripheral with the specified options.
 *
 * @param[in] Copy_psUSART Pointer to the USART peripheral structure. Must point to one of the following:
 *                           - USART1: Pointer to the USART1 peripheral structure.
 *                           - USART2: Pointer to the USART2 peripheral structure.
 *                           - USART3: Pointer to the USART3 peripheral structure.
 * @param[in] config Pointer to the UART configuration structure that holds the configuration options.
 *                   The structure must contain the following fields:
 *                   - HwFlowControl: The hardware flow control option to use. Must be one of the following:
 *                                     - UART_HW_FLOW_CONTROL_NONE: No hardware flow control.
 *                                     - UART_HW_FLOW_CONTROL_RTS: Request to Send (RTS) hardware flow control.
 *                                     - UART_HW_FLOW_CONTROL_CTS: Clear to Send (CTS) hardware flow control.
 *                                     - UART_HW_FLOW_CONTROL_RTS_CTS: RTS and CTS hardware flow control.
 *                   - ParityMode: The parity mode to use. Must be one of the following:
*                                      - UART_PARITY_NONE: No parity bit is used.
*                                      - UART_PARITY_EVEN: Even parity is used.
*                                      - UART_PARITY_ODD: Odd parity is used.
 *                   - BaudRate: The baud rate option to use. Must be one of the following:
*                                      - BAUD_RATE_9600: Baud rate of 9600.
*                                      - BAUD_RATE_115200: Baud rate of 115200.
*                                      - BAUD_RATE_57600: Baud rate of 57600.
*                                      - BAUD_RATE_38400: Baud rate of 38400.
 *                   - StopBits: The stop bit mode to use. Must be one of the following:
*                                      - UART_STOP_BITS_1: 1 stop bit is used.
*                                      - UART_STOP_BITS_2: 2 stop bits are used.
*                                      - UART_STOP_BITS_0_5: 0.5 stop bit is used.
*                                      - UART_STOP_BITS_1_5: 1.5 stop bits are used.
 *                   - WordLength: The data word length to use. Must be one of the following:
*                                      - UART_WORD_LENGTH_8BIT: 8 data bits are used.
*                                      - UART_WORD_LENGTH_9BIT: 9 data bits are used.
 *
 * @retval None
 *
 * @note Example Usage:
 * @code
 * /**< Choose the USART peripheral you want to use (in this case, USART1)
 * USART_RegDef_t *usart_selected = USART1;
 *
 * /**< Create a UART configuration structure and set the desired options
 * UART_Config_t uart_config;
 * uart_config.HwFlowControl = UART_HW_FLOW_CONTROL_NONE;
 * uart_config.ParityMode = UART_PARITY_NONE;
 * uart_config.BaudRate = BAUD_RATE_115200;
 * uart_config.StopBits = UART_STOP_BITS_1;
 * uart_config.WordLength = UART_WORD_LENGTH_8BIT;
 *
 * /**< Configure the UART peripheral using the UART_voidInit function
 * UART_voidInit(usart_selected, &uart_config);
 *
 * /**< Now the UART peripheral is configured and ready to use for communication.
 * @endcode
 */
void UART_voidInit(USART_RegDef_t *Copy_psUSART, UART_Config_t *config);

/**
 * @brief Send data over UART.
 *
 * This function sends data over UART.
 *
 * @param[in] data The data to send.
 *
 * @retval None
 */
void UART_voidSendData(u8 data);

/**
 * @brief Receive data over UART.
 *
 * This function receives data over UART.
 *
 * @return The received data.
 */
u8 UART_u8ReceiveData(void);

/**
 * @}
 */

#endif /* __UART_INTERFACE_H__ */

/**
 * @}
 */