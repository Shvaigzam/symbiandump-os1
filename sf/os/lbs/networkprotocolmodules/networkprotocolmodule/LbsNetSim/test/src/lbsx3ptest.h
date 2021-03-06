/**
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @file lbsregisterlcsmolrtest.h
*/
#if (!defined LBSX3PEST_H)
#define LBSX3PEST_H
#include <test/testexecutestepbase.h>
#include "Te_lbsnetsimtestSuiteStepBase.h"
#include <lbs/test/lbsnetsimtest.h>
#include <lbs/test/lbsnetsimtestobserver.h>
#include <lbs/test/lbsnetsimgatewayobserver.h>
#include <lbs/test/lbsnetsimgateway.h>

class CLbsX3PTest : 
	public CTe_lbsnetsimtestSuiteStepBase
	{
	public:
		enum EStates
			{
			EError,
			EStart,
			EGatewayRegisterLcsMoLr,
			EGatewayMeasurementReportLocation,
			EGatewayReleaseLcsMoLr,
			EFinished
			};

		CLbsX3PTest();
		~CLbsX3PTest();
		virtual TVerdict doTestStepPreambleL();
		virtual TVerdict doTestStepL();
		virtual TVerdict doTestStepPostambleL();
	private:
		class CAOGateway : 
			public CAOGateway_Base
			{
			public:
				CAOGateway(CLbsX3PTest* aBase);
				~CAOGateway();
				
				void RunL();
				void DoCancel();
				TBool Finished();
			
				// MLbsNetSimGatewayObserver
				virtual void ProcessMeasurementControlLocation(const TPositionInfoBase& aPosition, const RLbsAssistanceDataBuilderSet& aData, const TLbsNetPosRequestQuality& aQuality);
				virtual void ProcessFacilityLcsMoLrResult(TInt, const TPositionInfoBase*);
			private:
				TBufC<10>	iDestination;
				TBool iMeasurementControlLocation;
				TBool iFacilityLcsMoLrResult;
			};
			
		class CAOTest :
			public CAOTest_Base
			{
			public:
				CAOTest(CLbsX3PTest* aBase, TInt aDelay, TBool aStepMode);
				~CAOTest();
				
				void RunL();
				void DoCancel();
				TBool Finished();
			
				// MLbsNetSimTestObserver
				virtual void NotifyRegisterLcsMoLr(const TDesC& aData);
				virtual void NotifyReleaseLcsMoLr(TInt aReason);
				virtual void NotifyMeasurementReportLocation(const TPositionInfo& aPosition);
				virtual void NotifyMeasurementControlLocation(const TPositionInfo& aPosition, const RLbsAssistanceDataBuilderSet& aData, const TLbsNetPosRequestQuality& aQuality);
				virtual void NotifyFacilityLcsMoLrResult(TInt, const TPositionInfo&);
			private:
				TBool	iNotificationRegisterLcsMoLr;
				TBool	iNotificationMeasurementReportLocation;
				TBool	iNotificationFacilityLcsMoLrResult;				
				TBool	iNotificationReleaseLcsMoLr;
				TBool   iNotificationMeasurementControlLocation;
			};
	};


_LIT(KX3PTest,"X3PTest");

#endif // LBSX3PEST_H
