/*-------------------------------- Arctic Core ------------------------------
 * Copyright (C) 2013, ArcCore AB, Sweden, www.arccore.com.
 * Contact: <contact@arccore.com>
 *
 * You may ONLY use this file:
 * 1)if you have a valid commercial ArcCore license and then in accordance with
 * the terms contained in the written license agreement between you and ArcCore,
 * or alternatively
 * 2)if you follow the terms found in GNU General Public License version 2 as
 * published by the Free Software Foundation and appearing in the file
 * LICENSE.GPL included in the packaging of this file or here
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>
 *-------------------------------- Arctic Core -----------------------------*/

#include <stdint.h>
#include "Cpu.h"
#include "asm_ppc.h"
#include "mm.h"

void MM_TlbSetup( const struct TlbEntry *tblTable  )
{
	int32_t i = 0;

	/* Setup the TLBs */
	while( tblTable[i].entry != (-1UL) ) {
		set_spr(SPR_MAS0, tblTable[i].mas0);
		set_spr(SPR_MAS1, tblTable[i].mas1);
		set_spr(SPR_MAS2, tblTable[i].mas2);
		set_spr(SPR_MAS3, tblTable[i].mas3);
		msync();
		isync();
		tlbwe();
		i++;
	}
}


