/*	File:		ISpPPTestTools.cp	Contains:	xxx put contents here xxx	Version:	xxx put version here xxx	Copyright:	� 1998 by Apple Computer, Inc., all rights reserved.	File Ownership:		DRI:				xxx put dri here xxx		Other Contact:		xxx put other contact here xxx		Technology:			xxx put technology here xxx	Writers:		(BWS)	Brent Schorsch	Change History (most recent first):		 <2>	 7/17/98	BWS		add header and change creator for SDK*//*************************************************************************************File:      ISpPPTestTools.cpCopyright � 1996, 1997, 1998 Apple Computer, Inc., All Rights ReservedYou may incorporate this sample code into your applications withoutrestriction, though the sample code has been provided "AS IS" and theresponsibility for its operation is 100% yours.  However, what you arenot permitted to do is to redistribute the source as "DSC Sample Code"after having made changes. If you're going to re-distribute the source,we require that you make it clear in the source that the code wasdescended from Apple Sample Code, but that you've made changes.*************************************************************************************/#include "ISpPPTestTools.h"void UInt32ToHexBytes(UInt32 number, unsigned char *bytes){		UInt32 mask = 0xf0000000;	int itr;		for(itr = 0; itr < 8; itr++)	{		UInt32 digit = number & mask;		digit = digit >> (4 * (7 - itr));				char theChar;		if ((digit >= 0) && (digit <= 9))		{			theChar = '0' + digit;		}		else if ((digit >= 10) && (digit <= 15))		{			theChar = 'a' + digit - 10;		}		else		{			theChar ='?';		}				*bytes = theChar;		bytes++;				mask = mask >> 4;	}}void UInt32ToHexString(UInt32 number, Str255 theString){	theString[0] = 10;	theString[1] = '0';	theString[2] = 'x';		UInt32ToHexBytes(number, &(theString[3]));}void UnsignedWideToHexString(const UnsignedWide &number, Str255 theString){	theString[0] = 18;	theString[1] = '0';	theString[2] = 'x';	UInt32ToHexBytes(number.hi, &(theString[3]));	UInt32ToHexBytes(number.lo, &(theString[11]));}void UInt32ToFourByte(UInt32 number, Str255 theString){	theString[0] = 4;	theString[1] = (number & 0xff000000) >> 24;	theString[2] = (number & 0x00ff0000) >> 16;	theString[3] = (number & 0x0000ff00) >> 8;	theString[4] = (number & 0x000000ff) >> 0;}