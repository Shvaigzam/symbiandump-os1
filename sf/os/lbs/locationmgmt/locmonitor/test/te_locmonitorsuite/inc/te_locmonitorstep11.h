/*
* Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/


/**
 @file te_locmonitorstep11.h
*/
#ifndef TE_LOCMONITORSTEP11_H
#define TE_LOCMONITORSTEP11_H

#include <test/TestExecuteStepBase.h>
#include "te_locmonitorstepbase.h"

class CTe_LocMonitorStep11 : public CTe_LocMonitorStepBase
	{
public:
	CTe_LocMonitorStep11();
	~CTe_LocMonitorStep11();
	virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	virtual TVerdict doTestStepPostambleL();

private:

	TPositionSatelliteInfo* iPosition;
	TPositionAreaExtendedInfo* iAreaInfo;
	TPosAreaReqParams* iAreaReqParams;
	};

_LIT(KLocMonitorStep11,"te_locmonitorstep11");

#endif
