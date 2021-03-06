/**	
 * \file            gsm_sms.c
 * \brief           SMS API
 */
 
/*
 * Copyright (c) 2018 Tilen Majerle
 *  
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of GSM-AT.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 */
#include "gsm/gsm_private.h"
#include "gsm/gsm_sms.h"
#include "gsm/gsm_mem.h"

#if GSM_CFG_SMS || __DOXYGEN__

/**
 * \brief           Send SMS text to phone number
 * \param[in]       num: String number
 * \param[in]       text: Text to send. Maximal 160 characters
 * \param[in]       blocking: Status whether command should be blocking or not
 * \return          \ref gsmOK on success, member of \ref gsmr_t otherwise
 */
gsmr_t
gsm_sms_send(const char* num, const char* text, uint32_t blocking) {
    GSM_MSG_VAR_DEFINE(msg);                    /* Define variable for message */

    GSM_MSG_VAR_ALLOC(msg);                     /* Allocate memory for variable */
    GSM_MSG_VAR_REF(msg).cmd_def = GSM_CMD_CMGS;
    GSM_MSG_VAR_REF(msg).cmd = GSM_CMD_CMGF;
    GSM_MSG_VAR_REF(msg).msg.sms_send.num = num;
    GSM_MSG_VAR_REF(msg).msg.sms_send.text = text;
    GSM_MSG_VAR_REF(msg).msg.sms_send.format = 1;   /* Send as plain text */

    return gsmi_send_msg_to_producer_mbox(&GSM_MSG_VAR_REF(msg), gsmi_initiate_cmd, blocking, 60000);   /* Send message to producer queue */
}

#endif /* GSM_CFG_SMS || __DOXYGEN__ */
