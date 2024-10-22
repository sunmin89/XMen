/* PRQA S 3108++ */
/**
 * Copyright (C) 2024 Isoft Infrastructure Software Co., Ltd.
 * SPDX-License-Identifier: LGPL-2.1-only-with-exception OR  LicenseRef-Commercial-License
 *
 * This library is free software; you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation; version 2.1.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with this library;
 * if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * or see <https://www.gnu.org/licenses/>.
 *
 * Alternatively, this file may be used under the terms of the Isoft Infrastructure Software Co., Ltd.
 * Commercial License, in which case the provisions of the Isoft Infrastructure Software Co., Ltd.
 * Commercial License shall apply instead of those of the GNU Lesser General Public License.
 *
 * You should have received a copy of the Isoft Infrastructure Software Co., Ltd.  Commercial License
 * along with this program. If not, please find it at <https://EasyXMen.com/xy/reference/permissions.html>
 *
 ********************************************************************************
 **                                                                            **
 **  FILENAME    : Dcm_OBD0x01.c                                               **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      :                                                             **
 **  DESCRIPTION : DCM OBD0x01 API definitions                                 **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "OBD.h"
#include "Dcm_OBDInternal.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
Dcm_FillTo4bytes(P2VAR(uint8, AUTOMATIC, DCM_VAR) pDataBuf, P2CONST(uint32, AUTOMATIC, DCM_VAR) pData)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    /*take every byte of uint32 PID,and fill in Dcm_Channel*/
    pDataBuf[0] = (uint8)((*pData & ((uint32)0x000000FFu << 24u)) >> 24u);
    pDataBuf[1] = (uint8)((*pData & ((uint32)0x000000FFu << 16u)) >> 16u);
    pDataBuf[2] = (uint8)((*pData & ((uint32)0x000000FFu << 8u)) >> 8u);
    pDataBuf[3] = (uint8)(*pData & (uint32)0x000000FFu);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
/******************************************************************************/
/*
 * Brief               <OBD service (0x01): Request current powertrain diagnostic data>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:current protocol control identifier>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
#if (STD_ON == DCM_OBD_SERVICE0X01_ENABLED)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, DCM_CODE)
/* PRQA S 3432,1532,3673++ */ /* MISRA Rule 20.7,8.7,8.13 */
Dcm_OBD0x01(

    Dcm_OpStatusType OpStatus,
    uint8 ProtocolCtrlId,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode)
/* PRQA S 3432,1532,3673-- */ /* MISRA Rule 20.7,8.7,8.13 */
{
    uint8 TxChannelCtrlIndex;
    uint8 TxChannelCfgIndex;
    uint32 Offset;
    uint8 MsgCtrlId;
    uint8 PidNum;
    uint8 iloop;
    uint8 Pid;
    uint32 SupportBuffer;
    uint32 TxOffset;
    uint8 MixPid = 0;
    Std_ReturnType ret = E_OK;
    uint8 noFindPidNum = 0;
    OBD_ReadPidValuesTypes OBD_ReadPid;

    DCM_UNUSED(OpStatus);
    DCM_UNUSED(ErrorCode);
    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
    TxChannelCtrlIndex = Dcm_MsgCtrl[MsgCtrlId].Dcm_TxCtrlChannelIndex;
    TxChannelCfgIndex = Dcm_ChannelCtrl[TxChannelCtrlIndex].Dcm_ChannelCfgIndex;
    Offset = (Dcm_DslCfg.pDcmChannelCfg)[TxChannelCfgIndex].offset;

    /*check the massage length and format */
    if ((Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen < DCM_UDS0X01_REQ_DATA_LENGTH_MIN)
        || (Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen > DCM_UDS0X01_REQ_DATA_LENGTH_MAX))
    {
        /* requested message format is wrong,ignore the request message */
        ret = E_NOT_OK;
    }

    if (E_OK == ret)
    {
        /* get requested PIDs numbers*/
        PidNum = (uint8)Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen - 1u;
        SchM_Enter_Dcm(Dcm_Channel);
        Dcm_Channel[Offset] = 0x41;
        SchM_Exit_Dcm(Dcm_Channel);
        TxOffset = Offset + 1u;
        for (iloop = 0; (iloop < PidNum) && (E_OK == ret); iloop++)
        {
            Pid = Dcm_MsgCtrl[MsgCtrlId].MsgContext.pReqData[iloop + 1u];
            switch (Pid)
            {
            case 0x00u:
            case 0x20u:
            case 0x40u:
            case 0x60u:
            case 0x80u:
            case 0xA0u:
            case 0xC0u:
            case 0xE0u:
                if (MixPid == NORMAL_REQUEST)
                {
                    ret = E_NOT_OK;
                }
                else
                {
                    OBD_CheckSupportedPIDs(Pid, &SupportBuffer, SID_REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA);
                    if (SupportBuffer != 0u)
                    {
                        SchM_Enter_Dcm(Dcm_Channel);
                        Dcm_Channel[TxOffset] = Pid;
                        TxOffset += 1u;
                        Dcm_FillTo4bytes(&(Dcm_Channel[TxOffset]), &SupportBuffer);
                        SchM_Exit_Dcm(Dcm_Channel);
                        TxOffset += 4u;
                    }
                    else
                    {
                        noFindPidNum++;
                    }
                    MixPid = SUPPORT_REQUEST;
                }
                break;
            default:
                if (MixPid == SUPPORT_REQUEST)
                {
                    ret = E_NOT_OK;
                }
                else
                {
                    OBD_ReadPid.SID = SID_REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA;
                    OBD_ReadPid.pid = Pid;
                    OBD_ReadPid.UDSCall = FALSE;
                    ret = OBD_ReadPidValues(&OBD_ReadPid, &TxOffset, &noFindPidNum);
                    /* Request message is supported but data is currently not available,
                     * ignore the request message */
                    MixPid = NORMAL_REQUEST;
                }
                break;
            }
        }
        /* can not find supported PIDs,ignose the requested message */
        if (noFindPidNum == PidNum)
        {
            /* there is no supported PID,ignore the request message */
            ret = E_NOT_OK;
        }
    }

    /* check tx data length */
    if ((E_OK == ret) && ((TxOffset - Offset) > (Dcm_DslCfg.pDcmChannelCfg[TxChannelCfgIndex].Dcm_DslBufferSize)))
    {
        /*Pdu length is bigger than buffer size,ignore the request message */
        ret = E_NOT_OK;
    }
    if (E_OK == ret)
    {
        SchM_Enter_Dcm(Dcm_MsgCtrl);
        Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResMaxDataLen = (Dcm_MsgLenType)TxOffset - Offset;
        Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResDataLen = (Dcm_MsgLenType)TxOffset - Offset;
        Dcm_MsgCtrl[MsgCtrlId].MsgContext.pResData = &Dcm_Channel[Offset];
        SchM_Exit_Dcm(Dcm_MsgCtrl);
        DsdInternal_ProcessingDone(ProtocolCtrlId);
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif /*STD_ON == DCM_OBD_SERVICE0X01_ENABLED*/