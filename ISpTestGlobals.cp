/*	File:		ISpTestGlobals.cp	Contains:	xxx put contents here xxx	Version:	xxx put version here xxx	Copyright:	� 1998 by Apple Computer, Inc., all rights reserved.	File Ownership:		DRI:				xxx put dri here xxx		Other Contact:		xxx put other contact here xxx		Technology:			xxx put technology here xxx	Writers:		(BWS)	Brent Schorsch	Change History (most recent first):		 <3>	 7/17/98	BWS		add header and change creator for SDK*//*************************************************************************************File:      ISpEventPane.hCopyright � 1996, 1997, 1998 Apple Computer, Inc., All Rights ReservedYou may incorporate this sample code into your applications withoutrestriction, though the sample code has been provided "AS IS" and theresponsibility for its operation is 100% yours.  However, what you arenot permitted to do is to redistribute the source as "DSC Sample Code"after having made changes. If you're going to re-distribute the source,we require that you make it clear in the source that the code wasdescended from Apple Sample Code, but that you've made changes.*************************************************************************************/#include "ISpTestGlobals.h"ISpElementListReference gElementList = 0;ISpElementReference gElement = 0;ISpElementReference gElementBuffer[1024];UInt32 gNumElements;UInt32 gCurElement = 0;extern OSStatus gStatus = noErr;LApplication *gMyApp = nil;Boolean gQuitting = false;