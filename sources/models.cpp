/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** models.cpp **** auteur : Vincent Tourraine *********
**                                                         **
** Fonctions d'initialisation de chargement des models.    **
**                                                         **
*************************************************************/

// Fonction d'initialisation des models ( declasse )
void Init_Models(void)
{
	// Allocution des id pour chaque model
	id_shokerPIQ=glGenLists(1);
	id_shokerCOR=glGenLists(1);

	// Model des piques d'un Shoker
	glNewList(id_shokerPIQ,GL_COMPILE);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5,0); glVertex3f(0,3,0);
	glTexCoord2f(0.4,0.43); glVertex3f(0.25,0.75,0.25);
	glTexCoord2f(0.6,0.43); glVertex3f(-0.25,0.75,0.25);
	glTexCoord2f(0.4,0.43); glVertex3f(-0.25,0.75,-0.25);
	glTexCoord2f(0.6,0.43); glVertex3f(0.25,0.75,-0.25);
	glTexCoord2f(0.4,0.43); glVertex3f(0.25,0.75,0.25);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5,1); glVertex3f(0,-3,0);
	glTexCoord2f(0.4,0.55); glVertex3f(0.25,-0.75,0.25);
	glTexCoord2f(0.6,0.55); glVertex3f(-0.25,-0.75,0.25);
	glTexCoord2f(0.4,0.55); glVertex3f(-0.25,-0.75,-0.25);
	glTexCoord2f(0.6,0.55); glVertex3f(0.25,-0.75,-0.25);
	glTexCoord2f(0.4,0.55); glVertex3f(0.25,-0.75,0.25);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.25,0.75,0.25);
	glVertex3f(0.25,0.25,0.75);
	glVertex3f(-0.25,0.75,0.25);
	glVertex3f(-0.25,0.25,0.75);
	glVertex3f(-0.75,0.25,0.25);
	glVertex3f(-0.25,0.75,0.25);
	glVertex3f(-0.75,0.25,-0.25);
	glVertex3f(-0.25,0.75,-0.25);
	glVertex3f(-0.25,0.25,-0.75);
	glVertex3f(0.25,0.75,-0.25);
	glVertex3f(0.25,0.25,-0.75);
	glVertex3f(0.75,0.25,-0.25);
	glVertex3f(0.25,0.75,-0.25);
	glVertex3f(0.75,0.25,0.25);
	glVertex3f(0.25,0.75,0.25);
	glVertex3f(0.25,0.25,0.75);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.25,-0.75,0.25);
	glVertex3f(0.25,-0.25,0.75);
	glVertex3f(-0.25,-0.75,0.25);
	glVertex3f(-0.25,-0.25,0.75);
	glVertex3f(-0.75,-0.25,0.25);
	glVertex3f(-0.25,-0.75,0.25);
	glVertex3f(-0.75,-0.25,-0.25);
	glVertex3f(-0.25,-0.75,-0.25);
	glVertex3f(-0.25,-0.25,-0.75);
	glVertex3f(0.25,-0.75,-0.25);
	glVertex3f(0.25,-0.25,-0.75);
	glVertex3f(0.75,-0.25,-0.25);
	glVertex3f(0.25,-0.75,-0.25);
	glVertex3f(0.75,-0.25,0.25);
	glVertex3f(0.25,-0.75,0.25);
	glVertex3f(0.25,-0.25,0.75);
	glEnd();

	glEndList();

	// Model du corps d'un Shoker
	glNewList(id_shokerCOR,GL_COMPILE);

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0,0.5); glVertex3f(2,0,0);
	glTexCoord2f(0.4,0.43); glVertex3f(0.75,0.25,0.25);
	glTexCoord2f(0.4,0.55); glVertex3f(0.75,0.25,-0.25);
	glTexCoord2f(0.4,0.43); glVertex3f(0.75,-0.25,-0.25);
	glTexCoord2f(0.4,0.55); glVertex3f(0.75,-0.25,0.25);
	glTexCoord2f(0.4,0.43); glVertex3f(0.75,0.25,0.25);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1,0.5); glVertex3f(-2,0,0);
	glTexCoord2f(0.6,0.43); glVertex3f(-0.75,0.25,0.25);
	glTexCoord2f(0.6,0.55); glVertex3f(-0.75,0.25,-0.25);
	glTexCoord2f(0.6,0.43); glVertex3f(-0.75,-0.25,-0.25);
	glTexCoord2f(0.6,0.55); glVertex3f(-0.75,-0.25,0.25);
	glTexCoord2f(0.6,0.43); glVertex3f(-0.75,0.25,0.25);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0,0.5); glVertex3f(0,0,2);
	glTexCoord2f(0.4,0.43); glVertex3f(0.25,0.25,0.75);
	glTexCoord2f(0.4,0.55); glVertex3f(-0.25,0.25,0.75);
	glTexCoord2f(0.4,0.43); glVertex3f(-0.25,-0.25,0.75);
	glTexCoord2f(0.4,0.55); glVertex3f(0.25,-0.25,0.75);
	glTexCoord2f(0.4,0.43); glVertex3f(0.25,0.25,0.75);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1,0.5); glVertex3f(0,0,-2);
	glTexCoord2f(0.6,0.43); glVertex3f(0.25,0.25,-0.75);
	glTexCoord2f(0.6,0.55); glVertex3f(-0.25,0.25,-0.75);
	glTexCoord2f(0.6,0.43); glVertex3f(-0.25,-0.25,-0.75);
	glTexCoord2f(0.6,0.55); glVertex3f(0.25,-0.25,-0.75);
	glTexCoord2f(0.6,0.43); glVertex3f(0.25,0.25,-0.75);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.6,0.45); glVertex3f(-0.25,0.25,0.75);
	glTexCoord2f(0.6,0.56); glVertex3f(-0.25,-0.25,0.75);
	glTexCoord2f(0.4,0.56); glVertex3f(-0.75,-0.25,0.25);
	glTexCoord2f(0.4,0.45); glVertex3f(-0.75,0.25,0.25);
	glTexCoord2f(0.6,0.45); glVertex3f(-0.75,0.25,-0.25);
	glTexCoord2f(0.6,0.56); glVertex3f(-0.75,-0.25,-0.25);
	glTexCoord2f(0.4,0.56); glVertex3f(-0.25,-0.25,-0.75);
	glTexCoord2f(0.4,0.45); glVertex3f(-0.25,0.25,-0.75);
	glTexCoord2f(0.4,0.45); glVertex3f(0.25,0.25,0.75);
	glTexCoord2f(0.4,0.56); glVertex3f(0.25,-0.25,0.75);
	glTexCoord2f(0.6,0.56); glVertex3f(0.75,-0.25,0.25);
	glTexCoord2f(0.6,0.45); glVertex3f(0.75,0.25,0.25);
	glTexCoord2f(0.4,0.45); glVertex3f(0.75,0.25,-0.25);
	glTexCoord2f(0.4,0.56); glVertex3f(0.75,-0.25,-0.25);
	glTexCoord2f(0.6,0.56); glVertex3f(0.25,-0.25,-0.75);
	glTexCoord2f(0.6,0.45); glVertex3f(0.25,0.25,-0.75);
	glEnd();

	glEndList();


	return;
}
