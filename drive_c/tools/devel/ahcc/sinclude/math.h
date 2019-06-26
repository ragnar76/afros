/*
 *	MATH.H		Math functionality for AHCC & PURE_C
 */

#if ! defined MATH_H
#define MATH_H

#ifdef __NO_FLOAT__
#error floating point not implemented by this compiler
#else


#if __ABC__ || __AHCC__

	#define FMATH_H
	#define operator __OP__
	#define cast __UC__

	typedef double FpF(double);
	typedef double FpFF(double,double);

	FpF ceil, floor;

	#ifndef __68881__

		FpF	 sin,cos,tan,asin,acos,atan,log,log10,log2,sqrt,
		     exp,sinh,asinh,cosh,acosh,tanh,atanh,fabs,
		     getexp,getman;

		/*	Of course the following is NON C
		 *   The ANSI standard tells us that standard headers are completely
		 *		implementor defined as long as their function complies the standard.
		 *			They need not even be files at all.
		 *		#include <name>		however is the standerd way to invoke them.
		 *	Every implementor has its own way to deal with extracode software.
		 *	I too do it my way.
		 *		Basicly I borrowed this from Algol68, long before I ever heard of C,
		 *			or even C++.
		 */

		/* ahcc puts every next declaration in front of the table!!
			So it is recommended to put these declarations
				in ascending order of frequency.
			Put the most frequent at the end.
		*/
		#define __IEEE__
		double	operator *  (double,double) XXmul,
				operator /  (double,double) XXdiv,
			/*	operator %  (double,double) XXrem,	*/
				operator +  (double,double) XXadd,
				operator -  (double,double) XXsub,
				operator -  (double)		Xneg;

		bool	operator !  (double) 		Xnot,
				operator <  (double,double) XXcmp,
				operator >  (double,double) XXcmp,
				operator <= (double,double) XXcmp,
				operator >= (double,double) XXcmp,
				operator == (double,double) XXcmp,
				operator != (double,double) XXcmp;

		unsigned
		long	cast(double) 		Xlcnv;
		int		cast(double)		Xlcnv;
		unsigned
		int		cast(double)		Xlcnv;
		char	cast(double)		Xlcnv;
		unsigned
		char 	cast(double)		Xlcnv;
		float	cast(double)		Xfcnv;
		long	cast(double)		Xlcnv;
		double	cast(float)			fXcnv,
				cast(unsigned long)	ulXcnv,
				cast(unsigned int)	uiXcnv,
				cast(unsigned char) uiXcnv,
				cast(char)			iXcnv,
				cast(int)			iXcnv,
				cast(long)			lXcnv;

		#ifdef __IEEE__			/* if allready determined */
		/* in fact this is determined by the called software itself,
			so here are the names */
			float	operator *  (float,float) FFmul,
					operator /  (float,float) FFdiv,
				/*	operator %  (float,float) FFrem,	*/
					operator +  (float,float) FFadd,
					operator -  (float,float) FFsub,
					operator -	(float)       Fneg;

			bool 	operator !  (float)       Fnot,
					operator <  (float,float) FFcmp,
					operator >  (float,float) FFcmp,
					operator <= (float,float) FFcmp,
					operator >= (float,float) FFcmp,
					operator == (float,float) FFcmp,
					operator != (float,float) FFcmp;

			unsigned
			long	cast(float)			_Flcnv;
			int		cast(float)			_Flcnv;
			unsigned
			int		cast(float)			_Flcnv;
			char	cast(float)			_Flcnv;
			unsigned
			char	cast(float)			_Flcnv;
			long	cast(float)			_Flcnv;
			float	cast(unsigned long)	_ulFcnv,
					cast(unsigned)		_uiFcnv,
					cast(char)			_iFcnv,		/* char on stack becomes int */
					cast(int)			_iFcnv,
					cast(long)			_lFcnv;

		#else
			/* here are the old SOZOBON names.
			    I know some names dont really exist, but this how
					it should be done and the missing ones can
						be added anytime. */
			float	operator *  (float,float) fpmul,
					operator /  (float,float) fpdiv,
				/*	operator %  (float,float) fprem,	*/
					operator +  (float,float) fpadd,
					operator -  (float,float) fpsub,
					operator -	(float)       fpneg;

			bool 	operator !  (float)       fpnot,
					operator <  (float,float) fpcmp,
					operator >  (float,float) fpcmp,
					operator <= (float,float) fpcmp,
					operator >= (float,float) fpcmp,
					operator == (float,float) fpcmp,
					operator != (float,float) fpcmp;

			unsigned
			long	cast(float)			_fpftol;
			int		cast(float)			_fpftol;
			unsigned
			int		cast(float)			_fpftol;
			char	cast(float)			_fpftol;
			unsigned
			char	cast(float)			_fpftol;
			long	cast(float)			_fpftol;
			float	cast(unsigned long)	_fpultof,
					cast(unsigned)		_fpuitof,
					cast(char)			_fpitof,		/* char on stack becomes int */
					cast(int)			_fpitof,
					cast(long)			_fpltof;
		#endif

	#else		/* if FPU, built in monadic operators (compiler opt -8) */

		#define fabs(f) __FABS__(f)
		#define trunc(f) __FINTRZ__(f)
		#define fint(f) __FINT__(f)
		#define	sqrt(f) __FSQRT__(f)
		#define fintrz(f) __FINTRZ__(f)

		#if ! __COLDFIRE__
		#define	sin(f) __FSIN__(f)
		#define	cos(f) __FCOS__(f)
		#define	tan(f) __FTAN__(f)
		#define	asin(f) __FASIN__(f)
		#define	acos(f) __FACOS__(f)
		#define	atan(f) __FATAN__(f)
		#define fetoxm1(f) __FETOXM1__(f)
		#define	log(f) __FLOGN__(f)
		#define flognp1(f) __FLOGNP1__(f)
		#define log2(f) __FLOG2__(f)
		#define	log10(f) __FLOG10__(f)
		#define fneg(f) __FNEG__(f)
		#define	exp(f) __FETOX__(f)
		#define	sinh(f) __FSINH__(f)
		#define	cosh(f) __FCOSH__(f)
		#define	tanh(f) __FTANH__(f)
		#define atanh(f) __FATANH__(f)
		#define fgetexp(f) __FGETEXP__(f)
		#define fgetman(f) __FGETMAN__(f)
		#define pow10(f) __FTENTOX__(f)
		#define pow2(f) __FTWOTOX__(f)
		#else
		double ldexp(double b, int n);
		double frexp(double b, int *ip);
		double modf(double b, double *op);
		double fmod( double x, double y );
		double  cos( double x );
		double  sin( double x );
		double  tan( double x );
		double acos( double x );
		double asin( double x );
		double atan( double x );
		double cosh( double x );
		double sinh( double x );
		double tanh( double x );
		double atanh( double x );
		double log10( double x );
		double log2( double x );
		double log ( double x );
		double exp ( double x );
		double pow10( int i );
		double pow2 ( double x );
		#endif
	#endif

	FpFF atan2,pow,fmod;
	FpF asinh, acosh;
	double atof(const char *);
	double ldexp(double b, int n);
	double frexp(double b, int *ip);
	double modf(double b, double *op);

	/* Some useful constants, generally to 21 digits */

	#define M_E				2.71828182845904523536
	#define M_LOG2E			1.44269504088896340736
	#define M_LOG10E		0.434294481903251827651
	#define M_LN2			0.693147180559945309417
	#define M_LN10			2.30258509299404568402
	#define M_PI			3.14159265358979323846
	#define M_PI_2			1.57079632679489661923
	#define M_PI_4			0.785398163397448309116
	#define M_1_PI			0.318309886183790671538
	#define M_2_PI			0.636619772367581343076
	#define M_1_SQRTPI		0.564189583547756286948
	#define M_2_SQRTPI		1.12837916709551257390
	#define M_SQRT2			1.41421356237309504880
	#define M_SQRT_2		0.707106781186547524401

#if __COLDFIRE__
	#define MAXREAL	(double)1.79769313486232E+308		/* 64 bits */
#else
	#define MAXREAL	(double)1.189731495357231765E+4932	/* 80 bits */
#endif
	#define HUGE_VAL	MAXREAL

	#define _ABS(x)	((x) < 0 ? -(x) : (x))

	#undef operator
	#undef cast

#else		/* not AHCC */
	/*      MATH.H

	        Mathematical Definition Includes

	        Copyright (c) Borland International 1990
	        All Rights Reserved.
	*/


	#define __MATH

#if __COLDFIRE__
	#define HUGE_VAL		1.79769313486232E+308		/* 64 bits */
#else
	#define HUGE_VAL        1.189731495357231765E+4932	/* 80 bits */
#endif

	#define M_E             2.71828182845904523536
	#define M_LOG2E         1.44269504088896340736
	#define M_LOG10E        0.434294481903251827651
	#define M_LN2           0.693147180559945309417
	#define M_LN10          2.30258509299404568402
	#define M_PI            3.14159265358979323846
	#define M_PI_2          1.57079632679489661923
	#define M_PI_4          0.785398163397448309116
	#define M_1_PI          0.318309886183790671538
	#define M_2_PI          0.636619772367581343076
	#define M_1_SQRTPI      0.564189583547756286948
	#define M_2_SQRTPI      1.12837916709551257390
	#define M_SQRT2         1.41421356237309504880
	#define M_SQRT_2        0.707106781186547524401

	double  fabs( double x );
	double  ceil( double x );
	double  floor( double x );
/*	double  round( double x ); */
	double  trunc( double x );

	double  fmod( double x, double y );
	double  exp( double x );
	double  log( double x );
	double  log2( double x );
	double  log10( double x );

	double  frexp( double x, int *nptr );
	double  ldexp( double x, int n );
	double  modf( double x, double *nptr );

	double  pow( double x, double y );
	double  pow10( int i );
	double  pow2( double i );
	double  sqrt( double x );

	double  cos( double x );
	double  sin( double x );
	double  tan( double x );
	void    sincos( double x, double *sin, double *cos );

	double  acos( double x );
	double  asin( double x );
	double  atan( double x );
	double  atan2( double x, double y );
	double  cosh( double x );
	double  sinh( double x );
	double  tanh( double x );

	double  acosh( double x );
	double  asinh( double x );
	double  atanh( double x );
	double  pow( double x, double y );

	short   ftoa( double *x, char *resStr, short ndig, short format,
	              short *decPnt, short *sign );

	double  atof( const char *digStr );


	typedef enum
	{
	         DOMAIN = 1,    /* argument domain error -- log (-1)      */
	         SING,          /* argument singularity  -- pow (0,-2))   */
	         OVERFLOW,      /* overflow range error  -- exp (1000)    */
	         UNDERFLOW      /* underflow range error -- exp (-1000)   */
	} mexcep;

	struct exception
	{
	    mexcep      type;
	    char        *name;
	    double      arg1;
	    double      arg2;
	    double      retval;
	};


	void    setmatherr( short (*errorfunc)( struct exception *e ) );
	short   fpumode( short dis );
	void    xdcnv( double *val, void *rep8bytes );
	void    dxcnv( void *rep8bytes, double *val );

	#if defined( __68881__ )
	double  fint( double x );
	double  fintrz( double x );
	double  fgetexp( double x );
	double  fgetman( double x );
	double  frem( double x, double y );
	double  fsgldiv( double x, double y );
	double  fsglmul( double x, double y );
	double  fetoxm1( double x );
	double  flognp1( double x );
	double  pow2( double x );
	#endif

	#if defined( __68881__ ) && !defined( __NFPUIN__ )
	                                              /* MC68881 extensions */
	/* Arithmetische Befehle: */
	#define trunc( x )      __FINTRZ__( x )
	#define fabs( x )       __FABS__( x )
	#define fgetexp( x )    __FGETEXP__( x )
	#define fgetman( x )    __FGETMAN__( x )
	#define fint( x )       __FINT__( x )
	#define fintrz( x )     __FINTRZ__( x )

	#define fmod( x, y )    __FMOD__( y, x )
	#define frem( x, y )    __FREM__( y, x )
	#define ldexp( x, y )   __FSCALE__( y, x )
	#define fsgldiv( x, y ) __FSGLDIV__( y, x )
	#define fsglmul( x, y ) __FSGLMUL__( y, x )

	/* Potenzen und Logarithmen: */
	#define exp( x )        __FETOX__( x )
	#define fetoxm1( x )    __FETOXM1__( x )
	#define log( x )        __FLOGN__( x )
	#define flognp1( x )    __FLOGNP1__( x )
	#define log10( x )      __FLOG10__( x )
	#define log2( x )       __FLOG2__( x )
	#define sqrt( x )       __FSQRT__( x )
	#define pow10( x )      __FTENTOX__( x )
	#define pow2( x )       __FTWOTOX__( x )

	/* Trigonometrie: */
	#define acos( x )       __FACOS__( x )
	#define asin( x )       __FASIN__( x )
	#define atan( x )       __FATAN__( x )
	#define cos( x )        __FCOS__( x )
	#define sin( x )        __FSIN__( x )
	#define tan( x )        __FTAN__( x )

	/* Hyperbelfunktionen: */
	#define atanh( x )      __FATANH__( x )
	#define cosh( x )       __FCOSH__( x )
	#define sinh( x )       __FSINH__( x )
	#define tanh( x )       __FTANH__( x )

	/* Conversionsfunktionen nur fr TC881LIB.LIB */
	double x80x96cnv( void *rep10bytes );
	void   x96x80cnv( double rep12bytes, void *rep10bytes );

	#endif
#endif	/* __ABC__ || __AHCC__ */

#endif	/* __NO_FLOAT__ */

#endif /* MATH_H */
