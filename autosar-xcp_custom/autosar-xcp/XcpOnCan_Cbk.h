/* Copyright (C) 2010 Joakim Plate, Peter Fridlund
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef XCPONCAN_CBK_H_
#define XCPONCAN_CBK_H_

#include "ComStack_Types.h"
#include "CanIf.h"

void           Xcp_CanIfRxIndication   (PduIdType XcpRxPduId, PduInfoType* XcpRxPduPtr);
void           Xcp_CanIfRxSpecial      (uint8 channel, PduIdType XcpRxPduId, const uint8 * data, uint8 len, uint32 type);
void           Xcp_CanIfTxConfirmation (PduIdType XcpTxPduId);

#endif /* XCPONCAN_CBK_H_ */
