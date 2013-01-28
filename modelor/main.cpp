/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
************************** S_MAD ****************************
*************************************************************
**                                                         **
******** s_mad.cpp **** auteur : Vincent Tourraine **********
**                                                         **
**                                                         **
*************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>

// Inclusions relatives � OpenGL
#include <GL/glut.h>
#include <GL/gl.h>

#include "def.hpp"
#include "fonctions.hpp"
#include "editor.hpp"

void New(void);
void Mix(void);
void Export(void);
void Import(void);
void Mute(void);
void _3D(int argc, char**argv);

int main(int argc, char**argv)
{
	printf("\n\nS-W 3 : PHOENIXIA : S_MAD\n\n\n");
	printf("1 - S_Mad 3D\n");
	printf("2 - Nouveau model\n");
	printf("3 - Mixer\n");
	printf("4 - Exporter un model\n");
	printf("5 - Importer un model\n");
	printf("6 - Muter un model\n");

	char input=getchar();

	switch(input)
	{
	case '1' :
		_3D(argc, argv);
		break;
	case '2' :
		New();
		break;
	case '3' :
		Mix();
		break;
	case '4' :
		Export();
		break;
	case '5' :
		Import();
		break;
	case '6' :
		Mute();
		break;
	default :
		break;
	}

	printf("EXIT S_MAD PROGRAM\n");
	return 0;

}

