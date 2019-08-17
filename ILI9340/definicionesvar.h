/*
 * definicionesvar.h
 * definiciones para nombres mas cortos sin signo
 * Febrero 19, 2015
 * Eduardo Alvarez Lopez
 */

//-----------------------------------------------------------------------------------//
//------------------------ Definiciones variables sin signo  ------------------------//
//-----------------------------------------------------------------------------------//

#ifndef DEFINICIONESVAR_H_		// comprueba sino se ha definido ya esta libreria para evitar errores
	#define DEFINICIONESVAR_H_	//de compilacion y sino se ha definido lo define


	#ifndef UNSIGNED_VAR
		#define UNSIGNED_VAR
		typedef enum{FALSE,TRUE}bool;
		typedef unsigned char u_char;
		typedef unsigned int u_int;
		typedef unsigned long u_long;
		typedef unsigned long long u_longlong;
	#endif

#endif
 /* DEFINICIONESVAR_H_ */
