/*	File:		ISpEventPane.cp	Contains:	xxx put contents here xxx	Version:	xxx put version here xxx	Copyright:	� 1998 by Apple Computer, Inc., all rights reserved.	File Ownership:		DRI:				xxx put dri here xxx		Other Contact:		xxx put other contact here xxx		Technology:			xxx put technology here xxx	Writers:		(BWS)	Brent Schorsch	Change History (most recent first):		 <5>	 7/17/98	BWS		add header and change creator for SDK*//*************************************************************************************File:      ISpEventPane.cpCopyright � 1996, 1997, 1998 Apple Computer, Inc., All Rights ReservedYou may incorporate this sample code into your applications withoutrestriction, though the sample code has been provided "AS IS" and theresponsibility for its operation is 100% yours.  However, what you arenot permitted to do is to redistribute the source as "DSC Sample Code"after having made changes. If you're going to re-distribute the source,we require that you make it clear in the source that the code wasdescended from Apple Sample Code, but that you've made changes.*************************************************************************************/#include "ISpEventPane.h"#include "ISpTestGlobals.h"#include <CodeFragments.h>#include <TextUtils.h>#include <Math64.h>#include "ISpPPTestTools.h"#include "LString.h"ISpEventPane::ISpEventPane(LStream *inStream):LOffscreenView(inStream){	mDataValid = false;	StartIdling();}ISpEventPane::~ISpEventPane(){}ISpEventPane *ISpEventPane::CreateISpEventPaneStream(LStream *inStream){  return (new ISpEventPane(inStream));}void ISpEventPane::SpendTime(const EventRecord &inMacEvent){	inMacEvent;		if (gElementList == nil) { return; }	ISpElementEvent theEvent;		OSStatus theErr;	Boolean wasEvent;		theErr = ISpElementList_GetNextEvent(	gElementList, 											sizeof(ISpElementEvent),											&theEvent,											&wasEvent);		if (wasEvent)	{		mDataValid = true;				mPrintRecord.theError = theErr;				mPrintRecord.when = theEvent.when;		mPrintRecord.data = theEvent.data;		mPrintRecord.theElement = theEvent.element;		mPrintRecord.refCon = theEvent.refCon;		mPrintRecord.percent = theEvent.data;		float max = 0xffffffff;		mPrintRecord.percent /= max;				ISpElementInfo info;		ISpElement_GetInfo(theEvent.element, &info);		mPrintRecord.label = info.theLabel;		mPrintRecord.kind = info.theKind;		BlockMoveData(info.theString, mPrintRecord.theString, 64);		Refresh();		UpdatePort();	}}void ISpEventPane::DrawSelf(){	if (!mDataValid) { return; }		Rect r;	Str255 theString;			CalcLocalFrameRect(r);	r.left += 10;	EraseRect(&r);	MoveTo(r.left, r.top + 15);	DrawString("\pError Code:  ");	NumToString(mPrintRecord.theError, theString);	DrawString(theString);	MoveTo (r.left, r.top + 30);	DrawString ("\pTime:  ");	UnsignedWideToHexString(mPrintRecord.when, theString);	DrawString (theString);		DrawString ("\p (");	UnsignedWide microseconds = {0, 0};	(void) ISpTimeToMicroseconds(&mPrintRecord.when, &microseconds);	#if TYPE_LONGLONG 	long double seconds =  ((long double)(* (UInt64 *) &microseconds)) / 1000000.0;	LStr255 secondsStr (seconds, 6, 3);	DrawString (secondsStr);	#else	if ((Ptr) UInt64ToLongDouble != (Ptr) kUnresolvedCFragSymbolAddress)	{		long double seconds =  UInt64ToLongDouble (* (UInt64 *) &microseconds) / 1000000;		LStr255 secondsStr (seconds, 6, 3);		DrawString (secondsStr);	}	else	{		SInt32	seconds = 0;		if (microseconds.hi)			seconds = (microseconds.hi * (0xFFFFFFFFU/1000000U));		seconds += (microseconds.lo / 1000000U);					LStr255 secondsStr (seconds);		DrawString (secondsStr);	}#endif	DrawString ("\p seconds)");	MoveTo(r.left, r.top + 45);	DrawString("\pData:  ");	UInt32ToHexString(mPrintRecord.data, theString);	DrawString(theString);		{		const rectWidth = 100;		Rect maxRect = {2,0,11,rectWidth};		Rect progRect = maxRect;				progRect.right = rectWidth * mPrintRecord.percent;				OffsetRect(&maxRect, r.left, r.top + 47);		OffsetRect(&progRect, r.left, r.top + 47);				::FrameRect(&maxRect);		::PaintRect(&progRect);	}	MoveTo(r.left, r.top + 75);	DrawString("\pElement Num:  ");	UInt32ToHexString((unsigned long) mPrintRecord.theElement, theString);	DrawString(theString);	MoveTo(r.left, r.top + 90);	DrawString("\prefCon:  ");	UInt32ToHexString(mPrintRecord.refCon, theString);	DrawString(theString);	MoveTo(r.left, r.top + 105);	DrawString("\pElement Label:  ");	UInt32ToFourByte(mPrintRecord.label, theString);	DrawString(theString);	MoveTo(r.left, r.top + 120);	DrawString("\pElement Kind:  ");	UInt32ToFourByte(mPrintRecord.kind, theString);	DrawString(theString);	MoveTo(r.left, r.top + 135);	DrawString("\pElement Name:  ");	DrawString(mPrintRecord.theString);}