// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// This file defines the class for the X3P protocol state handler
// 
//

/**
 @file
 @internalComponent
 @test
*/

#ifndef __CX3PSTATEHANDLER_H__
#define __CX3PSTATEHANDLER_H__

#include <e32base.h>
#include "cstatehandlerbase.h"

class CStateMachineBase;

/** Class that defines the X3P protocol state handler
This class implements pure virtual methods defined by CStateHandlerBase
@see CStateHandlerBase
*/
NONSHARABLE_CLASS(CX3pStateHandler) : public CStateHandlerBase
	{
public:

	static CX3pStateHandler* NewL(CStateMachineBase& aMachine);
	virtual ~CX3pStateHandler();
	
	// CStateHandlerBase methods
	
	void Initialise();
	void EntryActions();
	void ExitActions();
	
protected:

	CX3pStateHandler(CStateMachineBase& aMachine);
	
private:
	
	void ConstructL();

	};

#endif // __CX3PSTATEHANDLER_H__

