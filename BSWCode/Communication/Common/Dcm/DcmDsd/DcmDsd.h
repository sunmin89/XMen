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
 **                                                                           **
 **  FILENAME    :                                                            **
 **                                                                           **
 **  Created on  : 2020/5/6 14:29:43                                          **
 **  Author      : tao.yu                                                     **
 **  Vendor      :                                                            **
 **  DESCRIPTION :                                                            **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                      **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */
#ifndef DCMDSD_H
#define DCMDSD_H
/*============================================================================*/

/****************************** references *********************************/
#include "Dcm_Types.h"

/****************************** declarations *********************************/
/*************************************************************************/
/*
 * Brief               <Find SID corresponding service configuration table index
 *                      and the service index in corresponding service configuration table.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Sid: Service Id;
 *                      ProtocolCtrlId: The corresponding protocol control block ID number>
 * Param-Name[out]     <(*pSidTabIndex):Request packet index number
 * in the service configuration table;
 *                      (*pSidTabServieCfgIndex): the service index
 *                      in corresponding service configuration table>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DCM_CODE) DsdInternal_SearchSidTabServiceIndex(
    uint8 Sid,
    uint8 ProtocolCtrlId,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(uint16, AUTOMATIC, DCM_VAR) pSidTabIndex,
    P2VAR(uint16, AUTOMATIC, DCM_VAR) pSidTabServieCfgIndex);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

extern FUNC(Std_ReturnType, DCM_CODE) DsdInternal_SearchSidTabSubServiceIndex(
    uint8 ProtocolCtrlId,
    uint16 SidTabIndex,
    uint16 ServiceIndex,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(uint16, AUTOMATIC, DCM_VAR) pSubServieCfgIndex);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

/*************************************************************************/
/*
 * Brief               <Set the negative response code NRC;>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:The corresponding protocol control block ID number;
 *                      Nrc: the negative response code;>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/
extern FUNC(void, DCM_CODE) DsdInternal_SetNrc(uint8 ProtocolCtrlId, Dcm_NegativeResponseCodeType Nrc);

/*************************************************************************/
/*
 * Brief               <Set corresponding message processing state>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:The corresponding protocol control block ID number;
 *                      MsgState: message processing state>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DsdInternal_SetMsgState(uint8 ProtocolCtrlId, Dcm_MsgStateType MsgState);

/*************************************************************************/
/*
 * Brief               <The diagnostic request processing in DSD layer>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:The corresponding protocol control block ID number;>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DCM_CODE) DsdInternal_RxIndication(uint8 ProtocolCtrlId);

/*************************************************************************/
/*
 * Brief               <Response to a diagnosis request processing>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:The corresponding protocol control block ID number;>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DsdInternal_ProcessingDone(uint8 ProtocolCtrlId);

/*************************************************************************/
/*
 * Brief               <Notify the DSD layer, respond to the confirmation>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:The corresponding protocol control block ID number;>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DsdInternal_TxConfirmation(uint8 ProtocolCtrlId);

/*************************************************************************/
/*
 * Brief               <Determine the diagnostic request packet is
 * allowed in the current session state.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:The corresponding protocol control block ID number;
 *                      Sid: Service Id;>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/
#if (STD_ON == DCM_SESSION_FUNC_ENABLED)

extern FUNC(Std_ReturnType, DCM_CODE) DsdInternal_SesCheck(uint8 ProtocolCtrlId, uint8 Sid);

extern FUNC(Std_ReturnType, DCM_CODE) DsdInternal_SubSesCheck(uint8 ProtocolCtrlId, uint8 Sid);

#if (STD_ON == DCM_DSP_DID_FUNC_ENABLED)

extern FUNC(Std_ReturnType, DCM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    DsdInternal_DidSessionCheck(uint16 DidInfoCfgIndex, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) pNrc);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

#endif
#endif
/*************************************************************************/
/*
 * Brief               <determine the diagnostic request packet is
 * allowed in the current security level>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:The corresponding protocol control block ID number;
 *                      Sid: Service Id;>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/
#if (STD_ON == DCM_SECURITY_FUNC_ENABLED)

extern FUNC(Std_ReturnType, DCM_CODE) DsdInternal_SecurityCheck(uint8 ProtocolCtrlId, uint8 Sid);

extern FUNC(Std_ReturnType, DCM_CODE) DsdInternal_SubSecurityCheck(uint8 ProtocolCtrlId, uint8 Sid);

#if (STD_ON == DCM_DSP_DID_FUNC_ENABLED)

extern FUNC(Std_ReturnType, DCM_CODE) DsdInternal_DidSecurityCheck(
    uint16 DidInfoCfgIndex,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) pNrc);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

#endif
#endif

#if ((STD_ON == DCM_DSP_DID_FUNC_ENABLED) && (STD_ON == DCM_UDS_SERVICE0X2C_ENABLED))

extern FUNC(Std_ReturnType, DCM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    DsdInternal_DDDIDcheckPerSourceDID(uint16 DDDidIdx, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) pNrc);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

#endif

FUNC(Std_ReturnType, DCM_CODE)
DsdInternal_ServiceAddressAndLengthFormatIdentifierCheck(const uint8 addressAndLengthFormatIdentifier);

#if (STD_ON == DCM_PAGEDBUFFER_ENABLED)

extern FUNC(void, DCM_CODE) DsdInternal_ProcessPage(uint8 ProtocolCtrlId);

extern FUNC(void, DCM_CODE) DsdInternal_StartPagedProcessing(uint8 ProtocolCtrlId);

#endif /*STD_ON == DCM_PAGEDBUFFER_ENABLED*/
/****************************** definitions *********************************/

#endif /* DCMDSD_H_ */
