// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// @file
// @internalTechnology
// @released
// Class implementation of CLbsPrivacyNotifierImpl
// 
//

#ifndef __LBSPRIVACYNOTIFIERIMPL_H__
#define __LBSPRIVACYNOTIFIERIMPL_H__

#include <e32std.h>
#include <e32def.h>
#include <e32base.h>

#include "LbsPrivacyNotifier.h"


/*
Wrapper to hide internal implementation

@internalTechnology
@released
*/
NONSHARABLE_CLASS(CLbsPrivacyNotifierImpl) : public CActive
	{

public:
	static CLbsPrivacyNotifierImpl* NewL(TPrivacyDialogType aDlg);
	static CLbsPrivacyNotifierImpl* NewL(TPrivacyDialogType aDlg, TTimeIntervalMicroSeconds32 aTimeout);
	~CLbsPrivacyNotifierImpl();
	void SetObserver(MLbsPrivacyNotifierObserver* aObserver);
	void DisplayL(TInt& aErr, const TLbsExternalRequestInfo& aRequestInfo);

protected:
	CLbsPrivacyNotifierImpl();
	void ConstructL(TPrivacyDialogType aDlg);
	void ConstructL(TPrivacyDialogType aDlg, TTimeIntervalMicroSeconds32 aTimeout);
	TInt Connect(); 
	void DoCancel();
	void RunL();

private:
	RNotifier iNotifier;// this hidden implementation uses notifier server to present user with dialogs
	RTimer iTimer;		// to implement dialog timeout
	TPrivacyDialogType iDialog;
	TTimeIntervalMicroSeconds32 iTimeout;
	TBool iConnected;
	TRequestStatus iStatus;
	MLbsPrivacyNotifierObserver* iObserver;
	TInt iButtonVal;
	};
	
#endif // __LBSPRIVACYNOTIFIERIMPL_H__
