



/*
 * Copyright (c) 2000, 2002 - 2008 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)stdlib.h	8.5 (Berkeley) 5/19/95
 */





/*
 * Copyright (c) 2007-2016 by Apple Inc.. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
 


 /*     
    These macros are for use in OS header files. They enable function prototypes
    and Objective-C methods to be tagged with the OS version in which they
    were first available; and, if applicable, the OS version in which they 
    became deprecated.  
     
    The desktop Mac OS X and iOS each have different version numbers.
    The __OSX_AVAILABLE_STARTING() macro allows you to specify both the desktop
    and iOS version numbers.  For instance:
        __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0)
    means the function/method was first available on Mac OS X 10.2 on the desktop
    and first available in iOS 2.0 on the iPhone.
    
    If a function is available on one platform, but not the other a _NA (not
    applicable) parameter is used.  For instance:
            __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA)
    means that the function/method was first available on Mac OS X 10.3, and it
    currently not implemented on the iPhone.

    At some point, a function/method may be deprecated.  That means Apple
    recommends applications stop using the function, either because there is a 
    better replacement or the functionality is being phased out.  Deprecated
    functions/methods can be tagged with a __OSX_AVAILABLE_BUT_DEPRECATED()
    macro which specifies the OS version where the function became available
    as well as the OS version in which it became deprecated.  For instance:
        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA)
    means that the function/method was introduced in Mac OS X 10.0, then
    became deprecated beginning in Mac OS X 10.5.  On iOS the function 
    has never been available.  
    
    For these macros to function properly, a program must specify the OS version range 
    it is targeting.  The min OS version is specified as an option to the compiler:
    -mmacosx-version-min=10.x when building for Mac OS X, and -miphoneos-version-min=y.z
    when building for the iPhone.  The upper bound for the OS version is rarely needed,
    but it can be set on the command line via: -D__MAC_OS_X_VERSION_MAX_ALLOWED=10x0 for
    Mac OS X and __IPHONE_OS_VERSION_MAX_ALLOWED = y0z00 for iOS.  
    
    Examples:

        A function available in Mac OS X 10.5 and later, but not on the phone:
        
            extern void mymacfunc() __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);


        An Objective-C method in Mac OS X 10.5 and later, but not on the phone:
        
            @interface MyClass : NSObject
            -(void) mymacmethod __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
            @end

        
        An enum available on the phone, but not available on Mac OS X:
        
            #if __IPHONE_OS_VERSION_MIN_REQUIRED
                enum { myEnum = 1 };
            #endif
           Note: this works when targeting the Mac OS X platform because 
           __IPHONE_OS_VERSION_MIN_REQUIRED is undefined which evaluates to zero. 
        

        An enum with values added in different iPhoneOS versions:
		
			enum {
			    myX  = 1,	// Usable on iPhoneOS 2.1 and later
			    myY  = 2,	// Usable on iPhoneOS 3.0 and later
			    myZ  = 3,	// Usable on iPhoneOS 3.0 and later
				...
		      Note: you do not want to use #if with enumeration values
			  when a client needs to see all values at compile time
			  and use runtime logic to only use the viable values.
			  

    It is also possible to use the *_VERSION_MIN_REQUIRED in source code to make one
    source base that can be compiled to target a range of OS versions.  It is best
    to not use the _MAC_* and __IPHONE_* macros for comparisons, but rather their values.
    That is because you might get compiled on an old OS that does not define a later
    OS version macro, and in the C preprocessor undefined values evaluate to zero
    in expresssions, which could cause the #if expression to evaluate in an unexpected
    way.
    
        #ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
            // code only compiled when targeting Mac OS X and not iPhone
            // note use of 1050 instead of __MAC_10_5
            #if __MAC_OS_X_VERSION_MIN_REQUIRED < 1050
                // code in here might run on pre-Leopard OS
            #else
                // code here can assume Leopard or later
            #endif
        #endif


*/


/* __MAC_NA is not defined to a value but is uses as a token by macros to indicate that the API is unavailable */


/* __IPHONE_NA is not defined to a value but is uses as a token by macros to indicate that the API is unavailable */






/*
 * Copyright (c) 2007-2016 by Apple Inc.. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
    File:       AvailabilityInternal.h
 
    Contains:   implementation details of __OSX_AVAILABLE_* macros from <Availability.h>

*/






    #ifdef __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__
        /* compiler sets __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ when -miphoneos-version-min is used */
        
    #endif



    #ifdef __ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__
        /* compiler sets __ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__ when -mtvos-version-min is used */
        
        #define __TV_OS_VERSION_MAX_ALLOWED 110000 
        /* for compatibility with existing code.  New code should use platform specific checks */
        
    #endif



    #ifdef __ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__
        /* compiler sets __ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__ when -mwatchos-version-min is used */
        
        #define __WATCH_OS_VERSION_MAX_ALLOWED 40000
        /* for compatibility with existing code.  New code should use platform specific checks */
        
    #endif



    #ifdef __ENVIRONMENT_BRIDGE_OS_VERSION_MIN_REQUIRED__
        /* compiler sets __ENVIRONMENT_BRIDGE_OS_VERSION_MIN_REQUIRED__ when -mbridgeos-version-min is used */
        
        #define __BRIDGE_OS_VERSION_MAX_ALLOWED 20000
        /* for compatibility with existing code.  New code should use platform specific checks */
        
    #endif






    #if 1
        
    #else
        
    #endif










    /* make sure a default max version is set */
    
        #define __IPHONE_OS_VERSION_MAX_ALLOWED     110300
    
    /* make sure a valid min is set */
    




    
        #if 1
            /* use better attributes if possible */
            
            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_2_0    __attribute__((availability(ios,introduced=2.0,deprecated=2.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_2_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_2_1    __attribute__((availability(ios,introduced=2.0,deprecated=2.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_2_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=2.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_2_2    __attribute__((availability(ios,introduced=2.0,deprecated=2.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_2_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=2.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_3_0    __attribute__((availability(ios,introduced=2.0,deprecated=3.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_3_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=3.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_3_1    __attribute__((availability(ios,introduced=2.0,deprecated=3.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_3_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=3.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_3_2    __attribute__((availability(ios,introduced=2.0,deprecated=3.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_3_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=3.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_4_0    __attribute__((availability(ios,introduced=2.0,deprecated=4.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_4_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=4.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_4_1    __attribute__((availability(ios,introduced=2.0,deprecated=4.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_4_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=4.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_4_2    __attribute__((availability(ios,introduced=2.0,deprecated=4.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_4_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=4.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_4_3    __attribute__((availability(ios,introduced=2.0,deprecated=4.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_4_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=4.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_5_0    __attribute__((availability(ios,introduced=2.0,deprecated=5.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_5_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=5.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_5_1    __attribute__((availability(ios,introduced=2.0,deprecated=5.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_5_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=5.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_6_0    __attribute__((availability(ios,introduced=2.0,deprecated=6.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_6_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=6.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_6_1    __attribute__((availability(ios,introduced=2.0,deprecated=6.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_6_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=6.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_7_0    __attribute__((availability(ios,introduced=2.0,deprecated=7.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_7_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=7.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_7_1    __attribute__((availability(ios,introduced=2.0,deprecated=7.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_7_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=7.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_0    __attribute__((availability(ios,introduced=2.0,deprecated=8.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=8.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_1    __attribute__((availability(ios,introduced=2.0,deprecated=8.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=8.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=2.0,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=2.0,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=2.0,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=2.0,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=2.0,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=2.0,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=2.0,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=2.0,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=2.0,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=2.0,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=2.0,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=2.0,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=2.0,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=2.0,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=2.0,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.0,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_0_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=2.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_2_1                    __attribute__((availability(ios,introduced=2.1)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_2_1_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=2.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_2_2    __attribute__((availability(ios,introduced=2.2,deprecated=2.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_2_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=2.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_3_0    __attribute__((availability(ios,introduced=2.2,deprecated=3.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_3_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=3.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_3_1    __attribute__((availability(ios,introduced=2.2,deprecated=3.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_3_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=3.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_3_2    __attribute__((availability(ios,introduced=2.2,deprecated=3.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_3_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=3.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_4_0    __attribute__((availability(ios,introduced=2.2,deprecated=4.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_4_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=4.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_4_1    __attribute__((availability(ios,introduced=2.2,deprecated=4.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_4_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=4.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_4_2    __attribute__((availability(ios,introduced=2.2,deprecated=4.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_4_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=4.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_4_3    __attribute__((availability(ios,introduced=2.2,deprecated=4.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_4_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=4.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_5_0    __attribute__((availability(ios,introduced=2.2,deprecated=5.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_5_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=5.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_5_1    __attribute__((availability(ios,introduced=2.2,deprecated=5.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_5_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=5.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_6_0    __attribute__((availability(ios,introduced=2.2,deprecated=6.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_6_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=6.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_6_1    __attribute__((availability(ios,introduced=2.2,deprecated=6.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_6_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=6.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_7_0    __attribute__((availability(ios,introduced=2.2,deprecated=7.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_7_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=7.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_7_1    __attribute__((availability(ios,introduced=2.2,deprecated=7.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_7_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=7.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_0    __attribute__((availability(ios,introduced=2.2,deprecated=8.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=8.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_1    __attribute__((availability(ios,introduced=2.2,deprecated=8.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=8.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=2.2,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=2.2,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=2.2,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=2.2,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=2.2,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=2.2,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=2.2,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=2.2,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=2.2,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=2.2,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=2.2,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=2.2,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=2.2,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=2.2,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=2.2,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=2.2,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_2_2_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=2.2)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_3_0                    __attribute__((availability(ios,introduced=3.0)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_3_0_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=3.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_3_1    __attribute__((availability(ios,introduced=3.1,deprecated=3.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_3_1_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=3.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_3_2    __attribute__((availability(ios,introduced=3.1,deprecated=3.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_3_2_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=3.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_4_0    __attribute__((availability(ios,introduced=3.1,deprecated=4.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_4_0_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=4.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_4_1    __attribute__((availability(ios,introduced=3.1,deprecated=4.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_4_1_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=4.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_4_2    __attribute__((availability(ios,introduced=3.1,deprecated=4.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_4_2_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=4.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_4_3    __attribute__((availability(ios,introduced=3.1,deprecated=4.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_4_3_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=4.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_5_0    __attribute__((availability(ios,introduced=3.1,deprecated=5.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_5_0_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=5.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_5_1    __attribute__((availability(ios,introduced=3.1,deprecated=5.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_5_1_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=5.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_6_0    __attribute__((availability(ios,introduced=3.1,deprecated=6.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_6_0_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=6.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_6_1    __attribute__((availability(ios,introduced=3.1,deprecated=6.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_6_1_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=6.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_7_0    __attribute__((availability(ios,introduced=3.1,deprecated=7.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_7_0_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=7.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_7_1    __attribute__((availability(ios,introduced=3.1,deprecated=7.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_7_1_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=7.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_0    __attribute__((availability(ios,introduced=3.1,deprecated=8.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_0_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=8.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_1    __attribute__((availability(ios,introduced=3.1,deprecated=8.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_1_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=8.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=3.1,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=3.1,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=3.1,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=3.1,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=3.1,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=3.1,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=3.1,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=3.1,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=3.1,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=3.1,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=3.1,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=3.1,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=3.1,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=3.1,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=3.1,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=3.1,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_3_1_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=3.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_3_2                    __attribute__((availability(ios,introduced=3.2)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_3_2_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=3.2)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_4_0    __attribute__((availability(ios,introduced=4.0,deprecated=4.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_4_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=4.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_4_1    __attribute__((availability(ios,introduced=4.0,deprecated=4.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_4_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=4.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_4_2    __attribute__((availability(ios,introduced=4.0,deprecated=4.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_4_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=4.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_4_3    __attribute__((availability(ios,introduced=4.0,deprecated=4.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_4_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=4.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_5_0    __attribute__((availability(ios,introduced=4.0,deprecated=5.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_5_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=5.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_5_1    __attribute__((availability(ios,introduced=4.0,deprecated=5.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_5_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=5.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_6_0    __attribute__((availability(ios,introduced=4.0,deprecated=6.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_6_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=6.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_6_1    __attribute__((availability(ios,introduced=4.0,deprecated=6.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_6_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=6.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_7_0    __attribute__((availability(ios,introduced=4.0,deprecated=7.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_7_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=7.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_7_1    __attribute__((availability(ios,introduced=4.0,deprecated=7.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_7_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=7.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_0    __attribute__((availability(ios,introduced=4.0,deprecated=8.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=8.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_1    __attribute__((availability(ios,introduced=4.0,deprecated=8.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=8.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=4.0,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=4.0,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=4.0,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=4.0,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=4.0,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=4.0,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=4.0,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=4.0,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=4.0,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=4.0,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=4.0,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=4.0,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=4.0,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=4.0,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=4.0,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.0,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_0_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=4.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_4_1                    __attribute__((availability(ios,introduced=4.1)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_4_1_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=4.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_4_2    __attribute__((availability(ios,introduced=4.2,deprecated=4.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_4_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=4.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_4_3    __attribute__((availability(ios,introduced=4.2,deprecated=4.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_4_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=4.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_5_0    __attribute__((availability(ios,introduced=4.2,deprecated=5.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_5_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=5.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_5_1    __attribute__((availability(ios,introduced=4.2,deprecated=5.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_5_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=5.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_6_0    __attribute__((availability(ios,introduced=4.2,deprecated=6.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_6_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=6.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_6_1    __attribute__((availability(ios,introduced=4.2,deprecated=6.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_6_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=6.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_7_0    __attribute__((availability(ios,introduced=4.2,deprecated=7.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_7_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=7.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_7_1    __attribute__((availability(ios,introduced=4.2,deprecated=7.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_7_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=7.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_0    __attribute__((availability(ios,introduced=4.2,deprecated=8.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=8.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_1    __attribute__((availability(ios,introduced=4.2,deprecated=8.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=8.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=4.2,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=4.2,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=4.2,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=4.2,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=4.2,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=4.2,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=4.2,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=4.2,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=4.2,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=4.2,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=4.2,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=4.2,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=4.2,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=4.2,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=4.2,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=4.2,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_4_2_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=4.2)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_4_3                    __attribute__((availability(ios,introduced=4.3)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_4_3_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=4.3)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_5_0    __attribute__((availability(ios,introduced=5.0,deprecated=5.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_5_0_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=5.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_5_1    __attribute__((availability(ios,introduced=5.0,deprecated=5.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_5_1_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=5.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_6_0    __attribute__((availability(ios,introduced=5.0,deprecated=6.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_6_0_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=6.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_6_1    __attribute__((availability(ios,introduced=5.0,deprecated=6.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_6_1_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=6.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_7_0    __attribute__((availability(ios,introduced=5.0,deprecated=7.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_7_0_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=7.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_7_1    __attribute__((availability(ios,introduced=5.0,deprecated=7.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_7_1_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=7.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_0    __attribute__((availability(ios,introduced=5.0,deprecated=8.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_0_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=8.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_1    __attribute__((availability(ios,introduced=5.0,deprecated=8.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_1_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=8.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=5.0,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=5.0,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=5.0,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=5.0,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=5.0,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=5.0,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=5.0,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=5.0,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=5.0,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=5.0,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=5.0,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=5.0,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=5.0,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=5.0,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=5.0,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=5.0,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_5_0_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=5.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_5_1                    __attribute__((availability(ios,introduced=5.1)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_5_1_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=5.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_6_0    __attribute__((availability(ios,introduced=6.0,deprecated=6.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_6_0_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=6.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_6_1    __attribute__((availability(ios,introduced=6.0,deprecated=6.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_6_1_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=6.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_7_0    __attribute__((availability(ios,introduced=6.0,deprecated=7.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_7_0_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=7.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_7_1    __attribute__((availability(ios,introduced=6.0,deprecated=7.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_7_1_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=7.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_0    __attribute__((availability(ios,introduced=6.0,deprecated=8.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_0_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=8.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_1    __attribute__((availability(ios,introduced=6.0,deprecated=8.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_1_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=8.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=6.0,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=6.0,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=6.0,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=6.0,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=6.0,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=6.0,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=6.0,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=6.0,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=6.0,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=6.0,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=6.0,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=6.0,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=6.0,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=6.0,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=6.0,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=6.0,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=6.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_6_1                    __attribute__((availability(ios,introduced=6.1)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_6_1_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=6.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_7_0    __attribute__((availability(ios,introduced=7.0,deprecated=7.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_7_0_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=7.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_7_1    __attribute__((availability(ios,introduced=7.0,deprecated=7.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_7_1_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=7.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_0    __attribute__((availability(ios,introduced=7.0,deprecated=8.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_0_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=8.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_1    __attribute__((availability(ios,introduced=7.0,deprecated=8.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_1_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=8.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=7.0,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=7.0,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=7.0,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=7.0,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=7.0,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=7.0,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=7.0,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=7.0,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=7.0,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=7.0,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=7.0,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=7.0,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=7.0,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=7.0,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=7.0,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=7.0,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_7_0_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=7.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_7_1                    __attribute__((availability(ios,introduced=7.1)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_7_1_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=7.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_0    __attribute__((availability(ios,introduced=8.0,deprecated=8.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=8.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_1    __attribute__((availability(ios,introduced=8.0,deprecated=8.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=8.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=8.0,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=8.0,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=8.0,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=8.0,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=8.0,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=8.0,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=8.0,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=8.0,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=8.0,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=8.0,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=8.0,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=8.0,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=8.0,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=8.0,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=8.0,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.0,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_0_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=8.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_8_1                    __attribute__((availability(ios,introduced=8.1)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_8_1_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=8.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_8_2    __attribute__((availability(ios,introduced=8.2,deprecated=8.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_8_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=8.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_8_3    __attribute__((availability(ios,introduced=8.2,deprecated=8.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_8_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=8.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=8.2,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=8.2,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=8.2,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=8.2,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=8.2,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=8.2,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=8.2,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=8.2,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=8.2,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=8.2,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=8.2,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=8.2,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=8.2,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.2,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_2_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=8.2)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_8_3                    __attribute__((availability(ios,introduced=8.3)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_8_3_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=8.3)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_8_4    __attribute__((availability(ios,introduced=8.4,deprecated=8.4)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_8_4_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=8.4,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_9_0    __attribute__((availability(ios,introduced=8.4,deprecated=9.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_9_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=9.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=8.4,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=8.4,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=8.4,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=8.4,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=8.4,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=8.4,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=8.4,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=8.4,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=8.4,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=8.4,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=8.4,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=8.4,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_8_4_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=8.4)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_9_0                    __attribute__((availability(ios,introduced=9.0)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_9_0_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=9.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_9_1    __attribute__((availability(ios,introduced=9.1,deprecated=9.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_9_1_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=9.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_9_2    __attribute__((availability(ios,introduced=9.1,deprecated=9.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_9_2_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=9.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=9.1,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=9.1,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=9.1,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=9.1,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=9.1,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=9.1,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=9.1,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=9.1,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=9.1,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=9.1,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_1_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=9.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_9_2                    __attribute__((availability(ios,introduced=9.2)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_9_2_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=9.2)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_9_3    __attribute__((availability(ios,introduced=9.3,deprecated=9.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_9_3_MSG(_msg)    __attribute__((availability(ios,introduced=9.3,deprecated=9.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_10_0    __attribute__((availability(ios,introduced=9.3,deprecated=10.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_10_0_MSG(_msg)    __attribute__((availability(ios,introduced=9.3,deprecated=10.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=9.3,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=9.3,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=9.3,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=9.3,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=9.3,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=9.3,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=9.3,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=9.3,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=9.3,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=9.3,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=9.3,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=9.3,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=9.3,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=9.3,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_9_3_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=9.3)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_10_0                    __attribute__((availability(ios,introduced=10.0)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_10_0_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=10.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_10_1    __attribute__((availability(ios,introduced=10.1,deprecated=10.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_10_1_MSG(_msg)    __attribute__((availability(ios,introduced=10.1,deprecated=10.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_10_2    __attribute__((availability(ios,introduced=10.1,deprecated=10.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_10_2_MSG(_msg)    __attribute__((availability(ios,introduced=10.1,deprecated=10.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=10.1,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=10.1,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=10.1,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=10.1,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=10.1,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=10.1,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=10.1,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=10.1,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=10.1,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=10.1,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_1_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=10.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_10_2                    __attribute__((availability(ios,introduced=10.2)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_10_2_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=10.2)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_10_3    __attribute__((availability(ios,introduced=10.3,deprecated=10.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_10_3_MSG(_msg)    __attribute__((availability(ios,introduced=10.3,deprecated=10.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_11_0    __attribute__((availability(ios,introduced=10.3,deprecated=11.0)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_11_0_MSG(_msg)    __attribute__((availability(ios,introduced=10.3,deprecated=11.0,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=10.3,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=10.3,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=10.3,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=10.3,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=10.3,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=10.3,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_10_3_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=10.3)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_11_0                    __attribute__((availability(ios,introduced=11.0)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_11_0_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=11.0)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_11_1_DEP__IPHONE_11_1    __attribute__((availability(ios,introduced=11.1,deprecated=11.1)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_11_1_DEP__IPHONE_11_1_MSG(_msg)    __attribute__((availability(ios,introduced=11.1,deprecated=11.1,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_11_1_DEP__IPHONE_11_2    __attribute__((availability(ios,introduced=11.1,deprecated=11.2)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_11_1_DEP__IPHONE_11_2_MSG(_msg)    __attribute__((availability(ios,introduced=11.1,deprecated=11.2,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_11_1_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=11.1,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_11_1_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=11.1,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_11_1_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=11.1)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_11_2                    __attribute__((availability(ios,introduced=11.2)))
            
            #if 1
                    
            #else
                    
            #endif
            
            #if 1
                    
            #else
                    
            #endif
            
            #define __AVAILABILITY_INTERNAL__IPHONE_11_2_DEP__IPHONE_NA_MSG(_msg)     __attribute__((availability(ios,introduced=11.2)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_11_3_DEP__IPHONE_11_3    __attribute__((availability(ios,introduced=11.3,deprecated=11.3)))
            
                    #define __AVAILABILITY_INTERNAL__IPHONE_11_3_DEP__IPHONE_11_3_MSG(_msg)    __attribute__((availability(ios,introduced=11.3,deprecated=11.3,message=_msg)))
            


            #define __AVAILABILITY_INTERNAL__IPHONE_11_3_DEP__IPHONE_NA               __attribute__((availability(ios,introduced=11.3)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_NA                               __attribute__((availability(ios,unavailable)))
            
            #define __AVAILABILITY_INTERNAL__IPHONE_NA_DEP__IPHONE_NA_MSG(_msg)      __attribute__((availability(ios,unavailable)))
        
    #endif

    


        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 101300
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 101300
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_12_4        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 101202
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 101202
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_12_1        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 101200
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 101200
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 101103
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 101103
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 101100
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 101100
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 101002
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 101002
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_10        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 1090
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 1090
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_8        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 1070
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 1070
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_6        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 1050
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 1050
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_4        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 1030
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 1030
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_2        __attribute__((unavailable))
        




        #if __MAC_OS_X_VERSION_MAX_ALLOWED < 1010
            
        #elif __MAC_OS_X_VERSION_MIN_REQUIRED < 1010
            
        #else
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0        __attribute__((unavailable))
        




        #define __AVAILABILITY_INTERNAL__MAC_NA             __attribute__((unavailable))
        





            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_1              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_1              
            
        #endif
        







            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_2              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_2              __AVAILABILITY_INTERNAL__MAC_10_2
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_3              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_3              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_3              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_4              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_4              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_4              __AVAILABILITY_INTERNAL__MAC_10_4
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_5              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_5              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_5              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_5              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_5              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_5              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_6              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_6              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_6              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_6              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_6              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_6              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_6              __AVAILABILITY_INTERNAL__MAC_10_6
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_7              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_7              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_7              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_7              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_7              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_7              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_7              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_7              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_8              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_8              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_8              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_8              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_8              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_8              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_8              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_8              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_8              __AVAILABILITY_INTERNAL__MAC_10_8
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_9              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_9              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_9              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_9              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_9              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_9              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_9              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_9              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_9              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_9              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_10              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_10              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_10              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_10              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_10              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_10              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_10              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_10              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_10              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_10              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_10              __AVAILABILITY_INTERNAL__MAC_10_10
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_10_2              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_10_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_10_2              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_10_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_10_2              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_10_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_10_2              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_10_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_10_2              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_10_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_10_2              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_10_2              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_10_3              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_10_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_10_3              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_10_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_10_3              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_10_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_10_3              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_10_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_10_3              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_10_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_10_3              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_10_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_10_3              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_11              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_11              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_11              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_11              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_11              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_11              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_11              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_11              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_11              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_11              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_11              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_11              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_11              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_11              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_11_2              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_11_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_11_2              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_11_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_11_2              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_11_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_11_2              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_11_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_11_2              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_11_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_11_2              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_11_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_11_2              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_11_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_11_2              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_11_3              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_11_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_11_3              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_11_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_11_3              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_11_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_11_3              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_11_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_11_3              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_11_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_11_3              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_11_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_11_3              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_11_3              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_11_3              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_11_3              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_11_4              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_11_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_11_4              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_11_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_11_4              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_11_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_11_4              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_11_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_11_4              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_11_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_11_4              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_11_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_11_4              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_11_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_11_4              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_11_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_10_11_4              __AVAILABILITY_INTERNAL__MAC_10_11_4
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_12              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_12              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_12              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_12              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_12              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_12              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_12              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_12              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_12              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_12              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_12              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_12              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_12              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_12              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_12              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_12              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_10_12              __AVAILABILITY_INTERNAL__MAC_10_11_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_DEP__MAC_10_12              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_12_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_12_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_12_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_12_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_12_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_12_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_12_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_12_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_11_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_DEP__MAC_10_12_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_1_DEP__MAC_10_12_1              __AVAILABILITY_INTERNAL__MAC_10_12_1
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_12_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_12_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_12_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_12_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_12_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_12_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_12_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_12_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_11_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_DEP__MAC_10_12_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_1_DEP__MAC_10_12_2              __AVAILABILITY_INTERNAL__MAC_10_12_1
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_2_DEP__MAC_10_12_2              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_11_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_1_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_12_1
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_2_DEP__MAC_10_12_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_4_DEP__MAC_10_12_4              __AVAILABILITY_INTERNAL__MAC_10_12_4
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_11_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_1_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_12_1
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_2_DEP__MAC_10_13              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_4_DEP__MAC_10_13              __AVAILABILITY_INTERNAL__MAC_10_12_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_DEP__MAC_10_13              
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_11_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_1_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_12_1
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_2_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_4_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_12_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_DEP__MAC_10_13_1              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_1_DEP__MAC_10_13_1              __AVAILABILITY_INTERNAL__MAC_10_13_1
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_11_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_1_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_12_1
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_2_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_4_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_12_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_DEP__MAC_10_13_2              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_1_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_13_1
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_2_DEP__MAC_10_13_2              __AVAILABILITY_INTERNAL__MAC_10_13_2
            
        #endif
        
            #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_0
            
            #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_6
            
            #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_8
            
            #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_10
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_10_3
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_11_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_11_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_1_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_12_1
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_2_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_12_4_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_12_4
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_DEP__MAC_10_13_4              
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_1_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_13_1
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_2_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_13_2
            
            #define __AVAILABILITY_INTERNAL__MAC_10_13_4_DEP__MAC_10_13_4              __AVAILABILITY_INTERNAL__MAC_10_13_4
            
        #endif
        
        #define __AVAILABILITY_INTERNAL__MAC_10_0_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_0
        
        #define __AVAILABILITY_INTERNAL__MAC_10_1_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_2_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_2
        
        #define __AVAILABILITY_INTERNAL__MAC_10_3_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_4_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_4
        
        #define __AVAILABILITY_INTERNAL__MAC_10_5_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_6_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_6
        
        #define __AVAILABILITY_INTERNAL__MAC_10_7_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_8
        
        #define __AVAILABILITY_INTERNAL__MAC_10_9_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_10_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_10
        
        #define __AVAILABILITY_INTERNAL__MAC_10_10_2_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_10_3_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_10_3
        
        #define __AVAILABILITY_INTERNAL__MAC_10_11_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_11_2_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_11_2
        
        #define __AVAILABILITY_INTERNAL__MAC_10_11_3_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_11_4_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_11_4
        
        #define __AVAILABILITY_INTERNAL__MAC_10_12_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_12_1_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_12_1
        
        #define __AVAILABILITY_INTERNAL__MAC_10_12_2_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_12_4_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_12_4
        
        #define __AVAILABILITY_INTERNAL__MAC_10_13_DEP__MAC_NA_MSG(_msg)   
        
        #define __AVAILABILITY_INTERNAL__MAC_10_13_1_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_13_1
        
        #define __AVAILABILITY_INTERNAL__MAC_10_13_2_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_13_2
        
        #define __AVAILABILITY_INTERNAL__MAC_10_13_4_DEP__MAC_NA_MSG(_msg)   __AVAILABILITY_INTERNAL__MAC_10_13_4
        
        #define __AVAILABILITY_INTERNAL__MAC_NA_DEP__MAC_NA_MSG(_msg)     __attribute__((unavailable))
    


/*
 Macros for defining which versions/platform a given symbol can be used.
 
 @see http://clang.llvm.org/docs/AttributeReference.html#availability
 */


 #if 1

    /*
     * API Introductions
     *
     * Use to specify the release that a particular API became available.
     *
     * Platform names:
     *   macos, ios, tvos, watchos, bridgeos
     *
     * Examples:
     *    __API_AVAILABLE(macos(10.10))
     *    __API_AVAILABLE(macos(10.9), ios(10.0))
     *    __API_AVAILABLE(macos(10.4), ios(8.0), watchos(2.0), tvos(10.0))
     *    __API_AVAILABLE(macos(10.4), ios(8.0), watchos(2.0), tvos(10.0), bridgeos(2.0))
     */
    
    #define __API_AVAILABLE_PLATFORM_macosx(x) macosx,introduced=x
    
    #define __API_AVAILABLE_PLATFORM_watchos(x) watchos,introduced=x
    
    #define __API_AVAILABLE_PLATFORM_bridgeos(x) bridgeos,introduced=x

    
    #define __API_AVAILABLE1(x) __attribute__((availability(__API_AVAILABLE_PLATFORM_##x)))
    
    #define __API_AVAILABLE3(x,y,z)  __attribute__((availability(__API_AVAILABLE_PLATFORM_##x))) __attribute__((availability(__API_AVAILABLE_PLATFORM_##y))) __attribute__((availability(__API_AVAILABLE_PLATFORM_##z)))
    
    #define __API_AVAILABLE5(x,y,z,t,b) __attribute__((availability(__API_AVAILABLE_PLATFORM_##x))) __attribute__((availability(__API_AVAILABLE_PLATFORM_##y))) __attribute__((availability(__API_AVAILABLE_PLATFORM_##z))) __attribute__((availability(__API_AVAILABLE_PLATFORM_##t))) __attribute__((availability(__API_AVAILABLE_PLATFORM_##b)))
    

    /*
     * API Deprecations
     *
     * Use to specify the release that a particular API became unavailable.
     *
     * Platform names:
     *   macos, ios, tvos, watchos, bridgeos
     *
     * Examples:
     *
     *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8))
     *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8), ios(2.0, 3.0), watchos(2.0, 3.0), tvos(9.0, 10.0))
     *
     *    __API_DEPRECATED_WITH_REPLACEMENT("-setName:", tvos(10.0, 10.4), ios(9.0, 10.0))
     *    __API_DEPRECATED_WITH_REPLACEMENT("SomeClassName", macos(10.4, 10.6), watchos(2.0, 3.0))
     */
    
    #define __API_DEPRECATED_PLATFORM_macosx(x,y) macosx,introduced=x,deprecated=y
    
    #define __API_DEPRECATED_PLATFORM_watchos(x,y) watchos,introduced=x,deprecated=y
    
    #define __API_DEPRECATED_PLATFORM_bridgeos(x,y) bridgeos,introduced=x,deprecated=y

    
    #define __API_DEPRECATED_MSG2(msg,x) __attribute__((availability(__API_DEPRECATED_PLATFORM_##x,message=msg)))
    
    #define __API_DEPRECATED_MSG4(msg,x,y,z) __attribute__((availability(__API_DEPRECATED_PLATFORM_##x,message=msg))) __attribute__((availability(__API_DEPRECATED_PLATFORM_##y,message=msg))) __attribute__((availability(__API_DEPRECATED_PLATFORM_##z,message=msg)))
    
    #define __API_DEPRECATED_MSG6(msg,x,y,z,t,b) __API_DEPRECATED_MSG4(msg,x,y,z) __attribute__((availability(__API_DEPRECATED_PLATFORM_##t,message=msg))) __attribute__((availability(__API_DEPRECATED_PLATFORM_##b,message=msg)))
    

    
        #define __API_R(rep,x) __attribute__((availability(__API_DEPRECATED_PLATFORM_##x,replacement=rep)))
    



    
    #define __API_DEPRECATED_REP3(rep,x,y) __API_R(rep,x) __API_R(rep,y)
    
    #define __API_DEPRECATED_REP5(rep,x,y,z,t) __API_DEPRECATED_REP3(rep,x,y) __API_R(rep,z) __API_R(rep,t)
    
    #define __API_DEPRECATED_REP_GET_MACRO(_1,_2,_3,_4,_5,_6,NAME,...) NAME

    /*
     * API Unavailability
     * Use to specify that an API is unavailable for a particular platform.
     *
     * Example:
     *    __API_UNAVAILABLE(macos)
     *    __API_UNAVAILABLE(watchos, tvos)
     */
    
    #define __API_UNAVAILABLE_PLATFORM_macosx macosx,unavailable
    
    #define __API_UNAVAILABLE_PLATFORM_watchos watchos,unavailable
    
    #define __API_UNAVAILABLE_PLATFORM_bridgeos bridgeos,unavailable

    
    #define __API_UNAVAILABLE1(x) __attribute__((availability(__API_UNAVAILABLE_PLATFORM_##x)))
    
    #define __API_UNAVAILABLE3(x,y,z) __attribute__((availability(__API_UNAVAILABLE_PLATFORM_##x))) __attribute__((availability(__API_UNAVAILABLE_PLATFORM_##y))) __attribute__((availability(__API_UNAVAILABLE_PLATFORM_##z)))
    
    #define __API_UNAVAILABLE_GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
 

/*
 * Swift compiler version
 * Allows for project-agnostic “epochs” for frameworks imported into Swift via the Clang importer, like #if _compiler_version for Swift
 * Example:
 *
 *  #if __swift_compiler_version_at_least(800, 2, 20)
 *  - (nonnull NSString *)description;
 *  #else
 *  - (NSString *)description;
 *  #endif
 */
 





    #define __swift_compiler_version_at_least(...) 1





    #define __OSX_AVAILABLE_STARTING(_osx, _ios) __AVAILABILITY_INTERNAL##_ios
    

    #define __OSX_AVAILABLE_BUT_DEPRECATED_MSG(_osxIntro, _osxDep, _iosIntro, _iosDep, _msg)                                                      __AVAILABILITY_INTERNAL##_iosIntro##_DEP##_iosDep##_MSG(_msg)





  #if 1
    
    #define __OS_AVAILABILITY_MSG(_target, _availability, _msg)  __attribute__((availability(_target,_availability,message=_msg)))
  


/* for use to document app extension usage */

  #if 1
    
    #define __IOS_EXTENSION_UNAVAILABLE(_msg)  __OS_AVAILABILITY_MSG(ios_app_extension,unavailable,_msg)
  




    #define __OS_AVAILABILITY_MSG(macosx_app_extension,unavailable,_msg)
    






/* for use marking APIs available info for Mac OSX */

  #if 1
    
    #define __OSX_AVAILABLE(_vers)               __attribute__((availability(macosx,introduced=_vers)))
    
  #endif







  #define __OSX_AVAILABLE(_vers)







/* for use marking APIs available info for iOS */

  #if 1
    
    #define __IOS_PROHIBITED                     __attribute__((availability(ios,unavailable)))
    
    #define __IOS_DEPRECATED(_start, _dep, _msg) __attribute__((availability(ios,introduced=_start))) __OS_AVAILABILITY_MSG(ios,deprecated=_dep,_msg)
  







  #define __IOS_PROHIBITED







  #define __IOS_DEPRECATED(_start, _dep, _msg)



/* for use marking APIs available info for tvOS */

  #if 1
    
    #define __TVOS_PROHIBITED                     __attribute__((availability(tvos,unavailable)))
    
    #define __TVOS_DEPRECATED(_start, _dep, _msg) __attribute__((availability(tvos,introduced=_start))) __OS_AVAILABILITY_MSG(tvos,deprecated=_dep,_msg)
  







  #define __TVOS_PROHIBITED







  #define __TVOS_DEPRECATED(_start, _dep, _msg)



/* for use marking APIs available info for Watch OS */

  #if 1
    
    #define __WATCHOS_PROHIBITED                     __attribute__((availability(watchos,unavailable)))
    
    #define __WATCHOS_DEPRECATED(_start, _dep, _msg) __attribute__((availability(watchos,introduced=_start))) __OS_AVAILABILITY_MSG(watchos,deprecated=_dep,_msg)
  







  #define __WATCHOS_PROHIBITED







  #define __WATCHOS_DEPRECATED(_start, _dep, _msg)



/* for use marking APIs unavailable for swift */

  #if 1
    
    #define __SWIFT_UNAVAILABLE_MSG(_msg)         __OS_AVAILABILITY_MSG(swift,unavailable,_msg)
  







  #define __SWIFT_UNAVAILABLE_MSG(_msg)



/*
 Macros for defining which versions/platform a given symbol can be used.
 
 @see http://clang.llvm.org/docs/AttributeReference.html#availability
 
 * Note that these macros are only compatible with clang compilers that
 * support the following target selection options:
 *
 * -mmacosx-version-min
 * -miphoneos-version-min
 * -mwatchos-version-min
 * -mtvos-version-min
 * -mbridgeos-version-min
 */


 #if 1

    /*
     * API Introductions
     *
     * Use to specify the release that a particular API became available.
     *
     * Platform names:
     *   macos, ios, tvos, watchos
     *
     * Examples:
     *    __API_AVAILABLE(macos(10.10))
     *    __API_AVAILABLE(macos(10.9), ios(10.0))
     *    __API_AVAILABLE(macos(10.4), ios(8.0), watchos(2.0), tvos(10.0))
     */
    


    /*
     * API Deprecations
     *
     * Use to specify the release that a particular API became unavailable.
     *
     * Platform names:
     *   macos, ios, tvos, watchos
     *
     * Examples:
     *
     *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8))
     *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8), ios(2.0, 3.0), watchos(2.0, 3.0), tvos(9.0, 10.0))
     *
     *    __API_DEPRECATED_WITH_REPLACEMENT("-setName:", tvos(10.0, 10.4), ios(9.0, 10.0))
     *    __API_DEPRECATED_WITH_REPLACEMENT("SomeClassName", macos(10.4, 10.6), watchos(2.0, 3.0))
     */
    
    #define __API_DEPRECATED_WITH_REPLACEMENT(...) __API_DEPRECATED_REP_GET_MACRO(__VA_ARGS__,__API_DEPRECATED_REP6,__API_DEPRECATED_REP5,__API_DEPRECATED_REP4,__API_DEPRECATED_REP3,__API_DEPRECATED_REP2,__API_DEPRECATED_REP1)(__VA_ARGS__)

    /*
     * API Unavailability
     * Use to specify that an API is unavailable for a particular platform.
     *
     * Example:
     *    __API_UNAVAILABLE(macos)
     *    __API_UNAVAILABLE(watchos, tvos)
     */
    
 #else 

    /* 
     * Evaluate to nothing for compilers that don't support availability.
     */
    
    
    #define __API_DEPRECATED_MSG1(...)
    
    #define __API_UNAVAILABLE_GET_MACRO(...,__API_UNAVAILABLE4,__API_UNAVAILABLE3,__API_UNAVAILABLE2,__API_UNAVAILABLE1)(...)
 


    /* 
     * Evaluate to nothing for compilers that don't support clang language extensions.
     */
    
    
    #define __API_DEPRECATED_MSG1(...)
    
    #define __API_UNAVAILABLE_GET_MACRO(...,__API_UNAVAILABLE4,__API_UNAVAILABLE3,__API_UNAVAILABLE2,__API_UNAVAILABLE1)(...)







/*
 * Copyright (c) 2004, 2008, 2009 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */





/*
 * Copyright (c) 2003-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */





/*
 * Copyright (c) 2000-2016 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/* Copyright 1995 NeXT Computer, Inc. All rights reserved. */
/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Berkeley Software Design, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)cdefs.h	8.8 (Berkeley) 1/9/95
 */












/* This SDK is designed to work with clang and specific versions of
 * gcc >= 4.0 with Apple's patch sets */




/*
 * Compatibility with compilers and environments that don't support compiler
 * feature checking function-like macros.
 */


/*
 * The __CONCAT macro is used to concatenate parts of symbol names, e.g.
 * with "#define OLD(foo) __CONCAT(old,foo)", OLD(foo) produces oldfoo.
 * The __CONCAT macro is a bit tricky -- make sure you don't put spaces
 * in between its arguments.  __CONCAT can also concatenate double-quoted
 * strings produced by the __STRING macro, but this only works with ANSI C.
 */









/*
 * In non-ANSI C environments, new programs will want ANSI-only C keywords
 * deleted from the program and old programs will want them left alone.
 * When using a compiler other than gcc, programs using the ANSI C keywords
 * const, inline etc. as normal identifiers should define -DNO_ANSI_KEYWORDS.
 * When using "gcc -traditional", we assume that this is the intent; if
 * __GNUC__ is defined but __STDC__ is not, we leave the new keywords alone.
 */











/* __unused denotes variables and functions that may not be used, preventing
 * the compiler from warning about it if not used.
 */


/* __used forces variables and functions to be included even if it appears
 * to the compiler that they are not used (and would thust be discarded).
 */


/* __deprecated causes the compiler to produce a warning when encountering
 * code using the deprecated functionality.
 * __deprecated_msg() does the same, and compilers that support it will print
 * a message along with the deprecation warning.
 * This may require turning on such warning with the -Wdeprecated flag.
 * __deprecated_enum_msg() should be used on enums, and compilers that support
 * it will print the deprecation warning.
 */




	#define __deprecated_msg(_msg) __attribute__((deprecated(_msg)))





	#define __deprecated_enum_msg(_msg) __deprecated_msg(_msg)




/* __unavailable causes the compiler to error out when encountering
 * code using the tagged function of variable.
 */


/* Delete pseudo-keywords wherever they are not available or needed. */





/*
 * We use `__restrict' as a way to define the `restrict' type qualifier
 * without disturbing older software that is unaware of C99 keywords.
 */






/* Compatibility with compilers and environments that don't support the
 * nullability feature.
 */



/*
 * __disable_tail_calls causes the compiler to not perform tail call
 * optimization inside the marked function.
 */






/*
 * __not_tail_called causes the compiler to prevent tail call optimization
 * on statically bound calls to the function.  It has no effect on indirect
 * calls.  Virtual functions, objective-c methods, and functions marked as
 * "always_inline" cannot be marked as __not_tail_called.
 */






/*
 * __result_use_check warns callers of a function that not using the function
 * return value is a bug, i.e. dismissing malloc() return value results in a
 * memory leak.
 */






/*
 * __swift_unavailable causes the compiler to mark a symbol as specifically
 * unavailable in Swift, regardless of any other availability in C.
 */






/* Declaring inline functions within headers is error-prone due to differences
 * across various versions of the C language and extensions.  __header_inline
 * can be used to declare inline functions within system headers.  In cases
 * where you want to force inlining instead of letting the compiler make
 * the decision, you can use __header_always_inline.
 *
 * Be aware that using inline for functions which compilers may also provide
 * builtins can behave differently under various compilers.  If you intend to
 * provide an inline version of such a function, you may want to use a macro
 * instead.
 *
 * The check for !__GNUC__ || __clang__ is because gcc doesn't correctly
 * support c99 inline in some cases:
 * http://gcc.gnu.org/bugzilla/show_bug.cgi?id=55965
 */












/*
 * Compiler-dependent macros that bracket portions of code where the
 * "-Wunreachable-code" warning should be ignored. Please use sparingly.
 */


/*
 * Compiler-dependent macros to declare that functions take printf-like
 * or scanf-like arguments.  They are null except for versions of gcc
 * that are known to support the features properly.  Functions declared
 * with these attributes will cause compilation warnings if there is a
 * mismatch between the format string and subsequent function parameter
 * types.
 */

























/* Source compatibility only, ID string not emitted in object file */
















/*
 * COMPILATION ENVIRONMENTS -- see compat(5) for additional detail
 *
 * DEFAULT	By default newly complied code will get POSIX APIs plus
 *		Apple API extensions in scope.
 *
 *		Most users will use this compilation environment to avoid
 *		behavioral differences between 32 and 64 bit code.
 *
 * LEGACY	Defining _NONSTD_SOURCE will get pre-POSIX APIs plus Apple
 *		API extensions in scope.
 *
 *		This is generally equivalent to the Tiger release compilation
 *		environment, except that it cannot be applied to 64 bit code;
 *		its use is discouraged.
 *
 *		We expect this environment to be deprecated in the future.
 *
 * STRICT	Defining _POSIX_C_SOURCE or _XOPEN_SOURCE restricts the
 *		available APIs to exactly the set of APIs defined by the
 *		corresponding standard, based on the value defined.
 *
 *		A correct, portable definition for _POSIX_C_SOURCE is 200112L.
 *		A correct, portable definition for _XOPEN_SOURCE is 600L.
 *
 *		Apple API extensions are not visible in this environment,
 *		which can cause Apple specific code to fail to compile,
 *		or behave incorrectly if prototypes are not in scope or
 *		warnings about missing prototypes are not enabled or ignored.
 *
 * In any compilation environment, for correct symbol resolution to occur,
 * function prototypes must be in scope.  It is recommended that all Apple
 * tools users add either the "-Wall" or "-Wimplicit-function-declaration"
 * compiler flags to their projects to be warned when a function is being
 * used without a prototype in scope.
 */

/* These settings are particular to each product. */
/* Platform: MacOSX */

/* #undef __DARWIN_ONLY_UNIX_CONFORMANCE (automatically set for 64-bit) */


/*
 * The __DARWIN_ALIAS macros are used to do symbol renaming; they allow
 * legacy code to use the old symbol, thus maintaining binary compatibility
 * while new code can use a standards compliant version of the same function.
 *
 * __DARWIN_ALIAS is used by itself if the function signature has not
 * changed, it is used along with a #ifdef check for __DARWIN_UNIX03
 * if the signature has changed.  Because the __LP64__ environment
 * only supports UNIX03 semantics it causes __DARWIN_UNIX03 to be
 * defined, but causes __DARWIN_ALIAS to do no symbol mangling.
 *
 * As a special case, when XCode is used to target a specific version of the
 * OS, the manifest constant __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
 * will be defined by the compiler, with the digits representing major version
 * time 100 + minor version times 10 (e.g. 10.5 := 1050).  If we are targeting
 * pre-10.5, and it is the default compilation environment, revert the
 * compilation environment to pre-__DARWIN_UNIX03.
 */


















/*
 * symbol suffixes used for symbol versioning
 */


























/*
 * symbol versioning macros
 */















/*
 * symbol release macros
 */

/* Copyright (c) 2010 Apple Inc. All rights reserved.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */












































































































































































































































































































































































/*
 * POSIX.1 requires that the macros we test be defined before any standard
 * header file is included.  This permits us to convert values for feature
 * testing, as necessary, using only _POSIX_C_SOURCE.
 *
 * Here's a quick run-down of the versions:
 *  defined(_POSIX_SOURCE)		1003.1-1988
 *  _POSIX_C_SOURCE == 1L		1003.1-1990
 *  _POSIX_C_SOURCE == 2L		1003.2-1992 C Language Binding Option
 *  _POSIX_C_SOURCE == 199309L		1003.1b-1993
 *  _POSIX_C_SOURCE == 199506L		1003.1c-1995, 1003.1i-1995,
 *					and the omnibus ISO/IEC 9945-1: 1996
 *  _POSIX_C_SOURCE == 200112L		1003.1-2001
 *  _POSIX_C_SOURCE == 200809L		1003.1-2008
 *
 * In addition, the X/Open Portability Guide, which is now the Single UNIX
 * Specification, defines a feature-test macro which indicates the version of
 * that specification, and which subsumes _POSIX_C_SOURCE.
 */

/* Deal with IEEE Std. 1003.1-1990, in which _POSIX_C_SOURCE == 1L. */





/* Deal with IEEE Std. 1003.2-1992, in which _POSIX_C_SOURCE == 2L. */





/* Deal with various X/Open Portability Guides and Single UNIX Spec. */


/*
 * Deal with all versions of POSIX.  The ordering relative to the tests above is
 * important.
 */




/* POSIX C deprecation macros */

/* Copyright (c) 2010 Apple Inc. All rights reserved.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



















































/*
 * Set a single macro which will always be defined and can be used to determine
 * the appropriate namespace.  For POSIX, these values will correspond to
 * _POSIX_C_SOURCE value.  Currently there are two additional levels corresponding
 * to ANSI (_ANSI_SOURCE) and Darwin extensions (_DARWIN_C_SOURCE)
 */











/* If the developer has neither requested a strict language mode nor a version
 * of POSIX, turn on functionality provided by __STDC_WANT_LIB_EXT1__ as part
 * of __DARWIN_C_FULL.
 */




/*
 * long long is not supported in c89 (__STRICT_ANSI__), but g++ -ansi and
 * c99 still want long longs.  While not perfect, we allow long longs for
 * g++.
 */






/*****************************************
 *  Public darwin-specific feature macros
 *****************************************/

/*
 * _DARWIN_FEATURE_64_BIT_INODE indicates that the ino_t type is 64-bit, and
 * structures modified for 64-bit inodes (like struct stat) will be used.
 */




/*
 * _DARWIN_FEATURE_64_ONLY_BIT_INODE indicates that the ino_t type may only
 * be 64-bit; there is no support for 32-bit ino_t when this macro is defined
 * (and non-zero).  There is no struct stat64 either, as the regular
 * struct stat will already be the 64-bit version.
 */




/*
 * _DARWIN_FEATURE_ONLY_VERS_1050 indicates that only those APIs updated
 * in 10.5 exists; no pre-10.5 variants are available.
 */




/*
 * _DARWIN_FEATURE_ONLY_UNIX_CONFORMANCE indicates only UNIX conforming API
 * are available (the legacy BSD APIs are not available)
 */




/*
 * _DARWIN_FEATURE_UNIX_CONFORMANCE indicates whether UNIX conformance is on,
 * and specifies the conformance level (3 is SUSv3)
 */




/* 
 * This macro casts away the qualifier from the variable
 *
 * Note: use at your own risk, removing qualifiers can result in
 * catastrophic run-time failures.
 */




/*
 * __XNU_PRIVATE_EXTERN is a linkage decoration indicating that a symbol can be
 * used from other compilation units, but not other libraries or executables.
 */




/*
 * Architecture validation for current SDK
 */








/*
 * Copyright (c) 2003-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */





/*
 * Copyright (c) 2000-2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



/*
 * This header file contains integer types.  It's intended to also contain
 * flotaing point and other arithmetic types, as needed, later.
 */


typedef __signed char		__int8_t;



typedef unsigned char		__uint8_t;
typedef	short			__int16_t;
typedef	unsigned short		__uint16_t;
typedef int			__int32_t;
typedef unsigned int		__uint32_t;
typedef long long		__int64_t;
typedef unsigned long long	__uint64_t;

typedef long			__darwin_intptr_t;
typedef unsigned int		__darwin_natural_t;

/*
 * The rune type below is declared to be an ``int'' instead of the more natural
 * ``unsigned long'' or ``long''.  Two things are happening here.  It is not
 * unsigned so that EOF (-1) can be naturally assigned to it and used.  Also,
 * it looks like 10646 will be a 31 bit standard.  This means that if your
 * ints cannot hold 32 bits, you will be in trouble.  The reason an int was
 * chosen over a long is that the is*() and to*() routines take ints (says
 * ANSI C), but they use __darwin_ct_rune_t instead of int.  By changing it
 * here, you lose a bit of ANSI conformance, but your programs will still
 * work.
 *
 * NOTE: rune_t is not covered by ANSI nor other standards, and should not
 * be instantiated outside of lib/libc/locale.  Use wchar_t.  wchar_t and
 * rune_t must be the same type.  Also wint_t must be no narrower than
 * wchar_t, and should also be able to hold all members of the largest
 * character set plus one extra value (WEOF). wint_t must be at least 16 bits.
 */

typedef int			__darwin_ct_rune_t;	/* ct_rune_t */

/*
 * mbstate_t is an opaque object to keep conversion state, during multibyte
 * stream conversions.  The content must not be referenced by user programs.
 */
typedef union {
	char		__mbstate8[128];
	long long	_mbstateL;			/* for alignment */
} __mbstate_t;

typedef __mbstate_t		__darwin_mbstate_t;	/* mbstate_t */


typedef long int	__darwin_ptrdiff_t;	/* ptr1 - ptr2 */







typedef long unsigned int		__darwin_size_t;	/* sizeof() */





typedef __builtin_va_list	__darwin_va_list;	/* va_list */





typedef int		__darwin_wchar_t;	/* wchar_t */




typedef __darwin_wchar_t	__darwin_rune_t;	/* rune_t */


typedef int		__darwin_wint_t;	/* wint_t */




typedef unsigned long		__darwin_clock_t;	/* clock() */
typedef __uint32_t		__darwin_socklen_t;	/* socklen_t (duh) */
typedef long			__darwin_ssize_t;	/* byte count or error */
typedef long			__darwin_time_t;	/* time() */








/*
 * Type definitions; takes common type definitions that must be used
 * in multiple header files due to [XSI], removes them from the system
 * space, and puts them in the implementation space.
 */



typedef	__int64_t	__darwin_blkcnt_t;	/* total blocks */
typedef	__int32_t	__darwin_blksize_t;	/* preferred block size */
typedef __int32_t	__darwin_dev_t;		/* dev_t */
typedef unsigned int	__darwin_fsblkcnt_t;	/* Used by statvfs and fstatvfs */
typedef unsigned int	__darwin_fsfilcnt_t;	/* Used by statvfs and fstatvfs */
typedef __uint32_t	__darwin_gid_t;		/* [???] process and group IDs */
typedef __uint32_t	__darwin_id_t;		/* [XSI] pid_t, uid_t, or gid_t*/
typedef __uint64_t	__darwin_ino64_t;	/* [???] Used for 64 bit inodes */

typedef __darwin_ino64_t __darwin_ino_t;	/* [???] Used for inodes */



typedef __darwin_natural_t __darwin_mach_port_name_t; /* Used by mach */
typedef __darwin_mach_port_name_t __darwin_mach_port_t; /* Used by mach */
typedef __uint16_t	__darwin_mode_t;	/* [???] Some file attributes */
typedef __int64_t	__darwin_off_t;		/* [???] Used for file sizes */
typedef __int32_t	__darwin_pid_t;		/* [???] process and group IDs */
typedef __uint32_t	__darwin_sigset_t;	/* [???] signal set */
typedef __int32_t	__darwin_suseconds_t;	/* [???] microseconds */
typedef __uint32_t	__darwin_uid_t;		/* [???] user IDs */
typedef __uint32_t	__darwin_useconds_t;	/* [???] microseconds */
typedef	unsigned char	__darwin_uuid_t[16];
typedef	char	__darwin_uuid_string_t[37];


/*
 * Copyright (c) 2003-2013 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */






// pthread opaque structures


struct __darwin_pthread_handler_rec {
	void (*__routine)(void *);	// Routine to call
	void *__arg;			// Argument to pass
	struct __darwin_pthread_handler_rec *__next;
};

struct _opaque_pthread_attr_t {
	long __sig;
	char __opaque[56];
};

struct _opaque_pthread_cond_t {
	long __sig;
	char __opaque[40];
};

struct _opaque_pthread_condattr_t {
	long __sig;
	char __opaque[8];
};

struct _opaque_pthread_mutex_t {
	long __sig;
	char __opaque[56];
};

struct _opaque_pthread_mutexattr_t {
	long __sig;
	char __opaque[8];
};

struct _opaque_pthread_once_t {
	long __sig;
	char __opaque[8];
};

struct _opaque_pthread_rwlock_t {
	long __sig;
	char __opaque[192];
};

struct _opaque_pthread_rwlockattr_t {
	long __sig;
	char __opaque[16];
};

struct _opaque_pthread_t {
	long __sig;
	struct __darwin_pthread_handler_rec  *__cleanup_stack;
	char __opaque[8176];
};

typedef struct _opaque_pthread_attr_t __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t *__darwin_pthread_t;















typedef	int		__darwin_nl_item;
typedef	int		__darwin_wctrans_t;

typedef	__uint32_t	__darwin_wctype_t;



























/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/* Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved */
/*
 * Copyright (c) 1982, 1986, 1989, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)wait.h	8.2 (Berkeley) 7/10/94
 */
 






/*
 * This file holds definitions relevent to the wait4 system call
 * and the alternate interfaces that use it (wait, wait3, waitpid).
 */

/*
 * [XSI] The type idtype_t shall be defined as an enumeration type whose
 * possible values shall include at least P_ALL, P_PID, and P_PGID.
 */
typedef enum {
	P_ALL,
	P_PID,
	P_PGID
} idtype_t;

/*
 * [XSI] The id_t and pid_t types shall be defined as described
 * in <sys/types.h>
 */

/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef __darwin_pid_t        pid_t; 

/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef __darwin_id_t	id_t;		/* can hold pid_t, gid_t, or uid_t */


/*
 * [XSI] The siginfo_t type shall be defined as described in <signal.h>
 * [XSI] The rusage structure shall be defined as described in <sys/resource.h>
 * [XSI] Inclusion of the <sys/wait.h> header may also make visible all
 * symbols from <signal.h> and <sys/resource.h>
 *
 * NOTE:	This requirement is currently being satisfied by the direct
 *		inclusion of <sys/signal.h> and <sys/resource.h>, below.
 *
 *		Software should not depend on the exposure of anything other
 *		than the types siginfo_t and struct rusage as a result of
 *		this inclusion.  If you depend on any types or manifest
 *		values othe than siginfo_t and struct rusage from either of
 *		those files, you should explicitly include them yourself, as
 *		well, or in future releases your stware may not compile
 *		without modification.
 */

/*
 * Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/* Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved */
/*
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)signal.h	8.2 (Berkeley) 1/21/94
 */






/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */




































/*
 * Copyright (c) 2007-2016 by Apple Inc.. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
 

    #define __attribute__((availability(_target, _availability)))
    



/* for use to document app extension usage */

  #if 1
    
    #define   
  




    #define 
    






/* for use marking APIs available info for Mac OSX */

  #if 1
    
    #define __OSX_AVAILABLE(_vers)               __attribute__((availability(macosx,introduced=_vers)))
    
  #endif







  #define __OSX_AVAILABLE(_vers)







/* for use marking APIs available info for iOS */

  #if 1
    
    #define __IOS_PROHIBITED                     __attribute__((availability(ios,unavailable)))
    
    #define __IOS_DEPRECATED(_start, _dep, _msg) __attribute__((availability(ios,introduced=_start))) 
  







  #define __IOS_PROHIBITED







  #define __IOS_DEPRECATED(_start, _dep, _msg)



/* for use marking APIs available info for tvOS */

  #if 1
    
    #define __TVOS_PROHIBITED                     __attribute__((availability(tvos,unavailable)))
    
    #define __TVOS_DEPRECATED(_start, _dep, _msg) __attribute__((availability(tvos,introduced=_start))) 
  







  #define __TVOS_PROHIBITED







  #define __TVOS_DEPRECATED(_start, _dep, _msg)



/* for use marking APIs available info for Watch OS */

  #if 1
    
    #define __WATCHOS_PROHIBITED                     __attribute__((availability(watchos,unavailable)))
    
    #define __WATCHOS_DEPRECATED(_start, _dep, _msg) __attribute__((availability(watchos,introduced=_start))) 
  







  #define __WATCHOS_PROHIBITED







  #define __WATCHOS_DEPRECATED(_start, _dep, _msg)



/* for use marking APIs unavailable for swift */

  #if 1
    
    #define __SWIFT_UNAVAILABLE_MSG(_msg)         
  







  #define __SWIFT_UNAVAILABLE_MSG(_msg)



/*
 Macros for defining which versions/platform a given symbol can be used.
 
 @see http://clang.llvm.org/docs/AttributeReference.html#availability
 
 * Note that these macros are only compatible with clang compilers that
 * support the following target selection options:
 *
 * -mmacosx-version-min
 * -miphoneos-version-min
 * -mwatchos-version-min
 * -mtvos-version-min
 * -mbridgeos-version-min
 */


 #if 1

    /*
     * API Introductions
     *
     * Use to specify the release that a particular API became available.
     *
     * Platform names:
     *   macos, ios, tvos, watchos
     *
     * Examples:
     *    __API_AVAILABLE(macos(10.10))
     *    __API_AVAILABLE(macos(10.9), ios(10.0))
     *    __API_AVAILABLE(macos(10.4), ios(8.0), watchos(2.0), tvos(10.0))
     */
    


    /*
     * API Deprecations
     *
     * Use to specify the release that a particular API became unavailable.
     *
     * Platform names:
     *   macos, ios, tvos, watchos
     *
     * Examples:
     *
     *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8))
     *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8), ios(2.0, 3.0), watchos(2.0, 3.0), tvos(9.0, 10.0))
     *
     *    __API_DEPRECATED_WITH_REPLACEMENT("-setName:", tvos(10.0, 10.4), ios(9.0, 10.0))
     *    __API_DEPRECATED_WITH_REPLACEMENT("SomeClassName", macos(10.4, 10.6), watchos(2.0, 3.0))
     */
    
    #define  __API_DEPRECATED_REP_GET_MACRO(__VA_ARGS__,__API_DEPRECATED_REP6,__API_DEPRECATED_REP5,__API_DEPRECATED_REP4,__API_DEPRECATED_REP3,__API_DEPRECATED_REP2,__API_DEPRECATED_REP1)(__VA_ARGS__)

    /*
     * API Unavailability
     * Use to specify that an API is unavailable for a particular platform.
     *
     * Example:
     *    __API_UNAVAILABLE(macos)
     *    __API_UNAVAILABLE(watchos, tvos)
     */
    
 #else 

    /* 
     * Evaluate to nothing for compilers that don't support availability.
     */
    
    
    #define __API_DEPRECATED_MSG1(...)
    
    #define __API_UNAVAILABLE_GET_MACRO(...,__API_UNAVAILABLE4,__API_UNAVAILABLE3,__API_UNAVAILABLE2,__API_UNAVAILABLE1)(...)
 


    /* 
     * Evaluate to nothing for compilers that don't support clang language extensions.
     */
    
    
    #define __API_DEPRECATED_MSG1(...)
    
    #define __API_UNAVAILABLE_GET_MACRO(...,__API_UNAVAILABLE4,__API_UNAVAILABLE3,__API_UNAVAILABLE2,__API_UNAVAILABLE1)(...)













/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */





/*
 * Copyright (c) 2000-2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 */







typedef int sig_atomic_t; 















/*
 * Language spec sez we must list exactly one parameter, even though we
 * actually supply three.  Ugh!
 * SIG_HOLD is chosen to avoid KERN_SIG_* values in <sys/signalvar.h>
 */






/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */







/*
 * Copyright (c) 2017 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */






/*
 * Copyright (c) 2004-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * @OSF_COPYRIGHT@
 */






/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright 1995 NeXT Computer, Inc. All rights reserved.
 */





/*
 * Copyright (c) 2000-2008 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright 1995 NeXT Computer, Inc. All rights reserved.
 */
/*
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)types.h	8.3 (Berkeley) 1/5/94
 */







/*
 * Basic integral types.  Omit the typedef if
 * not possible for a machine/compiler combination.
 */

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


typedef	__signed char		int8_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


typedef	short			int16_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


typedef	int			int32_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


typedef	long long		int64_t;



/*
 * Copyright (c) 2016 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


typedef	unsigned char		u_int8_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


typedef	unsigned short			u_int16_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


typedef	unsigned int		u_int32_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


typedef	unsigned long long	u_int64_t;



typedef int64_t			register_t;





/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright 1995 NeXT Computer, Inc. All rights reserved.
 */


typedef __darwin_intptr_t	intptr_t;

/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


typedef unsigned long		uintptr_t;



/* These types are used for reserving the largest possible size. */
typedef u_int64_t		user_addr_t;	
typedef u_int64_t		user_size_t;	
typedef int64_t			user_ssize_t;
typedef int64_t			user_long_t;
typedef u_int64_t		user_ulong_t;
typedef int64_t			user_time_t;
typedef int64_t			user_off_t;






/* This defines the size of syscall arguments after copying into the kernel: */
typedef u_int64_t		syscall_arg_t;








/*
 * i386 is the structure that is exported to user threads for 
 * use in status/mutate calls.  This structure should never change.
 *
 */



struct __darwin_i386_thread_state
{
    unsigned int	__eax;
    unsigned int	__ebx;
    unsigned int	__ecx;
    unsigned int	__edx;
    unsigned int	__edi;
    unsigned int	__esi;
    unsigned int	__ebp;
    unsigned int	__esp;
    unsigned int	__ss;
    unsigned int	__eflags;
    unsigned int	__eip;
    unsigned int	__cs;
    unsigned int	__ds;
    unsigned int	__es;
    unsigned int	__fs;
    unsigned int	__gs;
};


/* This structure should be double-word aligned for performance */



struct __darwin_fp_control
{
    unsigned short		__invalid	:1,
    				__denorm	:1,
				__zdiv		:1,
				__ovrfl		:1,
				__undfl		:1,
				__precis	:1,
						:2,
				__pc		:2,





				__rc		:2,






					/*inf*/	:1,
						:3;
};
typedef struct __darwin_fp_control	__darwin_fp_control_t;


/*
 * Status word.
 */



struct __darwin_fp_status
{
    unsigned short		__invalid	:1,
    				__denorm	:1,
				__zdiv		:1,
				__ovrfl		:1,
				__undfl		:1,
				__precis	:1,
				__stkflt	:1,
				__errsumm	:1,
				__c0		:1,
				__c1		:1,
				__c2		:1,
				__tos		:3,
				__c3		:1,
				__busy		:1;
};
typedef struct __darwin_fp_status	__darwin_fp_status_t;

				
/* defn of 80bit x87 FPU or MMX register  */



struct __darwin_mmst_reg
{
	char	__mmst_reg[10];
	char	__mmst_rsrv[6];
};










/* defn of 128 bit XMM regs */



struct __darwin_xmm_reg
{
	char		__xmm_reg[16];
};








/* defn of 256 bit YMM regs */



struct __darwin_ymm_reg
{
	char		__ymm_reg[32];
};








/* defn of 512 bit ZMM regs */



struct __darwin_zmm_reg
{
	char		__zmm_reg[64];
};










struct __darwin_opmask_reg
{
	char		__opmask_reg[8];
};








/* 
 * Floating point state.
 */







struct __darwin_i386_float_state
{
	int 			__fpu_reserved[2];
	struct __darwin_fp_control	__fpu_fcw;		/* x87 FPU control word */
	struct __darwin_fp_status	__fpu_fsw;		/* x87 FPU status word */
	__uint8_t		__fpu_ftw;		/* x87 FPU tag word */
	__uint8_t		__fpu_rsrv1;		/* reserved */ 
	__uint16_t		__fpu_fop;		/* x87 FPU Opcode */
	__uint32_t		__fpu_ip;		/* x87 FPU Instruction Pointer offset */
	__uint16_t		__fpu_cs;		/* x87 FPU Instruction Pointer Selector */
	__uint16_t		__fpu_rsrv2;		/* reserved */
	__uint32_t		__fpu_dp;		/* x87 FPU Instruction Operand(Data) Pointer offset */
	__uint16_t		__fpu_ds;		/* x87 FPU Instruction Operand(Data) Pointer Selector */
	__uint16_t		__fpu_rsrv3;		/* reserved */
	__uint32_t		__fpu_mxcsr;		/* MXCSR Register state */
	__uint32_t		__fpu_mxcsrmask;	/* MXCSR mask */
	struct __darwin_mmst_reg	__fpu_stmm0;		/* ST0/MM0   */
	struct __darwin_mmst_reg	__fpu_stmm1;		/* ST1/MM1  */
	struct __darwin_mmst_reg	__fpu_stmm2;		/* ST2/MM2  */
	struct __darwin_mmst_reg	__fpu_stmm3;		/* ST3/MM3  */
	struct __darwin_mmst_reg	__fpu_stmm4;		/* ST4/MM4  */
	struct __darwin_mmst_reg	__fpu_stmm5;		/* ST5/MM5  */
	struct __darwin_mmst_reg	__fpu_stmm6;		/* ST6/MM6  */
	struct __darwin_mmst_reg	__fpu_stmm7;		/* ST7/MM7  */
	struct __darwin_xmm_reg		__fpu_xmm0;		/* XMM 0  */
	struct __darwin_xmm_reg		__fpu_xmm1;		/* XMM 1  */
	struct __darwin_xmm_reg		__fpu_xmm2;		/* XMM 2  */
	struct __darwin_xmm_reg		__fpu_xmm3;		/* XMM 3  */
	struct __darwin_xmm_reg		__fpu_xmm4;		/* XMM 4  */
	struct __darwin_xmm_reg		__fpu_xmm5;		/* XMM 5  */
	struct __darwin_xmm_reg		__fpu_xmm6;		/* XMM 6  */
	struct __darwin_xmm_reg		__fpu_xmm7;		/* XMM 7  */
	char			__fpu_rsrv4[14*16];	/* reserved */
	int 			__fpu_reserved1;
};


struct __darwin_i386_avx_state
{
	int 			__fpu_reserved[2];
	struct __darwin_fp_control	__fpu_fcw;		/* x87 FPU control word */
	struct __darwin_fp_status	__fpu_fsw;		/* x87 FPU status word */
	__uint8_t		__fpu_ftw;		/* x87 FPU tag word */
	__uint8_t		__fpu_rsrv1;		/* reserved */ 
	__uint16_t		__fpu_fop;		/* x87 FPU Opcode */
	__uint32_t		__fpu_ip;		/* x87 FPU Instruction Pointer offset */
	__uint16_t		__fpu_cs;		/* x87 FPU Instruction Pointer Selector */
	__uint16_t		__fpu_rsrv2;		/* reserved */
	__uint32_t		__fpu_dp;		/* x87 FPU Instruction Operand(Data) Pointer offset */
	__uint16_t		__fpu_ds;		/* x87 FPU Instruction Operand(Data) Pointer Selector */
	__uint16_t		__fpu_rsrv3;		/* reserved */
	__uint32_t		__fpu_mxcsr;		/* MXCSR Register state */
	__uint32_t		__fpu_mxcsrmask;	/* MXCSR mask */
	struct __darwin_mmst_reg	__fpu_stmm0;		/* ST0/MM0   */
	struct __darwin_mmst_reg	__fpu_stmm1;		/* ST1/MM1  */
	struct __darwin_mmst_reg	__fpu_stmm2;		/* ST2/MM2  */
	struct __darwin_mmst_reg	__fpu_stmm3;		/* ST3/MM3  */
	struct __darwin_mmst_reg	__fpu_stmm4;		/* ST4/MM4  */
	struct __darwin_mmst_reg	__fpu_stmm5;		/* ST5/MM5  */
	struct __darwin_mmst_reg	__fpu_stmm6;		/* ST6/MM6  */
	struct __darwin_mmst_reg	__fpu_stmm7;		/* ST7/MM7  */
	struct __darwin_xmm_reg		__fpu_xmm0;		/* XMM 0  */
	struct __darwin_xmm_reg		__fpu_xmm1;		/* XMM 1  */
	struct __darwin_xmm_reg		__fpu_xmm2;		/* XMM 2  */
	struct __darwin_xmm_reg		__fpu_xmm3;		/* XMM 3  */
	struct __darwin_xmm_reg		__fpu_xmm4;		/* XMM 4  */
	struct __darwin_xmm_reg		__fpu_xmm5;		/* XMM 5  */
	struct __darwin_xmm_reg		__fpu_xmm6;		/* XMM 6  */
	struct __darwin_xmm_reg		__fpu_xmm7;		/* XMM 7  */
	char			__fpu_rsrv4[14*16];	/* reserved */
	int 			__fpu_reserved1;
	char			__avx_reserved1[64];
	struct __darwin_xmm_reg		__fpu_ymmh0;		/* YMMH 0  */
	struct __darwin_xmm_reg		__fpu_ymmh1;		/* YMMH 1  */
	struct __darwin_xmm_reg		__fpu_ymmh2;		/* YMMH 2  */
	struct __darwin_xmm_reg		__fpu_ymmh3;		/* YMMH 3  */
	struct __darwin_xmm_reg		__fpu_ymmh4;		/* YMMH 4  */
	struct __darwin_xmm_reg		__fpu_ymmh5;		/* YMMH 5  */
	struct __darwin_xmm_reg		__fpu_ymmh6;		/* YMMH 6  */
	struct __darwin_xmm_reg		__fpu_ymmh7;		/* YMMH 7  */
};


struct __darwin_i386_avx512_state
{
	int 			__fpu_reserved[2];
	struct __darwin_fp_control	__fpu_fcw;		/* x87 FPU control word */
	struct __darwin_fp_status	__fpu_fsw;		/* x87 FPU status word */
	__uint8_t		__fpu_ftw;		/* x87 FPU tag word */
	__uint8_t		__fpu_rsrv1;		/* reserved */ 
	__uint16_t		__fpu_fop;		/* x87 FPU Opcode */
	__uint32_t		__fpu_ip;		/* x87 FPU Instruction Pointer offset */
	__uint16_t		__fpu_cs;		/* x87 FPU Instruction Pointer Selector */
	__uint16_t		__fpu_rsrv2;		/* reserved */
	__uint32_t		__fpu_dp;		/* x87 FPU Instruction Operand(Data) Pointer offset */
	__uint16_t		__fpu_ds;		/* x87 FPU Instruction Operand(Data) Pointer Selector */
	__uint16_t		__fpu_rsrv3;		/* reserved */
	__uint32_t		__fpu_mxcsr;		/* MXCSR Register state */
	__uint32_t		__fpu_mxcsrmask;	/* MXCSR mask */
	struct __darwin_mmst_reg	__fpu_stmm0;		/* ST0/MM0   */
	struct __darwin_mmst_reg	__fpu_stmm1;		/* ST1/MM1  */
	struct __darwin_mmst_reg	__fpu_stmm2;		/* ST2/MM2  */
	struct __darwin_mmst_reg	__fpu_stmm3;		/* ST3/MM3  */
	struct __darwin_mmst_reg	__fpu_stmm4;		/* ST4/MM4  */
	struct __darwin_mmst_reg	__fpu_stmm5;		/* ST5/MM5  */
	struct __darwin_mmst_reg	__fpu_stmm6;		/* ST6/MM6  */
	struct __darwin_mmst_reg	__fpu_stmm7;		/* ST7/MM7  */
	struct __darwin_xmm_reg		__fpu_xmm0;		/* XMM 0  */
	struct __darwin_xmm_reg		__fpu_xmm1;		/* XMM 1  */
	struct __darwin_xmm_reg		__fpu_xmm2;		/* XMM 2  */
	struct __darwin_xmm_reg		__fpu_xmm3;		/* XMM 3  */
	struct __darwin_xmm_reg		__fpu_xmm4;		/* XMM 4  */
	struct __darwin_xmm_reg		__fpu_xmm5;		/* XMM 5  */
	struct __darwin_xmm_reg		__fpu_xmm6;		/* XMM 6  */
	struct __darwin_xmm_reg		__fpu_xmm7;		/* XMM 7  */
	char			__fpu_rsrv4[14*16];	/* reserved */
	int 			__fpu_reserved1;
	char			__avx_reserved1[64];
	struct __darwin_xmm_reg		__fpu_ymmh0;		/* YMMH 0  */
	struct __darwin_xmm_reg		__fpu_ymmh1;		/* YMMH 1  */
	struct __darwin_xmm_reg		__fpu_ymmh2;		/* YMMH 2  */
	struct __darwin_xmm_reg		__fpu_ymmh3;		/* YMMH 3  */
	struct __darwin_xmm_reg		__fpu_ymmh4;		/* YMMH 4  */
	struct __darwin_xmm_reg		__fpu_ymmh5;		/* YMMH 5  */
	struct __darwin_xmm_reg		__fpu_ymmh6;		/* YMMH 6  */
	struct __darwin_xmm_reg		__fpu_ymmh7;		/* YMMH 7  */
	struct __darwin_opmask_reg	__fpu_k0;		/* K0 */
	struct __darwin_opmask_reg	__fpu_k1;		/* K1 */
	struct __darwin_opmask_reg	__fpu_k2;		/* K2 */
	struct __darwin_opmask_reg	__fpu_k3;		/* K3 */
	struct __darwin_opmask_reg	__fpu_k4;		/* K4 */
	struct __darwin_opmask_reg	__fpu_k5;		/* K5 */
	struct __darwin_opmask_reg	__fpu_k6;		/* K6 */
	struct __darwin_opmask_reg	__fpu_k7;		/* K7 */
	struct __darwin_ymm_reg		__fpu_zmmh0;		/* ZMMH 0  */
	struct __darwin_ymm_reg		__fpu_zmmh1;		/* ZMMH 1  */
	struct __darwin_ymm_reg		__fpu_zmmh2;		/* ZMMH 2  */
	struct __darwin_ymm_reg		__fpu_zmmh3;		/* ZMMH 3  */
	struct __darwin_ymm_reg		__fpu_zmmh4;		/* ZMMH 4  */
	struct __darwin_ymm_reg		__fpu_zmmh5;		/* ZMMH 5  */
	struct __darwin_ymm_reg		__fpu_zmmh6;		/* ZMMH 6  */
	struct __darwin_ymm_reg		__fpu_zmmh7;		/* ZMMH 7  */
};





struct __darwin_i386_exception_state
{
	__uint16_t	__trapno;
	__uint16_t	__cpu;
	__uint32_t	__err;
	__uint32_t	__faultvaddr;
};




struct __darwin_x86_debug_state32
{
	unsigned int	__dr0;
	unsigned int	__dr1;
	unsigned int	__dr2;
	unsigned int	__dr3;
	unsigned int	__dr4;
	unsigned int	__dr5;
	unsigned int	__dr6;
	unsigned int	__dr7;
};


/*
 * 64 bit versions of the above
 */



struct __darwin_x86_thread_state64
{
	__uint64_t	__rax;
	__uint64_t	__rbx;
	__uint64_t	__rcx;
	__uint64_t	__rdx;
	__uint64_t	__rdi;
	__uint64_t	__rsi;
	__uint64_t	__rbp;
	__uint64_t	__rsp;
	__uint64_t	__r8;
	__uint64_t	__r9;
	__uint64_t	__r10;
	__uint64_t	__r11;
	__uint64_t	__r12;
	__uint64_t	__r13;
	__uint64_t	__r14;
	__uint64_t	__r15;
	__uint64_t	__rip;
	__uint64_t	__rflags;
	__uint64_t	__cs;
	__uint64_t	__fs;
	__uint64_t	__gs;
};





struct __darwin_x86_float_state64
{
	int 			__fpu_reserved[2];
	struct __darwin_fp_control	__fpu_fcw;		/* x87 FPU control word */
	struct __darwin_fp_status	__fpu_fsw;		/* x87 FPU status word */
	__uint8_t		__fpu_ftw;		/* x87 FPU tag word */
	__uint8_t		__fpu_rsrv1;		/* reserved */ 
	__uint16_t		__fpu_fop;		/* x87 FPU Opcode */

	/* x87 FPU Instruction Pointer */
	__uint32_t		__fpu_ip;		/* offset */
	__uint16_t		__fpu_cs;		/* Selector */

	__uint16_t		__fpu_rsrv2;		/* reserved */

	/* x87 FPU Instruction Operand(Data) Pointer */
	__uint32_t		__fpu_dp;		/* offset */
	__uint16_t		__fpu_ds;		/* Selector */

	__uint16_t		__fpu_rsrv3;		/* reserved */
	__uint32_t		__fpu_mxcsr;		/* MXCSR Register state */
	__uint32_t		__fpu_mxcsrmask;	/* MXCSR mask */
	struct __darwin_mmst_reg	__fpu_stmm0;		/* ST0/MM0   */
	struct __darwin_mmst_reg	__fpu_stmm1;		/* ST1/MM1  */
	struct __darwin_mmst_reg	__fpu_stmm2;		/* ST2/MM2  */
	struct __darwin_mmst_reg	__fpu_stmm3;		/* ST3/MM3  */
	struct __darwin_mmst_reg	__fpu_stmm4;		/* ST4/MM4  */
	struct __darwin_mmst_reg	__fpu_stmm5;		/* ST5/MM5  */
	struct __darwin_mmst_reg	__fpu_stmm6;		/* ST6/MM6  */
	struct __darwin_mmst_reg	__fpu_stmm7;		/* ST7/MM7  */
	struct __darwin_xmm_reg		__fpu_xmm0;		/* XMM 0  */
	struct __darwin_xmm_reg		__fpu_xmm1;		/* XMM 1  */
	struct __darwin_xmm_reg		__fpu_xmm2;		/* XMM 2  */
	struct __darwin_xmm_reg		__fpu_xmm3;		/* XMM 3  */
	struct __darwin_xmm_reg		__fpu_xmm4;		/* XMM 4  */
	struct __darwin_xmm_reg		__fpu_xmm5;		/* XMM 5  */
	struct __darwin_xmm_reg		__fpu_xmm6;		/* XMM 6  */
	struct __darwin_xmm_reg		__fpu_xmm7;		/* XMM 7  */
	struct __darwin_xmm_reg		__fpu_xmm8;		/* XMM 8  */
	struct __darwin_xmm_reg		__fpu_xmm9;		/* XMM 9  */
	struct __darwin_xmm_reg		__fpu_xmm10;		/* XMM 10  */
	struct __darwin_xmm_reg		__fpu_xmm11;		/* XMM 11 */
	struct __darwin_xmm_reg		__fpu_xmm12;		/* XMM 12  */
	struct __darwin_xmm_reg		__fpu_xmm13;		/* XMM 13  */
	struct __darwin_xmm_reg		__fpu_xmm14;		/* XMM 14  */
	struct __darwin_xmm_reg		__fpu_xmm15;		/* XMM 15  */
	char			__fpu_rsrv4[6*16];	/* reserved */
	int 			__fpu_reserved1;
};


struct __darwin_x86_avx_state64
{
	int 			__fpu_reserved[2];
	struct __darwin_fp_control	__fpu_fcw;		/* x87 FPU control word */
	struct __darwin_fp_status	__fpu_fsw;		/* x87 FPU status word */
	__uint8_t		__fpu_ftw;		/* x87 FPU tag word */
	__uint8_t		__fpu_rsrv1;		/* reserved */ 
	__uint16_t		__fpu_fop;		/* x87 FPU Opcode */

	/* x87 FPU Instruction Pointer */
	__uint32_t		__fpu_ip;		/* offset */
	__uint16_t		__fpu_cs;		/* Selector */

	__uint16_t		__fpu_rsrv2;		/* reserved */

	/* x87 FPU Instruction Operand(Data) Pointer */
	__uint32_t		__fpu_dp;		/* offset */
	__uint16_t		__fpu_ds;		/* Selector */

	__uint16_t		__fpu_rsrv3;		/* reserved */
	__uint32_t		__fpu_mxcsr;		/* MXCSR Register state */
	__uint32_t		__fpu_mxcsrmask;	/* MXCSR mask */
	struct __darwin_mmst_reg	__fpu_stmm0;		/* ST0/MM0   */
	struct __darwin_mmst_reg	__fpu_stmm1;		/* ST1/MM1  */
	struct __darwin_mmst_reg	__fpu_stmm2;		/* ST2/MM2  */
	struct __darwin_mmst_reg	__fpu_stmm3;		/* ST3/MM3  */
	struct __darwin_mmst_reg	__fpu_stmm4;		/* ST4/MM4  */
	struct __darwin_mmst_reg	__fpu_stmm5;		/* ST5/MM5  */
	struct __darwin_mmst_reg	__fpu_stmm6;		/* ST6/MM6  */
	struct __darwin_mmst_reg	__fpu_stmm7;		/* ST7/MM7  */
	struct __darwin_xmm_reg		__fpu_xmm0;		/* XMM 0  */
	struct __darwin_xmm_reg		__fpu_xmm1;		/* XMM 1  */
	struct __darwin_xmm_reg		__fpu_xmm2;		/* XMM 2  */
	struct __darwin_xmm_reg		__fpu_xmm3;		/* XMM 3  */
	struct __darwin_xmm_reg		__fpu_xmm4;		/* XMM 4  */
	struct __darwin_xmm_reg		__fpu_xmm5;		/* XMM 5  */
	struct __darwin_xmm_reg		__fpu_xmm6;		/* XMM 6  */
	struct __darwin_xmm_reg		__fpu_xmm7;		/* XMM 7  */
	struct __darwin_xmm_reg		__fpu_xmm8;		/* XMM 8  */
	struct __darwin_xmm_reg		__fpu_xmm9;		/* XMM 9  */
	struct __darwin_xmm_reg		__fpu_xmm10;		/* XMM 10  */
	struct __darwin_xmm_reg		__fpu_xmm11;		/* XMM 11 */
	struct __darwin_xmm_reg		__fpu_xmm12;		/* XMM 12  */
	struct __darwin_xmm_reg		__fpu_xmm13;		/* XMM 13  */
	struct __darwin_xmm_reg		__fpu_xmm14;		/* XMM 14  */
	struct __darwin_xmm_reg		__fpu_xmm15;		/* XMM 15  */
	char			__fpu_rsrv4[6*16];	/* reserved */
	int 			__fpu_reserved1;
	char			__avx_reserved1[64];
	struct __darwin_xmm_reg		__fpu_ymmh0;		/* YMMH 0  */
	struct __darwin_xmm_reg		__fpu_ymmh1;		/* YMMH 1  */
	struct __darwin_xmm_reg		__fpu_ymmh2;		/* YMMH 2  */
	struct __darwin_xmm_reg		__fpu_ymmh3;		/* YMMH 3  */
	struct __darwin_xmm_reg		__fpu_ymmh4;		/* YMMH 4  */
	struct __darwin_xmm_reg		__fpu_ymmh5;		/* YMMH 5  */
	struct __darwin_xmm_reg		__fpu_ymmh6;		/* YMMH 6  */
	struct __darwin_xmm_reg		__fpu_ymmh7;		/* YMMH 7  */
	struct __darwin_xmm_reg		__fpu_ymmh8;		/* YMMH 8  */
	struct __darwin_xmm_reg		__fpu_ymmh9;		/* YMMH 9  */
	struct __darwin_xmm_reg		__fpu_ymmh10;		/* YMMH 10  */
	struct __darwin_xmm_reg		__fpu_ymmh11;		/* YMMH 11  */
	struct __darwin_xmm_reg		__fpu_ymmh12;		/* YMMH 12  */
	struct __darwin_xmm_reg		__fpu_ymmh13;		/* YMMH 13  */
	struct __darwin_xmm_reg		__fpu_ymmh14;		/* YMMH 14  */
	struct __darwin_xmm_reg		__fpu_ymmh15;		/* YMMH 15  */
};


struct __darwin_x86_avx512_state64
{
	int 			__fpu_reserved[2];
	struct __darwin_fp_control	__fpu_fcw;		/* x87 FPU control word */
	struct __darwin_fp_status	__fpu_fsw;		/* x87 FPU status word */
	__uint8_t		__fpu_ftw;		/* x87 FPU tag word */
	__uint8_t		__fpu_rsrv1;		/* reserved */ 
	__uint16_t		__fpu_fop;		/* x87 FPU Opcode */

	/* x87 FPU Instruction Pointer */
	__uint32_t		__fpu_ip;		/* offset */
	__uint16_t		__fpu_cs;		/* Selector */

	__uint16_t		__fpu_rsrv2;		/* reserved */

	/* x87 FPU Instruction Operand(Data) Pointer */
	__uint32_t		__fpu_dp;		/* offset */
	__uint16_t		__fpu_ds;		/* Selector */

	__uint16_t		__fpu_rsrv3;		/* reserved */
	__uint32_t		__fpu_mxcsr;		/* MXCSR Register state */
	__uint32_t		__fpu_mxcsrmask;	/* MXCSR mask */
	struct __darwin_mmst_reg	__fpu_stmm0;		/* ST0/MM0   */
	struct __darwin_mmst_reg	__fpu_stmm1;		/* ST1/MM1  */
	struct __darwin_mmst_reg	__fpu_stmm2;		/* ST2/MM2  */
	struct __darwin_mmst_reg	__fpu_stmm3;		/* ST3/MM3  */
	struct __darwin_mmst_reg	__fpu_stmm4;		/* ST4/MM4  */
	struct __darwin_mmst_reg	__fpu_stmm5;		/* ST5/MM5  */
	struct __darwin_mmst_reg	__fpu_stmm6;		/* ST6/MM6  */
	struct __darwin_mmst_reg	__fpu_stmm7;		/* ST7/MM7  */
	struct __darwin_xmm_reg		__fpu_xmm0;		/* XMM 0  */
	struct __darwin_xmm_reg		__fpu_xmm1;		/* XMM 1  */
	struct __darwin_xmm_reg		__fpu_xmm2;		/* XMM 2  */
	struct __darwin_xmm_reg		__fpu_xmm3;		/* XMM 3  */
	struct __darwin_xmm_reg		__fpu_xmm4;		/* XMM 4  */
	struct __darwin_xmm_reg		__fpu_xmm5;		/* XMM 5  */
	struct __darwin_xmm_reg		__fpu_xmm6;		/* XMM 6  */
	struct __darwin_xmm_reg		__fpu_xmm7;		/* XMM 7  */
	struct __darwin_xmm_reg		__fpu_xmm8;		/* XMM 8  */
	struct __darwin_xmm_reg		__fpu_xmm9;		/* XMM 9  */
	struct __darwin_xmm_reg		__fpu_xmm10;		/* XMM 10  */
	struct __darwin_xmm_reg		__fpu_xmm11;		/* XMM 11 */
	struct __darwin_xmm_reg		__fpu_xmm12;		/* XMM 12  */
	struct __darwin_xmm_reg		__fpu_xmm13;		/* XMM 13  */
	struct __darwin_xmm_reg		__fpu_xmm14;		/* XMM 14  */
	struct __darwin_xmm_reg		__fpu_xmm15;		/* XMM 15  */
	char			__fpu_rsrv4[6*16];	/* reserved */
	int 			__fpu_reserved1;
	char			__avx_reserved1[64];
	struct __darwin_xmm_reg		__fpu_ymmh0;		/* YMMH 0  */
	struct __darwin_xmm_reg		__fpu_ymmh1;		/* YMMH 1  */
	struct __darwin_xmm_reg		__fpu_ymmh2;		/* YMMH 2  */
	struct __darwin_xmm_reg		__fpu_ymmh3;		/* YMMH 3  */
	struct __darwin_xmm_reg		__fpu_ymmh4;		/* YMMH 4  */
	struct __darwin_xmm_reg		__fpu_ymmh5;		/* YMMH 5  */
	struct __darwin_xmm_reg		__fpu_ymmh6;		/* YMMH 6  */
	struct __darwin_xmm_reg		__fpu_ymmh7;		/* YMMH 7  */
	struct __darwin_xmm_reg		__fpu_ymmh8;		/* YMMH 8  */
	struct __darwin_xmm_reg		__fpu_ymmh9;		/* YMMH 9  */
	struct __darwin_xmm_reg		__fpu_ymmh10;		/* YMMH 10  */
	struct __darwin_xmm_reg		__fpu_ymmh11;		/* YMMH 11  */
	struct __darwin_xmm_reg		__fpu_ymmh12;		/* YMMH 12  */
	struct __darwin_xmm_reg		__fpu_ymmh13;		/* YMMH 13  */
	struct __darwin_xmm_reg		__fpu_ymmh14;		/* YMMH 14  */
	struct __darwin_xmm_reg		__fpu_ymmh15;		/* YMMH 15  */
	struct __darwin_opmask_reg	__fpu_k0;		/* K0 */
	struct __darwin_opmask_reg	__fpu_k1;		/* K1 */
	struct __darwin_opmask_reg	__fpu_k2;		/* K2 */
	struct __darwin_opmask_reg	__fpu_k3;		/* K3 */
	struct __darwin_opmask_reg	__fpu_k4;		/* K4 */
	struct __darwin_opmask_reg	__fpu_k5;		/* K5 */
	struct __darwin_opmask_reg	__fpu_k6;		/* K6 */
	struct __darwin_opmask_reg	__fpu_k7;		/* K7 */
	struct __darwin_ymm_reg		__fpu_zmmh0;		/* ZMMH 0  */
	struct __darwin_ymm_reg		__fpu_zmmh1;		/* ZMMH 1  */
	struct __darwin_ymm_reg		__fpu_zmmh2;		/* ZMMH 2  */
	struct __darwin_ymm_reg		__fpu_zmmh3;		/* ZMMH 3  */
	struct __darwin_ymm_reg		__fpu_zmmh4;		/* ZMMH 4  */
	struct __darwin_ymm_reg		__fpu_zmmh5;		/* ZMMH 5  */
	struct __darwin_ymm_reg		__fpu_zmmh6;		/* ZMMH 6  */
	struct __darwin_ymm_reg		__fpu_zmmh7;		/* ZMMH 7  */
	struct __darwin_ymm_reg		__fpu_zmmh8;		/* ZMMH 8  */
	struct __darwin_ymm_reg		__fpu_zmmh9;		/* ZMMH 9  */
	struct __darwin_ymm_reg		__fpu_zmmh10;		/* ZMMH 10  */
	struct __darwin_ymm_reg		__fpu_zmmh11;		/* ZMMH 11  */
	struct __darwin_ymm_reg		__fpu_zmmh12;		/* ZMMH 12  */
	struct __darwin_ymm_reg		__fpu_zmmh13;		/* ZMMH 13  */
	struct __darwin_ymm_reg		__fpu_zmmh14;		/* ZMMH 14  */
	struct __darwin_ymm_reg		__fpu_zmmh15;		/* ZMMH 15  */
	struct __darwin_zmm_reg		__fpu_zmm16;		/* ZMM 16  */
	struct __darwin_zmm_reg		__fpu_zmm17;		/* ZMM 17  */
	struct __darwin_zmm_reg		__fpu_zmm18;		/* ZMM 18  */
	struct __darwin_zmm_reg		__fpu_zmm19;		/* ZMM 19  */
	struct __darwin_zmm_reg		__fpu_zmm20;		/* ZMM 20  */
	struct __darwin_zmm_reg		__fpu_zmm21;		/* ZMM 21  */
	struct __darwin_zmm_reg		__fpu_zmm22;		/* ZMM 22  */
	struct __darwin_zmm_reg		__fpu_zmm23;		/* ZMM 23  */
	struct __darwin_zmm_reg		__fpu_zmm24;		/* ZMM 24  */
	struct __darwin_zmm_reg		__fpu_zmm25;		/* ZMM 25  */
	struct __darwin_zmm_reg		__fpu_zmm26;		/* ZMM 26  */
	struct __darwin_zmm_reg		__fpu_zmm27;		/* ZMM 27  */
	struct __darwin_zmm_reg		__fpu_zmm28;		/* ZMM 28  */
	struct __darwin_zmm_reg		__fpu_zmm29;		/* ZMM 29  */
	struct __darwin_zmm_reg		__fpu_zmm30;		/* ZMM 30  */
	struct __darwin_zmm_reg		__fpu_zmm31;		/* ZMM 31  */
};





struct __darwin_x86_exception_state64
{
    __uint16_t	__trapno;
    __uint16_t	__cpu;
    __uint32_t	__err;
    __uint64_t	__faultvaddr;
};




struct __darwin_x86_debug_state64
{
	__uint64_t	__dr0;
	__uint64_t	__dr1;
	__uint64_t	__dr2;
	__uint64_t	__dr3;
	__uint64_t	__dr4;
	__uint64_t	__dr5;
	__uint64_t	__dr6;
	__uint64_t	__dr7;
};




struct __darwin_x86_cpmu_state64
{
	__uint64_t __ctrs[16];
};


















struct __darwin_mcontext32
{
	struct __darwin_i386_exception_state	__es;
	struct __darwin_i386_thread_state	__ss;
	struct __darwin_i386_float_state	__fs;
};


struct __darwin_mcontext_avx32
{
	struct __darwin_i386_exception_state	__es;
	struct __darwin_i386_thread_state	__ss;
	struct __darwin_i386_avx_state		__fs;
};



struct __darwin_mcontext_avx512_32
{
	struct __darwin_i386_exception_state	__es;
	struct __darwin_i386_thread_state	__ss;
	struct __darwin_i386_avx512_state	__fs;
};







struct __darwin_mcontext64
{
	struct __darwin_x86_exception_state64	__es;
	struct __darwin_x86_thread_state64	__ss;
	struct __darwin_x86_float_state64	__fs;
};


struct __darwin_mcontext_avx64
{
	struct __darwin_x86_exception_state64	__es;
	struct __darwin_x86_thread_state64	__ss;
	struct __darwin_x86_avx_state64		__fs;
};



struct __darwin_mcontext_avx512_64
{
	struct __darwin_x86_exception_state64	__es;
	struct __darwin_x86_thread_state64	__ss;
	struct __darwin_x86_avx512_state64	__fs;
};








typedef struct __darwin_mcontext64	*mcontext_t;










/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef __darwin_pthread_attr_t pthread_attr_t;



/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

/* Structure used in sigaltstack call. */












struct __darwin_sigaltstack
{
	void            *ss_sp;	        /* signal stack base */
	__darwin_size_t ss_size;        /* signal stack length */
	int             ss_flags;       /* SA_DISABLE and/or SA_ONSTACK */
};
typedef struct __darwin_sigaltstack	stack_t; /* [???] signal stack */


/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */












/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



struct __darwin_ucontext
{
	int                     uc_onstack;
	__darwin_sigset_t       uc_sigmask;     /* signal mask used by this context */
	struct __darwin_sigaltstack     uc_stack;       /* stack used by this context */
	struct __darwin_ucontext        *uc_link;       /* pointer to resuming context */
	__darwin_size_t	        uc_mcsize;      /* size of the machine context passed in */
	struct __darwin_mcontext64        *uc_mcontext;   /* pointer to machine specific context */



};

/* user context */
typedef struct __darwin_ucontext	ucontext_t;     /* [???] user context */	





/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef __darwin_sigset_t		sigset_t;

/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef __darwin_size_t        size_t; 

/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef __darwin_uid_t        uid_t; 


union sigval {
	/* Members as suggested by Annex C of POSIX 1003.1b. */
	int	sival_int;
	void	*sival_ptr;
};





struct sigevent {
	int				sigev_notify;				/* Notification type */
	int				sigev_signo;				/* Signal number */
	union sigval	sigev_value;				/* Signal value */
	void			(*sigev_notify_function)(union sigval);	  /* Notification function */
	pthread_attr_t	*sigev_notify_attributes;	/* Notification attributes */
};


typedef struct __siginfo {
	int	si_signo;		/* signal number */
	int	si_errno;		/* errno association */
	int	si_code;		/* signal code */
	pid_t	si_pid;			/* sending process */
	uid_t	si_uid;			/* sender's ruid */
	int	si_status;		/* exit value */
	void	*si_addr;		/* faulting instruction */
	union sigval si_value;		/* signal value */
	long	si_band;		/* band event for SIGPOLL */
	unsigned long	__pad[7];	/* Reserved for Future Use */
} siginfo_t;


/* 
 * When the signal is SIGILL or SIGFPE, si_addr contains the address of 
 * the faulting instruction.
 * When the signal is SIGSEGV or SIGBUS, si_addr contains the address of 
 * the faulting memory reference. Although for x86 there are cases of SIGSEGV
 * for which si_addr cannot be determined and is NULL. 
 * If the signal is SIGCHLD, the si_pid field will contain the child process ID,
 *  si_status contains the exit value or signal and
 *  si_uid contains the real user ID of the process that sent the signal.
 */

/* Values for si_code */

/* Codes for SIGILL */


/* Codes for SIGFPE */


/* Codes for SIGSEGV */






/* Codes for SIGBUS */







/* Codes for SIGTRAP */



/* Codes for SIGCHLD */


/* Codes for SIGPOLL */







/* union for signal handlers */
union __sigaction_u {
	void    (*__sa_handler)(int);
	void    (*__sa_sigaction)(int, struct __siginfo *,
		       void *);
};

/* Signal vector template for Kernel user boundary */
struct	__sigaction {
	union __sigaction_u __sigaction_u;  /* signal handler */
	void    (*sa_tramp)(void *, int, int, siginfo_t *, void *);
	sigset_t sa_mask;		/* signal mask to apply */
	int	sa_flags;		/* see signal options below */
};

/*
 * Signal vector "template" used in sigaction call.
 */
struct	sigaction {
	union __sigaction_u __sigaction_u;  /* signal handler */
	sigset_t sa_mask;		/* signal mask to apply */
	int	sa_flags;		/* see signal options below */
};



/* if SA_SIGINFO is set, sa_sigaction is to be used instead of sa_handler. */




/* This will provide 64bit register set in a 32bit user address space */



/* the following are the only bits we support from user space, the 
 * rest are for kernel use only.
 */


/*
 * Flags for sigprocmask:
 */




/* POSIX 1003.1b required values. */







typedef	void (*sig_t)(int);	/* type of signal function */


/*
 * Structure used in sigaltstack call.
 */







/*
 * 4.3 compatibility:
 * Signal vector "template" used in sigvec call.
 */
struct	sigvec {
	void	(*sv_handler)(int);	/* signal handler */
	int	sv_mask;		/* signal mask to apply */
	int	sv_flags;		/* see signal options below */
};











/*
 * Structure used in sigstack call.
 */
struct	sigstack {
	char	*ss_sp;			/* signal stack pointer */
	int	ss_onstack;		/* current status */
};


/*
 * Macro for converting signal number to a mask suitable for
 * sigblock().
 */








/*
 * For historical reasons; programs expect signal's return value to be
 * defined by <sys/signal.h>.
 */

void	(*signal(int, void (*)(int)))(int);


/*
 * Copyright (c) 2000-2008 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/* Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved */
/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)resource.h	8.2 (Berkeley) 1/4/94
 */










/*===---- stdint.h - Standard header for sized integer types --------------===*\
 *
 * Copyright (c) 2009 Chris Lattner
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
\*===----------------------------------------------------------------------===*/




/* If we're hosted, fall back to the system's stdint.h, which might have
 * additional definitions.
 */


// C99 7.18.3 Limits of other integer types
//
//  Footnote 219, 220: C++ implementations should define these macros only when
//  __STDC_LIMIT_MACROS is defined before <stdint.h> is included.
//
//  Footnote 222: C++ implementations should define these macros only when
//  __STDC_CONSTANT_MACROS is defined before <stdint.h> is included.
//
// C++11 [cstdint.syn]p2:
//
//  The macros defined by <cstdint> are provided unconditionally. In particular,
//  the symbols __STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS (mentioned in
//  footnotes 219, 220, and 222 in the C standard) play no role in C++.
//
// C11 removed the problematic footnotes.
//
// Work around this inconsistency by always defining those macros in C++ mode,
// so that a C library implementation which follows the C99 standard can be
// used in C++.



/*
 * Copyright (c) 2000-2010 Apple Inc.
 * All rights reserved.
 */










/* from ISO/IEC 988:1999 spec */

/* 7.18.1.1 Exact-width integer types */






/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef unsigned char uint8_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef unsigned short uint16_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef unsigned int uint32_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef unsigned long long uint64_t;


/* 7.18.1.2 Minimum-width integer types */
typedef int8_t           int_least8_t;
typedef int16_t         int_least16_t;
typedef int32_t         int_least32_t;
typedef int64_t         int_least64_t;
typedef uint8_t         uint_least8_t;
typedef uint16_t       uint_least16_t;
typedef uint32_t       uint_least32_t;
typedef uint64_t       uint_least64_t;


/* 7.18.1.3 Fastest-width integer types */
typedef int8_t            int_fast8_t;
typedef int16_t          int_fast16_t;
typedef int32_t          int_fast32_t;
typedef int64_t          int_fast64_t;
typedef uint8_t          uint_fast8_t;
typedef uint16_t        uint_fast16_t;
typedef uint32_t        uint_fast32_t;
typedef uint64_t        uint_fast64_t;


/* 7.18.1.4 Integer types capable of holding object pointers */






/* 7.18.1.5 Greatest-width integer types */

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */




typedef long int intmax_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */




typedef long unsigned int uintmax_t;


/* 7.18.2 Limits of specified-width integer types:
 *   These #defines specify the minimum and maximum limits
 *   of each of the types declared above.
 *
 *   They must have "the same type as would an expression that is an
 *   object of the corresponding type converted according to the integer
 *   promotion".
 */


/* 7.18.2.1 Limits of exact-width integer types */







   /*
      Note:  the literal "most negative int" cannot be written in C --
      the rules in the standard (section 6.4.4.1 in C99) will give it
      an unsigned type, so INT32_MIN (and the most negative member of
      any larger signed type) must be written via a constant expression.
   */








/* 7.18.2.2 Limits of minimum-width integer types */















/* 7.18.2.3 Limits of fastest minimum-width integer types */















/* 7.18.2.4 Limits of integer types capable of holding object pointers */














/* 7.18.2.5 Limits of greatest-width integer types */





/* 7.18.3 "Other" */






















/* WCHAR_MIN should be 0 if wchar_t is an unsigned type and
   (-WCHAR_MAX-1) if wchar_t is a signed type.  Unfortunately,
   it turns out that -fshort-wchar changes the signedness of
   the type. */














/* 7.18.4 Macros for integer constants */

































/*
 * Copyright (c) 2007-2016 by Apple Inc.. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
 

    #define __attribute__((availability(_target, _availability)))
    



/* for use to document app extension usage */

  #if 1
    
    #define   
  




    #define 
    






/* for use marking APIs available info for Mac OSX */

  #if 1
    
    #define __OSX_AVAILABLE(_vers)               __attribute__((availability(macosx,introduced=_vers)))
    
  #endif







  #define __OSX_AVAILABLE(_vers)







/* for use marking APIs available info for iOS */

  #if 1
    
    #define __IOS_PROHIBITED                     __attribute__((availability(ios,unavailable)))
    
    #define __IOS_DEPRECATED(_start, _dep, _msg) __attribute__((availability(ios,introduced=_start))) 
  







  #define __IOS_PROHIBITED







  #define __IOS_DEPRECATED(_start, _dep, _msg)



/* for use marking APIs available info for tvOS */

  #if 1
    
    #define __TVOS_PROHIBITED                     __attribute__((availability(tvos,unavailable)))
    
    #define __TVOS_DEPRECATED(_start, _dep, _msg) __attribute__((availability(tvos,introduced=_start))) 
  







  #define __TVOS_PROHIBITED







  #define __TVOS_DEPRECATED(_start, _dep, _msg)



/* for use marking APIs available info for Watch OS */

  #if 1
    
    #define __WATCHOS_PROHIBITED                     __attribute__((availability(watchos,unavailable)))
    
    #define __WATCHOS_DEPRECATED(_start, _dep, _msg) __attribute__((availability(watchos,introduced=_start))) 
  







  #define __WATCHOS_PROHIBITED







  #define __WATCHOS_DEPRECATED(_start, _dep, _msg)



/* for use marking APIs unavailable for swift */

  #if 1
    
    #define __SWIFT_UNAVAILABLE_MSG(_msg)         
  







  #define __SWIFT_UNAVAILABLE_MSG(_msg)



/*
 Macros for defining which versions/platform a given symbol can be used.
 
 @see http://clang.llvm.org/docs/AttributeReference.html#availability
 
 * Note that these macros are only compatible with clang compilers that
 * support the following target selection options:
 *
 * -mmacosx-version-min
 * -miphoneos-version-min
 * -mwatchos-version-min
 * -mtvos-version-min
 * -mbridgeos-version-min
 */


 #if 1

    /*
     * API Introductions
     *
     * Use to specify the release that a particular API became available.
     *
     * Platform names:
     *   macos, ios, tvos, watchos
     *
     * Examples:
     *    __API_AVAILABLE(macos(10.10))
     *    __API_AVAILABLE(macos(10.9), ios(10.0))
     *    __API_AVAILABLE(macos(10.4), ios(8.0), watchos(2.0), tvos(10.0))
     */
    


    /*
     * API Deprecations
     *
     * Use to specify the release that a particular API became unavailable.
     *
     * Platform names:
     *   macos, ios, tvos, watchos
     *
     * Examples:
     *
     *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8))
     *    __API_DEPRECATED("No longer supported", macos(10.4, 10.8), ios(2.0, 3.0), watchos(2.0, 3.0), tvos(9.0, 10.0))
     *
     *    __API_DEPRECATED_WITH_REPLACEMENT("-setName:", tvos(10.0, 10.4), ios(9.0, 10.0))
     *    __API_DEPRECATED_WITH_REPLACEMENT("SomeClassName", macos(10.4, 10.6), watchos(2.0, 3.0))
     */
    
    #define  __API_DEPRECATED_REP_GET_MACRO(__VA_ARGS__,__API_DEPRECATED_REP6,__API_DEPRECATED_REP5,__API_DEPRECATED_REP4,__API_DEPRECATED_REP3,__API_DEPRECATED_REP2,__API_DEPRECATED_REP1)(__VA_ARGS__)

    /*
     * API Unavailability
     * Use to specify that an API is unavailable for a particular platform.
     *
     * Example:
     *    __API_UNAVAILABLE(macos)
     *    __API_UNAVAILABLE(watchos, tvos)
     */
    
 #else 

    /* 
     * Evaluate to nothing for compilers that don't support availability.
     */
    
    
    #define __API_DEPRECATED_MSG1(...)
    
    #define __API_UNAVAILABLE_GET_MACRO(...,__API_UNAVAILABLE4,__API_UNAVAILABLE3,__API_UNAVAILABLE2,__API_UNAVAILABLE1)(...)
 


    /* 
     * Evaluate to nothing for compilers that don't support clang language extensions.
     */
    
    
    #define __API_DEPRECATED_MSG1(...)
    
    #define __API_UNAVAILABLE_GET_MACRO(...,__API_UNAVAILABLE4,__API_UNAVAILABLE3,__API_UNAVAILABLE2,__API_UNAVAILABLE1)(...)






/* [XSI] The timeval structure shall be defined as described in
 * <sys/time.h>
 */

/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */






struct timeval
{
	__darwin_time_t	        tv_sec;	        /* seconds */
	__darwin_suseconds_t    tv_usec;        /* and microseconds */
};


/* The id_t type shall be defined as described in <sys/types.h> */



/*
 * Resource limit type (low 63 bits, excluding the sign bit)
 */
typedef __uint64_t	rlim_t;


/*****
 * PRIORITY
 */

/*
 * Possible values of the first parameter to getpriority()/setpriority(),
 * used to indicate the type of the second parameter.
 */









/*
 * Range limitations for the value of the third parameter to setpriority().
 */



/* 
 * use PRIO_DARWIN_BG to set the current thread into "background" state
 * which lowers CPU, disk IO, and networking priorites until thread terminates
 * or "background" state is revoked
 */


/*
 * use PRIO_DARWIN_NONUI to restrict a process's ability to make calls to
 * the GPU. (deprecated)
 */






/*****
 * RESOURCE USAGE
 */

/*
 * Possible values of the first parameter to getrusage(), used to indicate
 * the scope of the information to be returned.
 */



/*
 * A structure representing an accounting of resource utilization.  The
 * address of an instance of this structure is the second parameter to
 * getrusage().
 *
 * Note: All values other than ru_utime and ru_stime are implementaiton
 *       defined and subject to change in a future release.  Their use
 *       is discouraged for standards compliant programs.
 */
struct	rusage {
	struct timeval ru_utime;	/* user time used (PL) */
	struct timeval ru_stime;	/* system time used (PL) */



	/*
	 * Informational aliases for source compatibility with programs
	 * that need more information than that provided by standards,
	 * and which do not mind being OS-dependent.
	 */
	long	ru_maxrss;		/* max resident set size (PL) */

	long	ru_ixrss;		/* integral shared memory size (NU) */
	long	ru_idrss;		/* integral unshared data (NU)  */
	long	ru_isrss;		/* integral unshared stack (NU) */
	long	ru_minflt;		/* page reclaims (NU) */
	long	ru_majflt;		/* page faults (NU) */
	long	ru_nswap;		/* swaps (NU) */
	long	ru_inblock;		/* block input operations (atomic) */
	long	ru_oublock;		/* block output operations (atomic) */
	long	ru_msgsnd;		/* messages sent (atomic) */
	long	ru_msgrcv;		/* messages received (atomic) */
	long	ru_nsignals;		/* signals received (atomic) */
	long	ru_nvcsw;		/* voluntary context switches (atomic) */
	long	ru_nivcsw;		/* involuntary " */


};


/*
 * Flavors for proc_pid_rusage().
 */







typedef void *rusage_info_t;

struct rusage_info_v0 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
};

struct rusage_info_v1 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
};

struct rusage_info_v2 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
	uint64_t ri_diskio_bytesread;
	uint64_t ri_diskio_byteswritten;
};

struct rusage_info_v3 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
	uint64_t ri_diskio_bytesread;
	uint64_t ri_diskio_byteswritten;
	uint64_t ri_cpu_time_qos_default;
	uint64_t ri_cpu_time_qos_maintenance;
	uint64_t ri_cpu_time_qos_background;
	uint64_t ri_cpu_time_qos_utility;
	uint64_t ri_cpu_time_qos_legacy;
	uint64_t ri_cpu_time_qos_user_initiated;
	uint64_t ri_cpu_time_qos_user_interactive;
	uint64_t ri_billed_system_time;
	uint64_t ri_serviced_system_time;
};

struct rusage_info_v4 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
	uint64_t ri_diskio_bytesread;
	uint64_t ri_diskio_byteswritten;
	uint64_t ri_cpu_time_qos_default;
	uint64_t ri_cpu_time_qos_maintenance;
	uint64_t ri_cpu_time_qos_background;
	uint64_t ri_cpu_time_qos_utility;
	uint64_t ri_cpu_time_qos_legacy;
	uint64_t ri_cpu_time_qos_user_initiated;
	uint64_t ri_cpu_time_qos_user_interactive;
	uint64_t ri_billed_system_time;
	uint64_t ri_serviced_system_time;
	uint64_t ri_logical_writes;
	uint64_t ri_lifetime_max_phys_footprint;
	uint64_t ri_instructions;
	uint64_t ri_cycles;
	uint64_t ri_billed_energy;
	uint64_t ri_serviced_energy;
	// We're reserving 2 counters for future extension
	uint64_t ri_unused[2];
};

typedef struct rusage_info_v4 rusage_info_current;





/*****
 * RESOURCE LIMITS
 */

/*
 * Symbolic constants for resource limits; since all limits are representable
 * as a type rlim_t, we are permitted to define RLIM_SAVED_* in terms of
 * RLIM_INFINITY.
 */




/*
 * Possible values of the first parameter to getrlimit()/setrlimit(), to
 * indicate for which resource the operation is being performed.
 */


/*
 * A structure representing a resource limit.  The address of an instance
 * of this structure is the second parameter to getrlimit()/setrlimit().
 */
struct rlimit {
	rlim_t	rlim_cur;		/* current (soft) limit */
	rlim_t	rlim_max;		/* maximum value for rlim_cur */
};


/*
 * proc_rlimit_control()
 *
 * Resource limit flavors
 */




/*
 * Flags for wakeups monitor control.
 */





/*
 * Flags for CPU usage monitor control.
 */


struct proc_rlimit_control_wakeupmon {
	uint32_t wm_flags;
	int32_t wm_rate;
};



/* I/O type */


/* scope */




/* I/O Priority */







/* compatibility with older names */








int	getpriority(int, id_t);

int	getiopolicy_np(int, int) __OSX_AVAILABLE_STARTING(1050, 20000);

int	getrlimit(int, struct rlimit *) __asm("_" "x" );
int	getrusage(int, struct rusage *);
int	setpriority(int, id_t, int);

int	setiopolicy_np(int, int, int) __OSX_AVAILABLE_STARTING(1050, 20000);

int	setrlimit(int, __const struct rlimit *) __asm("_" "x" );




/*
 * Option bits for the third argument of wait4.  WNOHANG causes the
 * wait to not hang if there are no stopped or terminated processes, rather
 * returning an error indication in this case (pid==0).  WUNTRACED
 * indicates that the caller should receive status about untraced children
 * which stop due to signals.  If children are stopped and a wait without
 * this option is done, it is as though they were still running... nothing
 * about them is returned.
 */



/*
 * Macros to test the exit status returned by wait
 * and extract the relevant values.
 */







/* These macros are permited, as they are in the implementation namespace */



/*
 * [XSI] The <sys/wait.h> header shall define the following macros for
 * analysis of process status values
 */





/* 0x13 == SIGCONT */













/*
 * [XSI] The following symbolic constants shall be defined as possible
 * values for the fourth argument to waitid().
 */
/* WNOHANG already defined for wait4() */
/* WUNTRACED defined for wait4() but not for waitid() */


/* waitid() parameter */







/* POSIX extensions and 4.2/4.3 compatability: */

/*
 * Tokens for special values of the "pid" parameter to wait4.
 */




/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright 1995 NeXT Computer, Inc. All rights reserved.
 */





/*
 * Copyright (c) 2000-2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright 1995 NeXT Computer, Inc. All rights reserved.
 */
/*
 * Copyright (c) 1987, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)endian.h	8.1 (Berkeley) 6/11/93
 */





/*
 * Define _NOQUAD if the compiler does NOT support 64-bit integers.
 */
/* #define _NOQUAD */

/*
 * Define the order of 32-bit words in 64-bit words.
 */



/*
 * Definitions for byte order, according to byte significance from low
 * address to high.
 */















/*
 * Copyright (c) 2004, 2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

/*
 * Copyright (c) 1995 NeXT Computer, Inc. All rights reserved.
 * Copyright (c) 2000-2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1987, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */






/*
 * Macros for network/external number representation conversion.
 */




/*
 * Copyright (c) 2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */




/*
 * This header is normally included from <libkern/OSByteOrder.h>.  However,
 * <sys/_endian.h> also includes this in the case of little-endian
 * architectures, so that we can map OSByteOrder routines to the hton* and ntoh*
 * macros.  This results in the asymmetry below; we only include
 * <libkern/arch/_OSByteOrder.h> for little-endian architectures.
 */



/* Macros for swapping constant values in the preprocessing stage. */
















/*
 * Copyright (c) 2006-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */






/* Generic byte swapping functions. */

static __inline
__uint16_t
_OSSwapInt16(
    __uint16_t        _data
)
{
    return ((__uint16_t)((_data << 8) | (_data >> 8)));
}

static __inline
__uint32_t
_OSSwapInt32(
    __uint32_t        _data
)
{

    return __builtin_bswap32(_data);




}


static __inline
__uint64_t
_OSSwapInt64(
    __uint64_t        _data
)
{
    return __builtin_bswap64(_data);
}









































/*
 * Deprecated:
 * Structure of the information in the status word returned by wait4.
 * If w_stopval==_WSTOPPED, then the second structure describes
 * the information returned, else the first.
 */
union wait {
	int	w_status;		/* used in syscall */
	/*
	 * Terminated process status.
	 */
	struct {

		unsigned int	w_Termsig:7,	/* termination signal */
				w_Coredump:1,	/* core dump indicator */
				w_Retcode:8,	/* exit code if w_termsig==0 */
				w_Filler:16;	/* upper bits filler */







	} w_T;
	/*
	 * Stopped process status.  Returned
	 * only for traced children unless requested
	 * with the WUNTRACED option bit.
	 */
	struct {

		unsigned int	w_Stopval:8,	/* == W_STOPPED if stopped */
				w_Stopsig:8,	/* signal that stopped us */
				w_Filler:16;	/* upper bits filler */






	} w_S;
};

















pid_t	wait(int *) __asm("_" "x" );
pid_t	waitpid(pid_t, int *, int) __asm("_" "x" );

int	waitid(idtype_t, id_t, siginfo_t *, int) __asm("_" "x" );


pid_t	wait3(int *, int, struct rusage *);
pid_t	wait4(pid_t, int *, int, struct rusage *);

           


/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */









void	*alloca(size_t);		/* built-in for gcc */



/* built-in for gcc 3 */










/* DO NOT REMOVE THIS COMMENT: fixincludes needs to see:
 * _GCC_SIZE_T */




/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */




typedef __darwin_ct_rune_t ct_rune_t;

/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef __darwin_rune_t rune_t; 




/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

/* wchar_t is a built-in type in C++ */




typedef __darwin_wchar_t wchar_t;


typedef struct {
	int quot;		/* quotient */
	int rem;		/* remainder */
} div_t;

typedef struct {
	long quot;		/* quotient */
	long rem;		/* remainder */
} ldiv_t;


typedef struct {
	long long quot;
	long long rem;
} lldiv_t;



/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */


















extern int __mb_cur_max;


















void	 abort(void) __attribute__((noreturn));
int	 abs(int) __attribute__((__const));
int	 atexit(void (* _Nonnull)(void));
double	 atof(__const char *);
int	 atoi(__const char *);
long	 atol(__const char *);

long long
	 atoll(__const char *);

void	*bsearch(__const void *__key, __const void *__base, size_t __nel,
	    size_t __width, int (* _Nonnull __compar)(__const void *, __const void *));
void	*calloc(size_t __count, size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1,2)));
div_t	 div(int, int) __attribute__((__const));
void	 exit(int) __attribute__((noreturn));
void	 free(void *);
char	*getenv(__const char *);
long	 labs(long) __attribute__((__const));
ldiv_t	 ldiv(long, long) __attribute__((__const));

long long
	 llabs(long long);
lldiv_t	 lldiv(long long, long long);

void	*malloc(size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(1)));
int	 mblen(__const char *__s, size_t __n);
size_t	 mbstowcs(wchar_t * restrict , __const char * restrict, size_t);
int	 mbtowc(wchar_t * restrict, __const char * restrict, size_t);
int 	 posix_memalign(void **__memptr, size_t __alignment, size_t __size) __OSX_AVAILABLE_STARTING(1060, 30000);
void	 qsort(void *__base, size_t __nel, size_t __width,
	    int (* _Nonnull __compar)(__const void *, __const void *));
int	 rand(void) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
void	*realloc(void *__ptr, size_t __size) __attribute__((__warn_unused_result__)) __attribute__((alloc_size(2)));
void	 srand(unsigned) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
double	 strtod(__const char *, char **) __asm("_" "x" );
float	 strtof(__const char *, char **) __asm("_" "x" );
long	 strtol(__const char *__str, char **__endptr, int __base);
long double
	 strtold(__const char *, char **);

long long 
	 strtoll(__const char *__str, char **__endptr, int __base);

unsigned long
	 strtoul(__const char *__str, char **__endptr, int __base);

unsigned long long
	 strtoull(__const char *__str, char **__endptr, int __base);








__attribute__((__availability__(swift, unavailable, message="Use posix_spawn APIs or NSTask instead.")))
 __IOS_PROHIBITED
__WATCHOS_PROHIBITED __TVOS_PROHIBITED
int	 system(__const char *) __asm("_" "x" );



size_t	 wcstombs(char * restrict, __const wchar_t * restrict, size_t);
int	 wctomb(char *, wchar_t);


void	_Exit(int) __attribute__((noreturn));
long	 a64l(__const char *);
double	 drand48(void);
char	*ecvt(double, int, int *restrict, int *restrict); /* LEGACY */
double	 erand48(unsigned short[3]);
char	*fcvt(double, int, int *restrict, int *restrict); /* LEGACY */
char	*gcvt(double, int, char *); /* LEGACY */
int	 getsubopt(char **, char * __const *, char **);
int	 grantpt(int);

char	*initstate(unsigned, char *, size_t); /* no  __DARWIN_ALIAS needed */



long	 jrand48(unsigned short[3]) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
char	*l64a(long);
void	 lcong48(unsigned short[7]);
long	 lrand48(void) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
char	*mktemp(char *);
int	 mkstemp(char *);
long	 mrand48(void) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
long	 nrand48(unsigned short[3]) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
int	 posix_openpt(int);
char	*ptsname(int);


int ptsname_r(int fildes, char *buffer, size_t buflen) ;


int	 putenv(char *) __asm("_" "x" );
long	 random(void) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));
int	 rand_r(unsigned *) __attribute__((__availability__(swift, unavailable, message="Use arc4random instead.")));

char	*realpath(__const char * restrict, char * restrict) __asm("_" "x" "$DARWIN_EXTSN");



unsigned short
	*seed48(unsigned short[3]);
int	 setenv(__const char * __name, __const char * __value, int __overwrite) __asm("_" "x" );

void	 setkey(__const char *) __asm("_" "x" );



char	*setstate(__const char *);
void	 srand48(long);

void	 srandom(unsigned);



int	 unlockpt(int);

int	 unsetenv(__const char *) __asm("_" "x" );









/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef __darwin_dev_t        dev_t;	/* device number */ 

/*
 * Copyright (c) 2003-2012 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */



typedef	__darwin_mode_t		mode_t;



uint32_t arc4random(void);
void	 arc4random_addrandom(unsigned char * /*dat*/, int /*datlen*/)
    __OSX_AVAILABLE(10.0)
    __IOS_DEPRECATED(2.0, 10.0, "use arc4random_stir")
    __TVOS_DEPRECATED(2.0, 10.0, "use arc4random_stir")
    __WATCHOS_DEPRECATED(1.0, 3.0, "use arc4random_stir");
void	 arc4random_buf(void * __buf, size_t __nbytes) __OSX_AVAILABLE_STARTING(1070, 40300);
void	 arc4random_stir(void);
uint32_t
	 arc4random_uniform(uint32_t __upper_bound) __OSX_AVAILABLE_STARTING(1070, 40300);

int	 atexit_b(void (^ _Nonnull)(void)) __OSX_AVAILABLE_STARTING(1060, 30200);
void	*bsearch_b(__const void *__key, __const void *__base, size_t __nel,
	    size_t __width, int (^ _Nonnull __compar)(__const void *, __const void *)) __OSX_AVAILABLE_STARTING(1060, 30200);


	 /* getcap(3) functions */
char	*cgetcap(char *, __const char *, int);
int	 cgetclose(void);
int	 cgetent(char **, char **, __const char *);
int	 cgetfirst(char **, char **);
int	 cgetmatch(__const char *, __const char *);
int	 cgetnext(char **, char **);
int	 cgetnum(char *, __const char *, long *);
int	 cgetset(__const char *);
int	 cgetstr(char *, __const char *, char **);
int	 cgetustr(char *, __const char *, char **);

int	 daemon(int, int) __asm("_" "x" "$1050") __OSX_AVAILABLE_BUT_DEPRECATED_MSG(1000, 1050, 20000, 20000, "Use posix_spawn APIs instead.") __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
char	*devname(dev_t, mode_t);
char	*devname_r(dev_t, mode_t, char *buf, int len);
char	*getbsize(int *, long *);
int	 getloadavg(double [], int);
__const char
	*getprogname(void);

int	 heapsort(void *__base, size_t __nel, size_t __width,
	    int (* _Nonnull __compar)(__const void *, __const void *));

int	 heapsort_b(void *__base, size_t __nel, size_t __width,
	    int (^ _Nonnull __compar)(__const void *, __const void *)) __OSX_AVAILABLE_STARTING(1060, 30200);

int	 mergesort(void *__base, size_t __nel, size_t __width,
	    int (* _Nonnull __compar)(__const void *, __const void *));

int	 mergesort_b(void *__base, size_t __nel, size_t __width,
	    int (^ _Nonnull __compar)(__const void *, __const void *)) __OSX_AVAILABLE_STARTING(1060, 30200);

void	 psort(void *__base, size_t __nel, size_t __width,
	    int (* _Nonnull __compar)(__const void *, __const void *)) __OSX_AVAILABLE_STARTING(1060, 30200);

void	 psort_b(void *__base, size_t __nel, size_t __width,
	    int (^ _Nonnull __compar)(__const void *, __const void *)) __OSX_AVAILABLE_STARTING(1060, 30200);

void	 psort_r(void *__base, size_t __nel, size_t __width, void *,
	    int (* _Nonnull __compar)(void *, __const void *, __const void *))  __OSX_AVAILABLE_STARTING(1060, 30200);

void	 qsort_b(void *__base, size_t __nel, size_t __width,
	    int (^ _Nonnull __compar)(__const void *, __const void *)) __OSX_AVAILABLE_STARTING(1060, 30200);

void	 qsort_r(void *__base, size_t __nel, size_t __width, void *,
	    int (* _Nonnull __compar)(void *, __const void *, __const void *));
int	 radixsort(__const unsigned char **__base, int __nel, __const unsigned char *__table,
	    unsigned __endbyte);
void	 setprogname(__const char *);
int	 sradixsort(__const unsigned char **__base, int __nel, __const unsigned char *__table,
	    unsigned __endbyte);
void	 sranddev(void);
void	 srandomdev(void);
void	*reallocf(void *__ptr, size_t __size) __attribute__((alloc_size(2)));

long long
	 strtoq(__const char *__str, char **__endptr, int __base);
unsigned long long
	 strtouq(__const char *__str, char **__endptr, int __base);

extern char *suboptarg;		/* getsubopt(3) external variable */
void	*valloc(size_t) __attribute__((alloc_size(1)));


/* Poison the following routines if -fshort-wchar is set */



           














































// Prototypes
typedef struct {
    int8 bool_count, count;
} twoint;

twoint *new_twoint(void);

float8 *min(float8 *x, float8 *y);

float8 *max(float8 *x, float8 *y);

float8 *neg_dm(float8 *x);

twoint *twoint_from_string(char *str);

char *twoint_to_string(twoint *t);

twoint *state_percentage(twoint *state, bool next);

float8 *final_percentage(twoint *last_state);


// General functions, independent from fuzzy type

// Zadeh operators

float8 *min(float8 *x, float8 *y) {
    if ((x == ((void *)0)) || (y == ((void *)0))) {
        return ((void *)0);
    }
    if (*x < *y) {
        return x;
    }
    return y;
}

PG_FUNCTION_INFO_V1(pg_ ## min);Datum pg_ ## min(PG_FUNCTION_ARGS) {  float8 * arg0 = ( float8 *) PG_GETARG_ ##  POINTER(0);  float8 * arg1 = ( float8 *) PG_GETARG_ ##  POINTER(1);  float8 * result = min(arg0, arg1); PG_RETURN_ ##  POINTER(result);};

float8 *max(float8 *x, float8 *y) {
    if ((x == ((void *)0)) || (y == ((void *)0))) {
        return ((void *)0);
    }
    if (*x < *y)
        return y;
    else
        return x;
}

float8 *neg_dm(float8 *x) {
    if (x == ((void *)0)) {
        return ((void *)0);
    } else {
        *x = 1 - *x;
        return (x);
    };
}

// Percentage Aggregate - Extended type that stores summed values

twoint *new_twoint(void) {
    return (twoint *) palloc(sizeof(twoint));
}

twoint *twoint_from_string(char *str) {
    twoint *result = new_twoint();


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
    sscanf(str, "%d,%d", &(result->bool_count), &(result->count));

#pragma GCC diagnostic pop

    return result;
}

char *twoint_to_string(twoint *t) {
    char *result = (char *) palloc(sizeof(char));
    strcpy(result, "");

    sprintf(result, "%d,%d", t->bool_count, t->count);
    return result;
}

twoint *state_percentage(twoint *state, bool next) {
    twoint *result = new_twoint();

    result->bool_count = state->bool_count;
    result->count = state->count;

    result->count++;
    if (next) {
        result->bool_count++;
    }

    return result;
}

float8 *final_percentage(twoint *last_state) {
    float8 *result = ((void *)0);

    if (last_state == ((void *)0)) {
        return ((void *)0);
    }

    result = (float8 *) palloc(8);
    *result = (float8)(last_state->bool_count / last_state->count);

    return result;
}


