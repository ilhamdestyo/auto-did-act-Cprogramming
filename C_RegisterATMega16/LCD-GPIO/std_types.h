/***********************************************************************/
/***********    File Name  : std_types.h			     	************/
/***********	Version	   : V0.1							************/
/***********    Date       : 16-05-2022             		************/
/***********    Description: standard types header file    	************/
/***********************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/***********************************************************************/
/***********				Types Deceleration				  **********/
/***********************************************************************/

typedef unsigned char      		uint8 ;		//digital value /*					  0 .. 255			        */
typedef unsigned short int 		uint16;		//digital value /*					  0 .. 65,535			    */
typedef unsigned long  int 		uint32;		//digital value /*					  0 .. 4,294,967,295	    */
typedef unsigned long long int	uint64;		//digital value /*       			  0 .. 18446744073709551615 */
 	
typedef signed char      	   	sint8 ;		//digital value /*			       -128 .. 172				    */
typedef signed short int 	   	sint16;		//digital value /*		        -32,768 .. 32,767			    */
typedef signed long int  	   	sint32;		//digital value /*	     -2,147,483,648 .. 2,147,483,647	    */
typedef signed long long int	sint64;		//digital value /* -9223372036854775808 .. 9223372036854775807  */

typedef float					float32;
typedef double					float64;

/* Boolean data type */
typedef unsigned char			bollean;

/***********************************************************************/
/***********				Constants Definitions			  **********/
/***********************************************************************/

/* Boolean values */
#ifndef TRUE
#define TRUE					(1u)
#endif
#ifndef FALSE
#define FALSE					(0u)
#endif

#define NULL_PTR				((void*)0x00)

#define LOGIC_HIGH				(1u)
#define LOGIC_LOW				(0u)

#endif
