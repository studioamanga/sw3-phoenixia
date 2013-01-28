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

// Fonction d'initialisation des models
void Init_Models(void)
{
	// Allocution des id pour chaque model
	id_shokerPIQ=glGenLists(1);
	id_shokerCOR=glGenLists(1);
	id_ciel=glGenLists(1);
	id_hlm=glGenLists(1);
	id_spatioport=glGenLists(1);
	id_sol=glGenLists(1);
	id_tunnel=glGenLists(1);

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

	// Model des tours et des batiments de CyberIndus
	glNewList(id_hlm,GL_COMPILE);
	glBegin(GL_QUADS);
	// Spatioport ( haut )
	glTexCoord2f(0.1,0.8); glVertex3f(-60.,40.,-100.);
	glTexCoord2f(0.1,0.6); glVertex3f(-60.,40.,-40.);
	glTexCoord2f(0.4,0.6); glVertex3f(60.,40.,-40.);
	glTexCoord2f(0.4,0.8); glVertex3f(60.,40.,-100.);
	// Spatioport ( arrière )
	glTexCoord2f(3.,5.); glVertex3f(-60.,-120.,-40.);
	glTexCoord2f(3.,0.); glVertex3f(-60.,40.,-40.);
	glTexCoord2f(0.,0.); glVertex3f(60.,40.,-40.);
	glTexCoord2f(0.,5.); glVertex3f(60.,-120.,-40.);
	// Spatioport ( avant )
	glTexCoord2f(0.,5.); glVertex3f(-60.,-120.,-100.);
	glTexCoord2f(0.,0.); glVertex3f(-60.,40.,-100.);
	glTexCoord2f(3.,0.); glVertex3f(60.,40.,-100.);
	glTexCoord2f(3.,5.); glVertex3f(60.,-120.,-100.);
	// Spatioport ( gauche )
	glTexCoord2f(2.,5.); glVertex3f(-60.,-120.,-100.);
	glTexCoord2f(2.,0.); glVertex3f(-60.,40.,-100.);
	glTexCoord2f(0.,0.); glVertex3f(-60.,40.,-40.);
	glTexCoord2f(0.,5.); glVertex3f(-60.,-120.,-40.);
	// Spatioport ( droite )
	glTexCoord2f(0.,5.); glVertex3f(60.,-120.,-100.);
	glTexCoord2f(0.,0.); glVertex3f(60.,40.,-100.);
	glTexCoord2f(2.,0.); glVertex3f(60.,40.,-40.);
	glTexCoord2f(2.,5.); glVertex3f(60.,-120.,-40.);

	// Tour gauche ( haut )
	glTexCoord2f(0.1,0.8); glVertex3f(-90.,150.,40.);
	glTexCoord2f(0.1,0.6); glVertex3f(-90.,150.,90.);
	glTexCoord2f(0.4,0.6); glVertex3f(-20.,150.,90.);
	glTexCoord2f(0.4,0.8); glVertex3f(-20.,150.,40.);
	// Tour gauche ( arrière )
	glTexCoord2f(2.,6.); glVertex3f(-90.,-120.,90.);
	glTexCoord2f(2.,0.); glVertex3f(-90.,150.,90.);
	glTexCoord2f(0.,0.); glVertex3f(-20.,150.,90.);
	glTexCoord2f(0.,6.); glVertex3f(-20.,-120.,90.);
	// Tour gauche ( avant )
	glTexCoord2f(0.,6.); glVertex3f(-90.,-120.,40.);
	glTexCoord2f(0.,0.); glVertex3f(-90.,150.,40.);
	glTexCoord2f(2.,0.); glVertex3f(-20.,150.,40.);
	glTexCoord2f(2.,6.); glVertex3f(-20.,-120.,40.);
	// Tour gauche ( gauche )
	glTexCoord2f(2.,6.); glVertex3f(-90.,-120.,40.);
	glTexCoord2f(2.,0.); glVertex3f(-90.,150.,40.);
	glTexCoord2f(0.,0.); glVertex3f(-90.,150.,90.);
	glTexCoord2f(0.,6.); glVertex3f(-90.,-120.,90.);
	// Tour gauche ( droite )
	glTexCoord2f(0.,6.); glVertex3f(-20.,-120.,40.);
	glTexCoord2f(0.,0.); glVertex3f(-20.,150.,40.);
	glTexCoord2f(2.,0.); glVertex3f(-20.,150.,90.);
	glTexCoord2f(2.,6.); glVertex3f(-20.,-120.,90.);

	// Tour droite ( haut )
	glTexCoord2f(0.1,0.8); glVertex3f(20.,130.,40.);
	glTexCoord2f(0.1,0.6); glVertex3f(20.,130.,90.);
	glTexCoord2f(0.4,0.6); glVertex3f(50.,130.,90.);
	glTexCoord2f(0.4,0.8); glVertex3f(50.,130.,40.);
	// Tour droite ( arrière )
	glTexCoord2f(2.,5.); glVertex3f(20.,-120.,90.);
	glTexCoord2f(2.,0.); glVertex3f(20.,130.,90.);
	glTexCoord2f(0.,0.); glVertex3f(50.,130.,90.);
	glTexCoord2f(0.,5.); glVertex3f(50.,-120.,90.);
	// Tour droite ( avant )
	glTexCoord2f(0.,5.); glVertex3f(20.,-120.,40.);
	glTexCoord2f(0.,0.); glVertex3f(20.,130.,40.);
	glTexCoord2f(2.,0.); glVertex3f(50.,130.,40.);
	glTexCoord2f(2.,5.); glVertex3f(50.,-120.,40.);
	// Tour droite ( gauche )
	glTexCoord2f(1.,5.); glVertex3f(20.,-120.,40.);
	glTexCoord2f(1.,0.); glVertex3f(20.,130.,40.);
	glTexCoord2f(0.,0.); glVertex3f(20.,130.,90.);
	glTexCoord2f(0.,5.); glVertex3f(20.,-120.,90.);
	// Tour droite ( droite )
	glTexCoord2f(0.,5.); glVertex3f(50.,-120.,40.);
	glTexCoord2f(0.,0.); glVertex3f(50.,130.,40.);
	glTexCoord2f(1.,0.); glVertex3f(50.,130.,90.);
	glTexCoord2f(1.,5.); glVertex3f(50.,-120.,90.);

	// Baie arrière ( haut )
	glTexCoord2f(0.1,0.8); glVertex3f(-160.,0.,160.);
	glTexCoord2f(0.1,0.6); glVertex3f(-160.,0.,180.);
	glTexCoord2f(0.4,0.6); glVertex3f(160.,0.,180.);
	glTexCoord2f(0.4,0.8); glVertex3f(160.,0.,160.);
	// Baie arrière ( arrière )
	glTexCoord2f(8.,3.); glVertex3f(-160.,-120.,180.);
	glTexCoord2f(8.,0.); glVertex3f(-160.,0.,180.);
	glTexCoord2f(0.,0.); glVertex3f(160.,0.,180.);
	glTexCoord2f(0.,3.); glVertex3f(160.,-120.,180.);
	// Baie arrière ( avant )
	glTexCoord2f(0.,3.); glVertex3f(-160.,-120.,160.);
	glTexCoord2f(0.,0.); glVertex3f(-160.,0.,160.);
	glTexCoord2f(8.,0.); glVertex3f(160.,0.,160.);
	glTexCoord2f(8.,3.); glVertex3f(160.,-120.,160.);
	// Baie arrière ( gauche )
	glTexCoord2f(1.,3.); glVertex3f(-160.,-120.,160.);
	glTexCoord2f(1.,0.); glVertex3f(-160.,0.,160.);
	glTexCoord2f(0.,0.); glVertex3f(-160.,0.,180.);
	glTexCoord2f(0.,3.); glVertex3f(-160.,-120.,180.);
	// Baie arrière ( droite )
	glTexCoord2f(0.,3.); glVertex3f(160.,-120.,160.);
	glTexCoord2f(0.,0.); glVertex3f(160.,0.,160.);
	glTexCoord2f(1.,0.); glVertex3f(160.,0.,180.);
	glTexCoord2f(1.,3.); glVertex3f(160.,-120.,180.);

	// Baie avant ( haut )
	glTexCoord2f(0.1,0.8); glVertex3f(-160.,0.,120.);
	glTexCoord2f(0.1,0.6); glVertex3f(-160.,0.,140.);
	glTexCoord2f(0.4,0.6); glVertex3f(160.,0.,140.);
	glTexCoord2f(0.4,0.8); glVertex3f(160.,0.,120.);
	// Baie avant ( arrière )
	glTexCoord2f(8.,3.); glVertex3f(-160.,-120.,140.);
	glTexCoord2f(8.,0.); glVertex3f(-160.,0.,140.);
	glTexCoord2f(0.,0.); glVertex3f(160.,0.,140.);
	glTexCoord2f(0.,3.); glVertex3f(160.,-120.,140.);
	// Baie avant ( avant )
	glTexCoord2f(0.,3.); glVertex3f(-160.,-120.,120.);
	glTexCoord2f(0.,0.); glVertex3f(-160.,0.,120.);
	glTexCoord2f(8.,0.); glVertex3f(160.,0.,120.);
	glTexCoord2f(8.,3.); glVertex3f(160.,-120.,120.);
	// Baie avant ( gauche )
	glTexCoord2f(1.,3.); glVertex3f(-160.,-120.,120.);
	glTexCoord2f(1.,0.); glVertex3f(-160.,0.,120.);
	glTexCoord2f(0.,0.); glVertex3f(-160.,0.,140.);
	glTexCoord2f(0.,3.); glVertex3f(-160.,-120.,140.);
	// Baie avant ( droite )
	glTexCoord2f(0.,3.); glVertex3f(160.,-120.,120.);
	glTexCoord2f(0.,0.); glVertex3f(160.,0.,120.);
	glTexCoord2f(1.,0.); glVertex3f(160.,0.,140.);
	glTexCoord2f(1.,3.); glVertex3f(160.,-120.,140.);

	glEnd();
	glEndList();

	// Model pour un cube d'environement de 1000*1000*1000
	glNewList(id_ciel,GL_COMPILE);
	glBegin(GL_QUADS);
	// Cube d'environnement ( bas )
	glTexCoord2f(0.,0.); glVertex3f(-1000.,-1000.,-1000.);
	glTexCoord2f(0.,1.); glVertex3f(-1000.,-1000.,1000.);
	glTexCoord2f(1.,1.); glVertex3f(1000.,-1000.,1000.);
	glTexCoord2f(1.,0.); glVertex3f(1000.,-1000.,-1000.);
	// Cube d'environnement ( haut )
	glTexCoord2f(0.,0.); glVertex3f(-1000.,1000.,-1000.);
	glTexCoord2f(0.,1.); glVertex3f(-1000.,1000.,1000.);
	glTexCoord2f(1.,1.); glVertex3f(1000.,1000.,1000.);
	glTexCoord2f(1.,0.); glVertex3f(1000.,1000.,-1000.);
	// Cube d'environnement ( arrière )
	glTexCoord2f(0.,0.); glVertex3f(-1000.,-1000.,1000.);
	glTexCoord2f(0.,1.); glVertex3f(-1000.,1000.,1000.);
	glTexCoord2f(1.,1.); glVertex3f(1000.,1000.,1000.);
	glTexCoord2f(1.,0.); glVertex3f(1000.,-1000.,1000.);
	// Cube d'environnement ( avant )
	glTexCoord2f(0.,0.); glVertex3f(-1000.,-1000.,-1000.);
	glTexCoord2f(0.,1.); glVertex3f(-1000.,1000.,-1000.);
	glTexCoord2f(1.,1.); glVertex3f(1000.,1000.,-1000.);
	glTexCoord2f(1.,0.); glVertex3f(1000.,-1000.,-1000.);
	// Cube d'environnement ( gauche )
	glTexCoord2f(0.,0.); glVertex3f(-1000.,-1000.,-1000.);
	glTexCoord2f(0.,1.); glVertex3f(-1000.,1000.,-1000.);
	glTexCoord2f(1.,1.); glVertex3f(-1000.,1000.,1000.);
	glTexCoord2f(1.,0.); glVertex3f(-1000.,-1000.,1000.);
	// Cube d'environnement ( droite )
	glTexCoord2f(0.,0.); glVertex3f(1000.,-1000.,-1000.);
	glTexCoord2f(0.,1.); glVertex3f(1000.,1000.,-1000.);
	glTexCoord2f(1.,1.); glVertex3f(1000.,1000.,1000.);
	glTexCoord2f(1.,0.); glVertex3f(1000.,-1000.,1000.);

	glEnd();
	glEndList();

	// Model des plateformes et piliers du spatioport de CyberIndus
	glNewList(id_spatioport,GL_COMPILE);
	glBegin(GL_QUADS);
	// Inférieur majeure ( bas )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,-45.,-360.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,-45.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(640.,-45.,-680.);
	glTexCoord2f(0.9,0.); glVertex3f(640.,-45.,-360.);
	// Inférieur majeure ( haut )
	glTexCoord2f(0.,0.); glVertex3f(-640.,-40.,-360.);
	glTexCoord2f(0.,4.); glVertex3f(-640.,-40.,-680.);
	glTexCoord2f(10.5,4.); glVertex3f(640.,-40.,-680.);
	glTexCoord2f(10.5,0.); glVertex3f(640.,-40.,-360.);
	// Inférieur majeure ( arrière )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,-40.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,-45.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(640.,-45.,-680.);
	glTexCoord2f(0.9,0.); glVertex3f(640.,-40.,-680.);
	// Inférieur majeure ( avant )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,-40.,-360.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,-45.,-360.);
	glTexCoord2f(0.9,1.); glVertex3f(640.,-45.,-360.);
	glTexCoord2f(0.9,0.); glVertex3f(640.,-40.,-360.);
	// Inférieur majeure ( gauche )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,-40.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,-45.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(-640.,-45.,-360.);
	glTexCoord2f(0.9,0.); glVertex3f(-640.,-40.,-360.);
	// Inférieur majeure ( droite )
	glTexCoord2f(0.85,0.); glVertex3f(640.,-40.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(640.,-45.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(640.,-45.,-360.);
	glTexCoord2f(0.9,0.); glVertex3f(640.,-40.,-360.);
	// Supérieur majeure ( bas )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,115.,-360.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,115.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(640.,115.,-680.);
	glTexCoord2f(0.9,0.); glVertex3f(640.,115.,-360.);
	// Supérieur majeure ( haut )
	glTexCoord2f(0.,0.); glVertex3f(-640.,120.,-360.);
	glTexCoord2f(0.,4.); glVertex3f(-640.,120.,-680.);
	glTexCoord2f(10.5,4.); glVertex3f(640.,120.,-680.);
	glTexCoord2f(10.5,0.); glVertex3f(640.,120.,-360.);
	// Supérieur majeure ( arrière )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,115.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,120.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(640.,120.,-680.);
	glTexCoord2f(0.9,0.); glVertex3f(640.,115.,-680.);
	// Supérieur majeure ( avant )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,115.,-360.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,120.,-360.);
	glTexCoord2f(0.9,1.); glVertex3f(640.,120.,-360.);
	glTexCoord2f(0.9,0.); glVertex3f(640.,115.,-360.);
	// Supérieur majeure ( gauche )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,115.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,120.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(-640.,120.,-360.);
	glTexCoord2f(0.9,0.); glVertex3f(-640.,115.,-360.);
	// Supérieur majeure ( droite )
	glTexCoord2f(0.85,0.); glVertex3f(640.,115.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(640.,120.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(640.,120.,-360.);
	glTexCoord2f(0.9,0.); glVertex3f(640.,115.,-360.);
	// Gauche majeure ( bas )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,75.,680.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,75.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(-320.,75.,-680.);
	glTexCoord2f(0.9,0.); glVertex3f(-320.,75.,680.);
	// Gauche majeure ( haut )
	glTexCoord2f(0.,0.); glVertex3f(-640.,80.,680.);
	glTexCoord2f(0.,10.5); glVertex3f(-640.,80.,-680.);
	glTexCoord2f(4.,10.5); glVertex3f(-320.,80.,-680.);
	glTexCoord2f(4.,0.); glVertex3f(-320.,80.,680.);
	// Gauche majeure ( arrière )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,75.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,80.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(-320.,80.,-680.);
	glTexCoord2f(0.9,0.); glVertex3f(-320.,75.,-680.);
	// Gauche majeure ( avant )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,75.,680.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,80.,680.);
	glTexCoord2f(0.9,1.); glVertex3f(-320.,80.,680.);
	glTexCoord2f(0.9,0.); glVertex3f(-320.,75.,680.);
	// Gauche majeure ( gauche )
	glTexCoord2f(0.85,0.); glVertex3f(-640.,75.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(-640.,80.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(-640.,80.,680.);
	glTexCoord2f(0.9,0.); glVertex3f(-640.,75.,680.);
	// Gauche majeure ( droite )
	glTexCoord2f(0.85,0.); glVertex3f(-320.,75.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(-320.,80.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(-320.,80.,680.);
	glTexCoord2f(0.9,0.); glVertex3f(-320.,75.,680.);
	// Droite majeure ( bas )
	glTexCoord2f(0.85,0.); glVertex3f(640.,75.,680.);
	glTexCoord2f(0.85,1.); glVertex3f(640.,75.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(320.,75.,-680.);
	glTexCoord2f(0.9,0.); glVertex3f(320.,75.,680.);
	// Droite majeure ( haut )
	glTexCoord2f(0.,0.); glVertex3f(640.,80.,680.);
	glTexCoord2f(0.,10.5); glVertex3f(640.,80.,-680.);
	glTexCoord2f(4.,10.5); glVertex3f(320.,80.,-680.);
	glTexCoord2f(4.,0.); glVertex3f(320.,80.,680.);
	// Droite majeure ( arrière )
	glTexCoord2f(0.85,0.); glVertex3f(640.,75.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(640.,80.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(320.,80.,-680.);
	glTexCoord2f(0.9,0.); glVertex3f(320.,75.,-680.);
	// Droite majeure ( avant )
	glTexCoord2f(0.85,0.); glVertex3f(640.,75.,680.);
	glTexCoord2f(0.85,1.); glVertex3f(640.,80.,680.);
	glTexCoord2f(0.9,1.); glVertex3f(320.,80.,680.);
	glTexCoord2f(0.9,0.); glVertex3f(320.,75.,680.);
	// Droite majeure ( gauche )
	glTexCoord2f(0.85,0.); glVertex3f(640.,75.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(640.,80.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(640.,80.,680.);
	glTexCoord2f(0.9,0.); glVertex3f(640.,75.,680.);
	// Droite majeure ( droite )
	glTexCoord2f(0.85,0.); glVertex3f(320.,75.,-680.);
	glTexCoord2f(0.85,1.); glVertex3f(320.,80.,-680.);
	glTexCoord2f(0.9,1.); glVertex3f(320.,80.,680.);
	glTexCoord2f(0.9,0.); glVertex3f(320.,75.,680.);

	// Supérieur ( bas )
	glTexCoord2f(0.85,0.); glVertex3f(-180.,20.,-80.);
	glTexCoord2f(0.85,1.); glVertex3f(-180.,20.,-140.);
	glTexCoord2f(0.9,1.); glVertex3f(180.,20.,-140.);
	glTexCoord2f(0.9,0.); glVertex3f(180.,20.,-80.);
	// Supérieur ( haut )
	glTexCoord2f(0.,0.); glVertex3f(-180.,25.,-80.);
	glTexCoord2f(0.,1.); glVertex3f(-180.,25.,-140.);
	glTexCoord2f(3.,1.); glVertex3f(180.,25.,-140.);
	glTexCoord2f(3.,0.); glVertex3f(180.,25.,-80.);
	// Supérieur ( arrière )
	glTexCoord2f(0.85,0.); glVertex3f(-180.,25.,-140.);
	glTexCoord2f(0.85,1.); glVertex3f(-180.,20.,-140.);
	glTexCoord2f(0.9,1.); glVertex3f(180.,20.,-140.);
	glTexCoord2f(0.9,0.); glVertex3f(180.,25.,-140.);
	// Supérieur ( avant )
	glTexCoord2f(0.85,0.); glVertex3f(-180.,25.,-80.);
	glTexCoord2f(0.85,1.); glVertex3f(-180.,20.,-80.);
	glTexCoord2f(0.9,1.); glVertex3f(180.,20.,-80.);
	glTexCoord2f(0.9,0.); glVertex3f(180.,25.,-80.);
	// Supérieur ( gauche )
	glTexCoord2f(0.85,0.); glVertex3f(-180.,25.,-140.);
	glTexCoord2f(0.85,1.); glVertex3f(-180.,20.,-140.);
	glTexCoord2f(0.9,1.); glVertex3f(-180.,20.,-80.);
	glTexCoord2f(0.9,0.); glVertex3f(-180.,25.,-80.);
	// Supérieur ( droite )
	glTexCoord2f(0.85,0.); glVertex3f(180.,25.,-140.);
	glTexCoord2f(0.85,1.); glVertex3f(180.,20.,-140.);
	glTexCoord2f(0.9,1.); glVertex3f(180.,20.,-80.);
	glTexCoord2f(0.9,0.); glVertex3f(180.,25.,-80.);

	// Inférieur ( bas )
	glTexCoord2f(0.85,0.); glVertex3f(-180.,-55.,20.);
	glTexCoord2f(0.85,1.); glVertex3f(-180.,-55.,-140.);
	glTexCoord2f(0.9,1.); glVertex3f(180.,-55.,-140.);
	glTexCoord2f(0.9,0.); glVertex3f(180.,-55.,20.);
	// Inférieur ( haut )
	glTexCoord2f(0.,0.); glVertex3f(-180.,-50.,20.);
	glTexCoord2f(0.,2.); glVertex3f(-180.,-50.,-140.);
	glTexCoord2f(3.,2.); glVertex3f(180.,-50.,-140.);
	glTexCoord2f(3.,0.); glVertex3f(180.,-50.,20.);
	// Inférieur ( arrière )
	glTexCoord2f(0.85,0.); glVertex3f(-180.,-50.,-140.);
	glTexCoord2f(0.85,1.); glVertex3f(-180.,-55.,-140.);
	glTexCoord2f(0.9,1.); glVertex3f(180.,-55.,-140.);
	glTexCoord2f(0.9,0.); glVertex3f(180.,-50.,-140.);
	// Inférieur ( avant )
	glTexCoord2f(0.85,0.); glVertex3f(-180.,-50.,20.);
	glTexCoord2f(0.85,1.); glVertex3f(-180.,-55.,20.);
	glTexCoord2f(0.9,1.); glVertex3f(180.,-55.,20.);
	glTexCoord2f(0.9,0.); glVertex3f(180.,-50.,20.);
	// Inférieur ( gauche )
	glTexCoord2f(0.85,0.); glVertex3f(-180.,-50.,-140.);
	glTexCoord2f(0.85,1.); glVertex3f(-180.,-55.,-140.);
	glTexCoord2f(0.9,1.); glVertex3f(-180.,-55.,20.);
	glTexCoord2f(0.9,0.); glVertex3f(-180.,-50.,20.);
	// Inférieur ( droite )
	glTexCoord2f(0.85,0.); glVertex3f(180.,-50.,-140.);
	glTexCoord2f(0.85,1.); glVertex3f(180.,-55.,-140.);
	glTexCoord2f(0.9,1.); glVertex3f(180.,-55.,20.);
	glTexCoord2f(0.9,0.); glVertex3f(180.,-50.,20.);

	// Pilier central ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(0.,250.,10.);
	glTexCoord2f(0.8,0.3); glVertex3f(10.,250.,0.);
	glTexCoord2f(0.9,0.3); glVertex3f(0.,250.,-10.);
	glTexCoord2f(0.9,0.2); glVertex3f(-10.,250.,0.);
	// Pilier central ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(10.,-120.,0.);
	glTexCoord2f(0.8,0.3); glVertex3f(10.,250.,0.);
	glTexCoord2f(0.9,0.3); glVertex3f(0.,250.,-10.);
	glTexCoord2f(0.9,0.2); glVertex3f(0.,-120.,-10.);
	// Pilier central ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(0.,-120.,-10.);
	glTexCoord2f(0.8,0.3); glVertex3f(0.,250.,-10.);
	glTexCoord2f(0.9,0.3); glVertex3f(-10.,250.,0.);
	glTexCoord2f(0.9,0.2); glVertex3f(-10.,-120.,0.);
	// Pilier central ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-10.,-120.,0.);
	glTexCoord2f(0.8,0.3); glVertex3f(-10.,250.,0.);
	glTexCoord2f(0.9,0.3); glVertex3f(0.,250.,10.);
	glTexCoord2f(0.9,0.2); glVertex3f(0.,-120.,10.);
	// Pilier central ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(0.,-120.,10.);
	glTexCoord2f(0.8,0.3); glVertex3f(0.,250.,10.);
	glTexCoord2f(0.9,0.3); glVertex3f(10.,250.,0.);
	glTexCoord2f(0.9,0.2); glVertex3f(10.,-120.,0.);

	// Pilier majeur gauche ( avant gauche ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,200.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,-550.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,200.,-570.);
	// Pilier majeur gauche ( avant gauche ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,-550.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,-550.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,-550.);
	// Pilier majeur gauche ( avant gauche ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,-570.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,-570.);
	// Pilier majeur gauche ( avant gauche ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-550.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-550.,-120.,-550.);
	// Pilier majeur gauche ( avant gauche ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(-530.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-530.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,-550.);
	// Pilier majeur gauche ( avant droit ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,200.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,-550.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,200.,-570.);
	// Pilier majeur gauche ( avant droit ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,-120.,-550.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,-550.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,-120.,-550.);
	// Pilier majeur gauche ( avant droit ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,-570.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,-120.,-570.);
	// Pilier majeur gauche ( avant droit ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-470.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-470.,-120.,-550.);
	// Pilier majeur gauche ( avant droit ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(-450.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-450.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,-120.,-550.);
	// Pilier majeur gauche ( arrière gauche ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,200.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,-470.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,200.,-490.);
	// Pilier majeur gauche ( arrière gauche ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,-470.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,-470.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,-470.);
	// Pilier majeur gauche ( arrière gauche ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,-490.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,-490.);
	// Pilier majeur gauche ( arrière gauche ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(-550.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-550.,-120.,-470.);
	// Pilier majeur gauche ( arrière gauche ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(-530.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-530.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,-470.);
	// Pilier majeur gauche ( arrière droit ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,200.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,-470.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,200.,-490.);
	// Pilier majeur gauche ( arrière droit ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,-120.,-470.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,-470.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,-120.,-470.);
	// Pilier majeur gauche ( arrière droit ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,-490.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,-120.,-490.);
	// Pilier majeur gauche ( arrière droit ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(-470.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-470.,-120.,-470.);
	// Pilier majeur gauche ( arrière droit ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(-450.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-450.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,-120.,-470.);

	// Pilier arrière majeur gauche ( avant gauche ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,200.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,550.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,200.,570.);
	// Pilier arrière majeur gauche ( avant gauche ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,550.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,550.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,550.);
	// Pilier arrière majeur gauche ( avant gauche ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,570.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,570.);
	// Pilier arrière majeur gauche ( avant gauche ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-550.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-550.,-120.,550.);
	// Pilier arrière majeur gauche ( avant gauche ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(-530.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-530.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,550.);
	// Pilier arrière majeur gauche ( avant droit ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,200.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,550.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,200.,570.);
	// Pilier arrière majeur gauche ( avant droit ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,-120.,550.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,550.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,-120.,550.);
	// Pilier arrière majeur gauche ( avant droit ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,570.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,-120.,570.);
	// Pilier arrière majeur gauche ( avant droit ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-470.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-470.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-470.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-470.,-120.,550.);
	// Pilier arrière majeur gauche ( avant droit ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(-450.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(-450.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(-450.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(-450.,-120.,550.);
	// Pilier arrière majeur gauche ( arrière gauche ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,200.,490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,470.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,200.,490.);
	// Pilier arrière majeur gauche ( arrière gauche ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,470.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,470.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,470.);
	// Pilier arrière majeur gauche ( arrière gauche ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,490.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,490.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,490.);
	// Pilier arrière majeur gauche ( arrière gauche ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-550.,-120.,490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-550.,200.,490.);
	glTexCoord2f(0.9,0.3); glVertex3f(-550.,200.,470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-550.,-120.,470.);
	// Pilier arrière majeur gauche ( arrière gauche ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(-530.,-120.,490.);
	glTexCoord2f(0.8,0.3); glVertex3f(-530.,200.,490.);
	glTexCoord2f(0.9,0.3); glVertex3f(-530.,200.,470.);
	glTexCoord2f(0.9,0.2); glVertex3f(-530.,-120.,470.);

	// Pilier majeur droit ( avant gauche ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,200.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,-550.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,200.,-570.);
	// Pilier majeur droit ( avant gauche ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,-550.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,-550.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,-550.);
	// Pilier majeur droit ( avant gauche ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,-570.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,-570.);
	// Pilier majeur droit ( avant gauche ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(550.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(550.,-120.,-550.);
	// Pilier majeur droit ( avant gauche ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(530.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(530.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,-550.);
	// Pilier majeur droit ( avant droit ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,200.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,-550.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,200.,-570.);
	// Pilier majeur droit ( avant droit ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,-120.,-550.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,-550.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,-120.,-550.);
	// Pilier majeur droit ( avant droit ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,-570.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,-120.,-570.);
	// Pilier majeur droit ( avant droit ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(470.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(470.,-120.,-550.);
	// Pilier majeur droit ( avant droit ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(450.,-120.,-570.);
	glTexCoord2f(0.8,0.3); glVertex3f(450.,200.,-570.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,-550.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,-120.,-550.);
	// Pilier majeur droit ( arrière gauche ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,200.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,-470.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,200.,-490.);
	// Pilier majeur droit ( arrière gauche ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,-470.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,-470.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,-470.);
	// Pilier majeur droit ( arrière gauche ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,-490.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,-490.);
	// Pilier majeur droit ( arrière gauche ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(550.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(550.,-120.,-470.);
	// Pilier majeur droit ( arrière gauche ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(530.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(530.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,-470.);
	// Pilier majeur droit ( arrière droit ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,200.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,-470.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,200.,-490.);
	// Pilier majeur droit ( arrière droit ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,-120.,-470.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,-470.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,-120.,-470.);
	// Pilier majeur droit ( arrière droit ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,-490.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,-120.,-490.);
	// Pilier majeur droit ( arrière droit ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(470.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(470.,-120.,-470.);
	// Pilier majeur droit ( arrière droit ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(450.,-120.,-490.);
	glTexCoord2f(0.8,0.3); glVertex3f(450.,200.,-490.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,-470.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,-120.,-470.);

	// Pilier arrière majeur droit ( avant gauche ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,200.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,550.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,200.,570.);
	// Pilier arrière majeur droit ( avant gauche ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,550.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,550.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,550.);
	// Pilier arrière majeur droit ( avant gauche ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,570.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,570.);
	// Pilier arrière majeur droit ( avant gauche ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(550.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(550.,-120.,550.);
	// Pilier arrière majeur droit ( avant gauche ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(530.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(530.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,550.);
	// Pilier arrière majeur droit ( avant droit ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,200.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,550.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,200.,570.);
	// Pilier arrière majeur droit ( avant droit ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,-120.,550.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,550.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,-120.,550.);
	// Pilier arrière majeur droit ( avant droit ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,570.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,-120.,570.);
	// Pilier arrière majeur droit ( avant droit ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(470.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(470.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(470.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(470.,-120.,550.);
	// Pilier arrière majeur droit ( avant droit ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(450.,-120.,570.);
	glTexCoord2f(0.8,0.3); glVertex3f(450.,200.,570.);
	glTexCoord2f(0.9,0.3); glVertex3f(450.,200.,550.);
	glTexCoord2f(0.9,0.2); glVertex3f(450.,-120.,550.);
	// Pilier arrière majeur droit ( arrière gauche ) ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,200.,490.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,470.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,470.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,200.,490.);
	// Pilier arrière majeur droit ( arrière gauche ) ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,470.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,470.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,470.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,470.);
	// Pilier arrière majeur droit ( arrière gauche ) ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,490.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,490.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,490.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,490.);
	// Pilier arrière majeur droit ( arrière gauche ) ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(550.,-120.,490.);
	glTexCoord2f(0.8,0.3); glVertex3f(550.,200.,490.);
	glTexCoord2f(0.9,0.3); glVertex3f(550.,200.,470.);
	glTexCoord2f(0.9,0.2); glVertex3f(550.,-120.,470.);
	// Pilier arrière majeur droit ( arrière gauche ) ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(530.,-120.,490.);
	glTexCoord2f(0.8,0.3); glVertex3f(530.,200.,490.);
	glTexCoord2f(0.9,0.3); glVertex3f(530.,200.,470.);
	glTexCoord2f(0.9,0.2); glVertex3f(530.,-120.,470.);

	// Pilier avant gauche ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(-110.,100.,-120.);
	glTexCoord2f(0.8,0.3); glVertex3f(-110.,100.,-100.);
	glTexCoord2f(0.9,0.3); glVertex3f(-90.,100.,-100.);
	glTexCoord2f(0.9,0.2); glVertex3f(-90.,100.,-120.);
	// Pilier avant gauche ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(-110.,-120.,-100.);
	glTexCoord2f(0.8,0.3); glVertex3f(-110.,100.,-100.);
	glTexCoord2f(0.9,0.3); glVertex3f(-90.,100.,-100.);
	glTexCoord2f(0.9,0.2); glVertex3f(-90.,-120.,-100.);
	// Pilier avant gauche ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(-110.,-120.,-120.);
	glTexCoord2f(0.8,0.3); glVertex3f(-110.,100.,-120.);
	glTexCoord2f(0.9,0.3); glVertex3f(-90.,100.,-120.);
	glTexCoord2f(0.9,0.2); glVertex3f(-90.,-120.,-120.);
	// Pilier avant gauche ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-110.,-120.,-120.);
	glTexCoord2f(0.8,0.3); glVertex3f(-110.,100.,-120.);
	glTexCoord2f(0.9,0.3); glVertex3f(-110.,100.,-100.);
	glTexCoord2f(0.9,0.2); glVertex3f(-110.,-120.,-100.);
	// Pilier avant gauche ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(-90.,-120.,-120.);
	glTexCoord2f(0.8,0.3); glVertex3f(-90.,100.,-120.);
	glTexCoord2f(0.9,0.3); glVertex3f(-90.,100.,-100.);
	glTexCoord2f(0.9,0.2); glVertex3f(-90.,-120.,-100.);

	// Pilier avant droit ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(90.,100.,-120.);
	glTexCoord2f(0.8,0.3); glVertex3f(90.,100.,-100.);
	glTexCoord2f(0.9,0.3); glVertex3f(110.,100.,-100.);
	glTexCoord2f(0.9,0.2); glVertex3f(110.,100.,-120.);
	// Pilier avant droit ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(90.,-120.,-100.);
	glTexCoord2f(0.8,0.3); glVertex3f(90.,100.,-100.);
	glTexCoord2f(0.9,0.3); glVertex3f(110.,100.,-100.);
	glTexCoord2f(0.9,0.2); glVertex3f(110.,-120.,-100.);
	// Pilier avant droit ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(90.,-120.,-120.);
	glTexCoord2f(0.8,0.3); glVertex3f(90.,100.,-120.);
	glTexCoord2f(0.9,0.3); glVertex3f(110.,100.,-120.);
	glTexCoord2f(0.9,0.2); glVertex3f(110.,-120.,-120.);
	// Pilier avant droit ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(90.,-120.,-120.);
	glTexCoord2f(0.8,0.3); glVertex3f(90.,100.,-120.);
	glTexCoord2f(0.9,0.3); glVertex3f(90.,100.,-100.);
	glTexCoord2f(0.9,0.2); glVertex3f(90.,-120.,-100.);
	// Pilier avant droit ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(110.,-120.,-120.);
	glTexCoord2f(0.8,0.3); glVertex3f(110.,100.,-120.);
	glTexCoord2f(0.9,0.3); glVertex3f(110.,100.,-100.);
	glTexCoord2f(0.9,0.2); glVertex3f(110.,-120.,-100.);

	// Pilier arrière gauche ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(-110.,50.,-40.);
	glTexCoord2f(0.8,0.3); glVertex3f(-110.,50.,-20.);
	glTexCoord2f(0.9,0.3); glVertex3f(-90.,50.,-20.);
	glTexCoord2f(0.9,0.2); glVertex3f(-90.,50.,-40.);
	// Pilier arrière gauche ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(-110.,-120.,-20.);
	glTexCoord2f(0.8,0.3); glVertex3f(-110.,50.,-20.);
	glTexCoord2f(0.9,0.3); glVertex3f(-90.,50.,-20.);
	glTexCoord2f(0.9,0.2); glVertex3f(-90.,-120.,-20.);
	// Pilier arrière gauche ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(-110.,-120.,-40.);
	glTexCoord2f(0.8,0.3); glVertex3f(-110.,50.,-40.);
	glTexCoord2f(0.9,0.3); glVertex3f(-90.,50.,-40.);
	glTexCoord2f(0.9,0.2); glVertex3f(-90.,-120.,-40.);
	// Pilier arrière gauche ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(-110.,-120.,-40.);
	glTexCoord2f(0.8,0.3); glVertex3f(-110.,50.,-40.);
	glTexCoord2f(0.9,0.3); glVertex3f(-110.,50.,-20.);
	glTexCoord2f(0.9,0.2); glVertex3f(-110.,-120.,-20.);
	// Pilier arrière gauche ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(-90.,-120.,-40.);
	glTexCoord2f(0.8,0.3); glVertex3f(-90.,50.,-40.);
	glTexCoord2f(0.9,0.3); glVertex3f(-90.,50.,-20.);
	glTexCoord2f(0.9,0.2); glVertex3f(-90.,-120.,-20.);

	// Pilier arrière droit ( haut )
	glTexCoord2f(0.8,0.2); glVertex3f(90.,50.,-40.);
	glTexCoord2f(0.8,0.3); glVertex3f(90.,50.,-20.);
	glTexCoord2f(0.9,0.3); glVertex3f(110.,50.,-20.);
	glTexCoord2f(0.9,0.2); glVertex3f(110.,50.,-40.);
	// Pilier arrière droit ( arrière )
	glTexCoord2f(0.8,0.2); glVertex3f(90.,-120.,-20.);
	glTexCoord2f(0.8,0.3); glVertex3f(90.,50.,-20.);
	glTexCoord2f(0.9,0.3); glVertex3f(110.,50.,-20.);
	glTexCoord2f(0.9,0.2); glVertex3f(110.,-120.,-20.);
	// Pilier arrière droit ( avant )
	glTexCoord2f(0.8,0.2); glVertex3f(90.,-120.,-40.);
	glTexCoord2f(0.8,0.3); glVertex3f(90.,50.,-40.);
	glTexCoord2f(0.9,0.3); glVertex3f(110.,50.,-40.);
	glTexCoord2f(0.9,0.2); glVertex3f(110.,-120.,-40.);
	// Pilier arrière droit ( gauche )
	glTexCoord2f(0.8,0.2); glVertex3f(90.,-120.,-40.);
	glTexCoord2f(0.8,0.3); glVertex3f(90.,50.,-40.);
	glTexCoord2f(0.9,0.3); glVertex3f(90.,50.,-20.);
	glTexCoord2f(0.9,0.2); glVertex3f(90.,-120.,-20.);
	// Pilier arrière droit ( droite )
	glTexCoord2f(0.8,0.2); glVertex3f(110.,-120.,-40.);
	glTexCoord2f(0.8,0.3); glVertex3f(110.,50.,-40.);
	glTexCoord2f(0.9,0.3); glVertex3f(110.,50.,-20.);
	glTexCoord2f(0.9,0.2); glVertex3f(110.,-120.,-20.);

	glEnd();
	glEndList();

	// Model pour le sol
	glNewList(id_sol,GL_COMPILE);
	glBegin(GL_QUADS);
	// Partie gauche
	glTexCoord2f(0.,30.); glVertex3f(-1000.,-120.,-1000.);
	glTexCoord2f(0.,0.); glVertex3f(-1000.,-120.,1000.);
	glTexCoord2f(14.,0.); glVertex3f(-90.,-120.,1000.);
	glTexCoord2f(14.,30.); glVertex3f(-90.,-120.,-1000.);
	// Partie medio-gauche arrière
	glTexCoord2f(0.,30.); glVertex3f(-90.,-120.,5.);
	glTexCoord2f(0.,0.); glVertex3f(-90.,-120.,1000.);
	glTexCoord2f(1.,0.); glVertex3f(-70.,-120.,1000.);
	glTexCoord2f(1.,30.); glVertex3f(-70.,-120.,5.);
	// Partie medio-gauche avant
	glTexCoord2f(0.,30.); glVertex3f(-90.,-120.,-1000.);
	glTexCoord2f(0.,0.); glVertex3f(-90.,-120.,-10.);
	glTexCoord2f(1.,0.); glVertex3f(-70.,-120.,-10.);
	glTexCoord2f(1.,30.); glVertex3f(-70.,-120.,-1000.);
	// Partie medio-gauche
	glTexCoord2f(0.,30.); glVertex3f(-70.,-120.,-1000.);
	glTexCoord2f(0.,0.); glVertex3f(-70.,-120.,1000.);
	glTexCoord2f(3.,0.); glVertex3f(-10.,-120.,1000.);
	glTexCoord2f(3.,30.); glVertex3f(-10.,-120.,-1000.);
	// Partie mediane
	glTexCoord2f(0.,13.); glVertex3f(-10.,-120.,-355.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-120.,142.);
	glTexCoord2f(1.,0.); glVertex3f(10.,-120.,142.);
	glTexCoord2f(1.,13.); glVertex3f(10.,-120.,-355.);
	// Partie mediane arrière
	glTexCoord2f(0.,12.); glVertex3f(-10.,-120.,157.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-120.,1000.);
	glTexCoord2f(1.,0.); glVertex3f(10.,-120.,1000.);
	glTexCoord2f(1.,12.); glVertex3f(10.,-120.,157.);
	// Partie mediane avant
	glTexCoord2f(0.,5.); glVertex3f(-10.,-120.,-1000.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-120.,-455.);
	glTexCoord2f(1.,0.); glVertex3f(10.,-120.,-455.);
	glTexCoord2f(1.,5.); glVertex3f(10.,-120.,-1000.);
	// Partie medio-droite arrière
	glTexCoord2f(0.,30.); glVertex3f(70.,-120.,5.);
	glTexCoord2f(0.,0.); glVertex3f(70.,-120.,1000.);
	glTexCoord2f(1.,0.); glVertex3f(90.,-120.,1000.);
	glTexCoord2f(1.,30.); glVertex3f(90.,-120.,5.);
	// Partie medio-droite avant
	glTexCoord2f(0.,30.); glVertex3f(70.,-120.,-1000.);
	glTexCoord2f(0.,0.); glVertex3f(70.,-120.,-10.);
	glTexCoord2f(1.,0.); glVertex3f(90.,-120.,-10.);
	glTexCoord2f(1.,30.); glVertex3f(90.,-120.,-1000.);
	// Partie medio-droite
	glTexCoord2f(0.,30.); glVertex3f(10.,-120.,-1000.);
	glTexCoord2f(0.,0.); glVertex3f(10.,-120.,1000.);
	glTexCoord2f(3.,0.); glVertex3f(70.,-120.,1000.);
	glTexCoord2f(3.,30.); glVertex3f(70.,-120.,-1000.);
	// Partie droite
	glTexCoord2f(0.,30.); glVertex3f(1000.,-120.,-1000.);
	glTexCoord2f(0.,0.); glVertex3f(1000.,-120.,1000.);
	glTexCoord2f(14.,0.); glVertex3f(90.,-120.,1000.);
	glTexCoord2f(14.,30.); glVertex3f(90.,-120.,-1000.);

	glEnd();
	glEndList();

	// Model pour les tunnels
	glNewList(id_tunnel,GL_COMPILE);
	glBegin(GL_QUADS);
	// Pass supérieur sup : haut
	glTexCoord2f(0.,0.); glVertex3f(0.,260.,10.);
	glTexCoord2f(0.,10.); glVertex3f(0.,300.,10.);
	glTexCoord2f(3.,10.); glVertex3f(10.,300.,0.);
	glTexCoord2f(3.,0.); glVertex3f(10.,260.,0.);
	// Pass supérieur sup : bas
	glTexCoord2f(0.,0.); glVertex3f(10.,260.,0.);
	glTexCoord2f(0.,10.); glVertex3f(10.,300.,0.);
	glTexCoord2f(3.,10.); glVertex3f(0.,300.,-10.);
	glTexCoord2f(3.,0.); glVertex3f(0.,260.,-10.);
	// Pass supérieur sup : gauche
	glTexCoord2f(0.,10.); glVertex3f(0.,260.,-10.);
	glTexCoord2f(0.,0.); glVertex3f(0.,300.,-10.);
	glTexCoord2f(3.,0.); glVertex3f(-10.,300.,0.);
	glTexCoord2f(3.,10.); glVertex3f(-10.,260.,0.);
	// Pass supérieur sup : droite
	glTexCoord2f(0.,10.); glVertex3f(-10.,260.,0.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,300.,0.);
	glTexCoord2f(3.,0.); glVertex3f(0.,300.,10.);
	glTexCoord2f(3.,10.); glVertex3f(0.,260.,10.);
	// Pass supérieur sup : haut
	glTexCoord2f(0.,0.); glVertex3f(-50.,260.,-40.);
	glTexCoord2f(0.,10.); glVertex3f(-10.,260.,0.);
	glTexCoord2f(3.,10.); glVertex3f(0.,260.,-10.);
	glTexCoord2f(3.,0.); glVertex3f(-40.,260.,-50.);
	// Pass supérieur 1 : bas
	glTexCoord2f(0.,0.); glVertex3f(-50.,250.,-40.);
	glTexCoord2f(0.,10.); glVertex3f(-10.,250.,0.);
	glTexCoord2f(3.,10.); glVertex3f(0.,250.,-10.);
	glTexCoord2f(3.,0.); glVertex3f(-40.,250.,-50.);
	// Pass supérieur 1 : gauche
	glTexCoord2f(0.,10.); glVertex3f(-50.,250.,-40.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,250.,0.);
	glTexCoord2f(3.,0.); glVertex3f(-10.,260.,0.);
	glTexCoord2f(3.,10.); glVertex3f(-50.,260.,-40.);
	// Pass supérieur 1 : droite
	glTexCoord2f(0.,10.); glVertex3f(-40.,250.,-50.);
	glTexCoord2f(0.,0.); glVertex3f(0.,250.,-10.);
	glTexCoord2f(3.,0.); glVertex3f(0.,260.,-10.);
	glTexCoord2f(3.,10.); glVertex3f(-40.,260.,-50.);
	// Pass supérieur 2 : haut
	glTexCoord2f(0.,0.); glVertex3f(50.,260.,-40.);
	glTexCoord2f(0.,10.); glVertex3f(10.,260.,0.);
	glTexCoord2f(3.,10.); glVertex3f(0.,260.,-10.);
	glTexCoord2f(3.,0.); glVertex3f(40.,260.,-50.);
	// Pass supérieur 2 : bas
	glTexCoord2f(0.,0.); glVertex3f(50.,250.,-40.);
	glTexCoord2f(0.,10.); glVertex3f(10.,250.,0.);
	glTexCoord2f(3.,10.); glVertex3f(0.,250.,-10.);
	glTexCoord2f(3.,0.); glVertex3f(40.,250.,-50.);
	// Pass supérieur 2 : gauche
	glTexCoord2f(0.,10.); glVertex3f(50.,250.,-40.);
	glTexCoord2f(0.,0.); glVertex3f(10.,250.,0.);
	glTexCoord2f(3.,0.); glVertex3f(10.,260.,0.);
	glTexCoord2f(3.,10.); glVertex3f(50.,260.,-40.);
	// Pass supérieur 2 : droite
	glTexCoord2f(0.,10.); glVertex3f(40.,250.,-50.);
	glTexCoord2f(0.,0.); glVertex3f(0.,250.,-10.);
	glTexCoord2f(3.,0.); glVertex3f(0.,260.,-10.);
	glTexCoord2f(3.,10.); glVertex3f(40.,260.,-50.);
	// Pass supérieur 3 : haut
	glTexCoord2f(0.,0.); glVertex3f(-50.,260.,40.);
	glTexCoord2f(0.,10.); glVertex3f(-10.,260.,0.);
	glTexCoord2f(3.,10.); glVertex3f(0.,260.,10.);
	glTexCoord2f(3.,0.); glVertex3f(-40.,260.,50.);
	// Pass supérieur 3 : bas
	glTexCoord2f(0.,0.); glVertex3f(-50.,250.,40.);
	glTexCoord2f(0.,10.); glVertex3f(-10.,250.,0.);
	glTexCoord2f(3.,10.); glVertex3f(0.,250.,10.);
	glTexCoord2f(3.,0.); glVertex3f(-40.,250.,50.);
	// Pass supérieur 3 : gauche
	glTexCoord2f(0.,10.); glVertex3f(-50.,250.,40.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,250.,0.);
	glTexCoord2f(3.,0.); glVertex3f(-10.,260.,0.);
	glTexCoord2f(3.,10.); glVertex3f(-50.,260.,40.);
	// Pass supérieur 3 : droite
	glTexCoord2f(0.,10.); glVertex3f(-40.,250.,50.);
	glTexCoord2f(0.,0.); glVertex3f(0.,250.,10.);
	glTexCoord2f(3.,0.); glVertex3f(0.,260.,10.);
	glTexCoord2f(3.,10.); glVertex3f(-40.,260.,50.);
	// Pass supérieur 4 : haut
	glTexCoord2f(0.,0.); glVertex3f(50.,260.,40.);
	glTexCoord2f(0.,10.); glVertex3f(10.,260.,0.);
	glTexCoord2f(3.,10.); glVertex3f(0.,260.,10.);
	glTexCoord2f(3.,0.); glVertex3f(40.,260.,50.);
	// Pass supérieur 4 : bas
	glTexCoord2f(0.,0.); glVertex3f(50.,250.,40.);
	glTexCoord2f(0.,10.); glVertex3f(10.,250.,0.);
	glTexCoord2f(3.,10.); glVertex3f(0.,250.,10.);
	glTexCoord2f(3.,0.); glVertex3f(40.,250.,50.);
	// Pass supérieur 4 : gauche
	glTexCoord2f(0.,10.); glVertex3f(50.,250.,40.);
	glTexCoord2f(0.,0.); glVertex3f(10.,250.,0.);
	glTexCoord2f(3.,0.); glVertex3f(10.,260.,0.);
	glTexCoord2f(3.,10.); glVertex3f(50.,260.,40.);
	// Pass supérieur 4 : droite
	glTexCoord2f(0.,10.); glVertex3f(40.,250.,50.);
	glTexCoord2f(0.,0.); glVertex3f(0.,250.,10.);
	glTexCoord2f(3.,0.); glVertex3f(0.,260.,10.);
	glTexCoord2f(3.,10.); glVertex3f(40.,260.,50.);

	// Navette arrière centrale : haut
	glTexCoord2f(0.,0.); glVertex3f(-320.,100.,550.);
	glTexCoord2f(0.,40.); glVertex3f(320.,100.,550.);
	glTexCoord2f(5.,40.); glVertex3f(320.,100.,570.);
	glTexCoord2f(5.,0.); glVertex3f(-320.,100.,570.);
	// Navette arrière centrale : bas
	glTexCoord2f(0.,0.); glVertex3f(-320.,80.,545.);
	glTexCoord2f(0.,40.); glVertex3f(320.,80.,545.);
	glTexCoord2f(5.,40.); glVertex3f(320.,80.,575.);
	glTexCoord2f(5.,0.); glVertex3f(-320.,80.,575.);
	// Navette arrière centrale : gauche
	glTexCoord2f(0.,40.); glVertex3f(-320.,80.,575.);
	glTexCoord2f(0.,0.); glVertex3f(320.,80.,575.);
	glTexCoord2f(5.,0.); glVertex3f(320.,100.,570.);
	glTexCoord2f(5.,40.); glVertex3f(-320.,100.,570.);
	// Navette arrière centrale : droite
	glTexCoord2f(0.,40.); glVertex3f(-320.,80.,545.);
	glTexCoord2f(0.,0.); glVertex3f(320.,80.,545.);
	glTexCoord2f(5.,0.); glVertex3f(320.,100.,550.);
	glTexCoord2f(5.,40.); glVertex3f(-320.,100.,550.);
	// Navette arrière gauche : haut
	glTexCoord2f(0.,0.); glVertex3f(-320.,100.,590.);
	glTexCoord2f(0.,40.); glVertex3f(320.,100.,590.);
	glTexCoord2f(5.,40.); glVertex3f(320.,100.,610.);
	glTexCoord2f(5.,0.); glVertex3f(-320.,100.,610.);
	// Navette arrière gauche : bas
	glTexCoord2f(0.,0.); glVertex3f(-320.,80.,585.);
	glTexCoord2f(0.,40.); glVertex3f(320.,80.,585.);
	glTexCoord2f(5.,40.); glVertex3f(320.,80.,615.);
	glTexCoord2f(5.,0.); glVertex3f(-320.,80.,615.);
	// Navette arrière gauche : gauche
	glTexCoord2f(0.,40.); glVertex3f(-320.,80.,585.);
	glTexCoord2f(0.,0.); glVertex3f(320.,80.,585.);
	glTexCoord2f(5.,0.); glVertex3f(320.,100.,590.);
	glTexCoord2f(5.,40.); glVertex3f(-320.,100.,590.);
	// Navette arrière gauche : droite
	glTexCoord2f(0.,40.); glVertex3f(-320.,80.,615.);
	glTexCoord2f(0.,0.); glVertex3f(320.,80.,615.);
	glTexCoord2f(5.,0.); glVertex3f(320.,100.,610.);
	glTexCoord2f(5.,40.); glVertex3f(-320.,100.,610.);
	// Navette arrière droite : haut
	glTexCoord2f(0.,0.); glVertex3f(-320.,100.,510.);
	glTexCoord2f(0.,40.); glVertex3f(320.,100.,510.);
	glTexCoord2f(5.,40.); glVertex3f(320.,100.,530.);
	glTexCoord2f(5.,0.); glVertex3f(-320.,100.,530.);
	// Navette arrière droite : bas
	glTexCoord2f(0.,0.); glVertex3f(-320.,80.,505.);
	glTexCoord2f(0.,40.); glVertex3f(320.,80.,505.);
	glTexCoord2f(5.,40.); glVertex3f(320.,80.,535.);
	glTexCoord2f(5.,0.); glVertex3f(-320.,80.,535.);
	// Navette arrière droite : gauche
	glTexCoord2f(0.,40.); glVertex3f(-320.,80.,505.);
	glTexCoord2f(0.,0.); glVertex3f(320.,80.,505.);
	glTexCoord2f(5.,0.); glVertex3f(320.,100.,510.);
	glTexCoord2f(5.,40.); glVertex3f(-320.,100.,510.);
	// Navette arrière droite : droite
	glTexCoord2f(0.,40.); glVertex3f(-320.,80.,535.);
	glTexCoord2f(0.,0.); glVertex3f(320.,80.,535.);
	glTexCoord2f(5.,0.); glVertex3f(320.,100.,530.);
	glTexCoord2f(5.,40.); glVertex3f(-320.,100.,530.);
	// Navette gauche : haut
	glTexCoord2f(0.,5.); glVertex3f(-120.,-25.,-360.);
	glTexCoord2f(0.,0.); glVertex3f(-140.,-25.,-360.);
	glTexCoord2f(20.,0.); glVertex3f(-140.,40.,-140.);
	glTexCoord2f(20.,5.); glVertex3f(-120.,40.,-140.);
	// Navette gauche : bas
	glTexCoord2f(0.,5.); glVertex3f(-120.,-40.,-360.);
	glTexCoord2f(0.,0.); glVertex3f(-140.,-40.,-360.);
	glTexCoord2f(20.,0.); glVertex3f(-140.,25.,-140.);
	glTexCoord2f(20.,5.); glVertex3f(-120.,25.,-140.);
	// Navette gauche : gauche
	glTexCoord2f(0.,20.); glVertex3f(-120.,25.,-140.);
	glTexCoord2f(0.,0.); glVertex3f(-120.,-40.,-360.);
	glTexCoord2f(5.,0.); glVertex3f(-120.,-25.,-360.);
	glTexCoord2f(5.,20.); glVertex3f(-120.,40.,-140.);
	// Navette gauche : droite
	glTexCoord2f(0.,20.); glVertex3f(-140.,25.,-140.);
	glTexCoord2f(0.,0.); glVertex3f(-140.,-40.,-360.);
	glTexCoord2f(5.,0.); glVertex3f(-140.,-25.,-360.);
	glTexCoord2f(5.,20.); glVertex3f(-140.,40.,-140.);
	// Navette droite : haut
	glTexCoord2f(0.,5.); glVertex3f(120.,135.,-360.);
	glTexCoord2f(0.,0.); glVertex3f(140.,135.,-360.);
	glTexCoord2f(20.,0.); glVertex3f(140.,40.,-140.);
	glTexCoord2f(20.,5.); glVertex3f(120.,40.,-140.);
	// Navette droite : bas
	glTexCoord2f(0.,5.); glVertex3f(120.,120.,-360.);
	glTexCoord2f(0.,0.); glVertex3f(140.,120.,-360.);
	glTexCoord2f(20.,0.); glVertex3f(140.,25.,-140.);
	glTexCoord2f(20.,5.); glVertex3f(120.,25.,-140.);
	// Navette droite : gauche
	glTexCoord2f(0.,20.); glVertex3f(120.,25.,-140.);
	glTexCoord2f(0.,0.); glVertex3f(120.,120.,-360.);
	glTexCoord2f(5.,0.); glVertex3f(120.,135.,-360.);
	glTexCoord2f(5.,20.); glVertex3f(120.,40.,-140.);
	// Navette droite : droite
	glTexCoord2f(0.,20.); glVertex3f(140.,25.,-140.);
	glTexCoord2f(0.,0.); glVertex3f(140.,120.,-360.);
	glTexCoord2f(5.,0.); glVertex3f(140.,135.,-360.);
	glTexCoord2f(5.,20.); glVertex3f(140.,40.,-140.);
	// Navette centrale gauche : haut
	glTexCoord2f(0.,0.); glVertex3f(-320.,95.,140.);
	glTexCoord2f(0.,20.); glVertex3f(-160.,0.,140.);
	glTexCoord2f(4.,20.); glVertex3f(-160.,0.,160.);
	glTexCoord2f(4.,0.); glVertex3f(-320.,95.,160.);
	// Navette centrale gauche : bas
	glTexCoord2f(0.,0.); glVertex3f(-320.,80.,140.);
	glTexCoord2f(0.,20.); glVertex3f(-160.,-15.,140.);
	glTexCoord2f(4.,20.); glVertex3f(-160.,-15.,160.);
	glTexCoord2f(4.,0.); glVertex3f(-320.,80.,160.);
	// Navette centrale gauche : gauche
	glTexCoord2f(0.,20.); glVertex3f(-320.,95.,160.);
	glTexCoord2f(0.,0.); glVertex3f(-160.,0.,160.);
	glTexCoord2f(4.,0.); glVertex3f(-160.,-15.,160.);
	glTexCoord2f(4.,20.); glVertex3f(-320.,80.,160.);
	// Navette centrale gauche : droite
	glTexCoord2f(0.,20.); glVertex3f(-320.,95.,140.);
	glTexCoord2f(0.,0.); glVertex3f(-160.,0.,140.);
	glTexCoord2f(4.,0.); glVertex3f(-160.,-15.,140.);
	glTexCoord2f(4.,20.); glVertex3f(-320.,80.,140.);
	// Navette centrale droite : haut
	glTexCoord2f(0.,0.); glVertex3f(320.,95.,140.);
	glTexCoord2f(0.,20.); glVertex3f(160.,0.,140.);
	glTexCoord2f(4.,20.); glVertex3f(160.,0.,160.);
	glTexCoord2f(4.,0.); glVertex3f(320.,95.,160.);
	// Navette centrale droite : bas
	glTexCoord2f(0.,0.); glVertex3f(320.,80.,140.);
	glTexCoord2f(0.,20.); glVertex3f(160.,-15.,140.);
	glTexCoord2f(4.,20.); glVertex3f(160.,-15.,160.);
	glTexCoord2f(4.,0.); glVertex3f(320.,80.,160.);
	// Navette centrale droite : gauche
	glTexCoord2f(0.,20.); glVertex3f(320.,95.,160.);
	glTexCoord2f(0.,0.); glVertex3f(160.,0.,160.);
	glTexCoord2f(4.,0.); glVertex3f(160.,-15.,160.);
	glTexCoord2f(4.,20.); glVertex3f(320.,80.,160.);
	// Navette centrale droite : droite
	glTexCoord2f(0.,20.); glVertex3f(320.,95.,140.);
	glTexCoord2f(0.,0.); glVertex3f(160.,0.,140.);
	glTexCoord2f(4.,0.); glVertex3f(160.,-15.,140.);
	glTexCoord2f(4.,20.); glVertex3f(320.,80.,140.);

	// Tunnel principal : haut
	glTexCoord2f(0.,30.); glVertex3f(-10.,-105.,-455.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-200.,142.);
	glTexCoord2f(5.,0.); glVertex3f(10.,-200.,142.);
	glTexCoord2f(5.,30.); glVertex3f(10.,-105.,-455.);
	// Tunnel principal : bas
	glTexCoord2f(0.,30.); glVertex3f(-10.,-120.,-455.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-215.,157.);
	glTexCoord2f(5.,0.); glVertex3f(10.,-215.,157.);
	glTexCoord2f(5.,30.); glVertex3f(10.,-120.,-455.);
	// Tunnel principal : gauche avant
	glTexCoord2f(0.,20.); glVertex3f(-10.,-105.,-455.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-169.,-50.);
	glTexCoord2f(5.,0.); glVertex3f(-10.,-183.5,-50.);
	glTexCoord2f(5.,20.); glVertex3f(-10.,-120.,-455.);
	// Tunnel principal : droite avant
	glTexCoord2f(0.,20.); glVertex3f(10.,-105.,-455.);
	glTexCoord2f(0.,0.); glVertex3f(10.,-169.,-50.);
	glTexCoord2f(5.,0.); glVertex3f(10.,-183.5,-50.);
	glTexCoord2f(5.,20.); glVertex3f(10.,-120.,-455.);
	// Tunnel principal : gauche arrière
	glTexCoord2f(0.,10.); glVertex3f(-10.,-171.3,-35.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-200.,142.);
	glTexCoord2f(5.,0.); glVertex3f(-10.,-215.,157.);
	glTexCoord2f(5.,10.); glVertex3f(-10.,-185.5,-35.);
	// Tunnel principal : droite arrière
	glTexCoord2f(0.,10.); glVertex3f(10.,-171.3,-35.);
	glTexCoord2f(0.,0.); glVertex3f(10.,-200.,142.);
	glTexCoord2f(5.,0.); glVertex3f(10.,-215.,157.);
	glTexCoord2f(5.,10.); glVertex3f(10.,-185.5,-35.);
	// Sortie du tunnel principal : avant
	glTexCoord2f(0.,10.); glVertex3f(-10.,-200.,142.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-100.,142.);
	glTexCoord2f(5.,0.); glVertex3f(10.,-100.,142.);
	glTexCoord2f(5.,10.); glVertex3f(10.,-200.,142.);
	// Sortie du tunnel principal : arrière
	glTexCoord2f(0.,10.); glVertex3f(-10.,-215.,157.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-100.,157.);
	glTexCoord2f(5.,0.); glVertex3f(10.,-100.,157.);
	glTexCoord2f(5.,10.); glVertex3f(10.,-215.,157.);
	// Sortie du tunnel principal : gauche
	glTexCoord2f(0.,10.); glVertex3f(-10.,-200.,142.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-100.,142.);
	glTexCoord2f(5.,0.); glVertex3f(-10.,-100.,157.);
	glTexCoord2f(5.,10.); glVertex3f(-10.,-215.,157.);
	// Sortie du tunnel principal : droite
	glTexCoord2f(0.,10.); glVertex3f(10.,-200.,142.);
	glTexCoord2f(0.,0.); glVertex3f(10.,-100.,142.);
	glTexCoord2f(5.,0.); glVertex3f(10.,-100.,157.);
	glTexCoord2f(5.,10.); glVertex3f(10.,-215.,157.);
	// Sortie gauche du tunnel principal : avant
	glTexCoord2f(0.,5.); glVertex3f(-10.,-169.,-50.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-183.5,-50.);
	glTexCoord2f(10.,0.); glVertex3f(-90.,-120.,-10.);
	glTexCoord2f(10.,5.); glVertex3f(-70.,-120.,-10.);
	// Sortie gauche du tunnel principal : arrière
	glTexCoord2f(0.,5.); glVertex3f(-10.,-171.3,-35.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-185.5,-35.);
	glTexCoord2f(10.,0.); glVertex3f(-90.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(-70.,-120.,5.);
	// Sortie gauche du tunnel principal : gauche
	glTexCoord2f(0.,5.); glVertex3f(-10.,-169.5,-50.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-171.8,-35.);
	glTexCoord2f(10.,0.); glVertex3f(-70.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(-70.,-120.,-10.);
	// Sortie gauche du tunnel principal : gauche
	glTexCoord2f(0.,5.); glVertex3f(-10.,-182.9,-50.);
	glTexCoord2f(0.,0.); glVertex3f(-10.,-185.2,-35.);
	glTexCoord2f(10.,0.); glVertex3f(-90.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(-90.,-120.,-10.);
	// Sortie droite du tunnel principal : avant
	glTexCoord2f(0.,5.); glVertex3f(10.,-169.,-50.);
	glTexCoord2f(0.,0.); glVertex3f(10.,-183.5,-50.);
	glTexCoord2f(10.,0.); glVertex3f(90.,-120.,-10.);
	glTexCoord2f(10.,5.); glVertex3f(70.,-120.,-10.);
	// Sortie droite du tunnel principal : arrière
	glTexCoord2f(0.,5.); glVertex3f(10.,-171.3,-35.);
	glTexCoord2f(0.,0.); glVertex3f(10.,-185.5,-35.);
	glTexCoord2f(10.,0.); glVertex3f(90.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(70.,-120.,5.);
	// Sortie droite du tunnel principal : gauche
	glTexCoord2f(0.,5.); glVertex3f(10.,-169.5,-50.);
	glTexCoord2f(0.,0.); glVertex3f(10.,-171.8,-35.);
	glTexCoord2f(10.,0.); glVertex3f(70.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(70.,-120.,-10.);
	// Sortie droite du tunnel principal : gauche
	glTexCoord2f(0.,5.); glVertex3f(10.,-182.9,-50.);
	glTexCoord2f(0.,0.); glVertex3f(10.,-185.2,-35.);
	glTexCoord2f(10.,0.); glVertex3f(90.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(90.,-120.,-10.);
	// Tunnel droit bas : avant
	glTexCoord2f(0.,5.); glVertex3f(105.,-40.,30.);
	glTexCoord2f(0.,0.); glVertex3f(125.,-40.,30.);
	glTexCoord2f(10.,0.); glVertex3f(90.,-120.,-10.);
	glTexCoord2f(10.,5.); glVertex3f(70.,-120.,-10.);
	// Tunnel droit bas : arrière
	glTexCoord2f(0.,5.); glVertex3f(105.,-40.,45.);
	glTexCoord2f(0.,0.); glVertex3f(125.,-40.,45.);
	glTexCoord2f(10.,0.); glVertex3f(90.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(70.,-120.,5.);
	// Tunnel droit bas : gauche
	glTexCoord2f(0.,5.); glVertex3f(105.,-40.,30.);
	glTexCoord2f(0.,0.); glVertex3f(105.,-40.,45.);
	glTexCoord2f(10.,0.); glVertex3f(70.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(70.,-120.,-10.);
	// Tunnel droit bas : gauche
	glTexCoord2f(0.,5.); glVertex3f(125.,-40.,30.);
	glTexCoord2f(0.,0.); glVertex3f(125.,-40.,45.);
	glTexCoord2f(10.,0.); glVertex3f(90.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(90.,-120.,-10.);
	// Tunnel droit haut avant : avant
	glTexCoord2f(0.,5.); glVertex3f(105.,-40.,30.);
	glTexCoord2f(0.,0.); glVertex3f(125.,-40.,30.);
	glTexCoord2f(10.,0.); glVertex3f(130.,0.,0.);
	glTexCoord2f(10.,5.); glVertex3f(110.,0.,0.);
	// Tunnel droit haut avant : arrière
	glTexCoord2f(0.,5.); glVertex3f(105.,-40.,45.);
	glTexCoord2f(0.,0.); glVertex3f(125.,-40.,45.);
	glTexCoord2f(10.,0.); glVertex3f(130.,15.,15.);
	glTexCoord2f(10.,5.); glVertex3f(110.,15.,15.);
	// Tunnel droit haut avant : gauche
	glTexCoord2f(0.,5.); glVertex3f(105.,-40.,30.);
	glTexCoord2f(0.,0.); glVertex3f(105.,-40.,45.);
	glTexCoord2f(10.,0.); glVertex3f(110.,15.,15.);
	glTexCoord2f(10.,5.); glVertex3f(110.,0.,0.);
	// Tunnel droit haut avant : gauche
	glTexCoord2f(0.,5.); glVertex3f(125.,-40.,30.);
	glTexCoord2f(0.,0.); glVertex3f(125.,-40.,45.);
	glTexCoord2f(10.,0.); glVertex3f(130.,15.,15.);
	glTexCoord2f(10.,5.); glVertex3f(130.,0.,0.);
	// Tunnel droit haut extrem. avant : avant
	glTexCoord2f(0.,5.); glVertex3f(120.,25.,-80.);
	glTexCoord2f(0.,0.); glVertex3f(140.,25.,-80.);
	glTexCoord2f(10.,0.); glVertex3f(130.,0.,0.);
	glTexCoord2f(10.,5.); glVertex3f(110.,0.,0.);
	// Tunnel droit haut extrem. avant : arrière
	glTexCoord2f(0.,5.); glVertex3f(120.,40.,-80.);
	glTexCoord2f(0.,0.); glVertex3f(140.,40.,-80.);
	glTexCoord2f(10.,0.); glVertex3f(130.,15.,15.);
	glTexCoord2f(10.,5.); glVertex3f(110.,15.,15.);
	// Tunnel droit haut extrem. avant : gauche
	glTexCoord2f(0.,5.); glVertex3f(120.,25.,-80.);
	glTexCoord2f(0.,0.); glVertex3f(120.,40.,-80.);
	glTexCoord2f(10.,0.); glVertex3f(110.,15.,15.);
	glTexCoord2f(10.,5.); glVertex3f(110.,0.,0.);
	// Tunnel droit haut extrem. avant : gauche
	glTexCoord2f(0.,5.); glVertex3f(140.,25.,-80.);
	glTexCoord2f(0.,0.); glVertex3f(140.,40.,-80.);
	glTexCoord2f(10.,0.); glVertex3f(130.,15.,15.);
	glTexCoord2f(10.,5.); glVertex3f(130.,0.,0.);
	// Tunnel gauche bas : avant
	glTexCoord2f(0.,5.); glVertex3f(-105.,-50.,25.);
	glTexCoord2f(0.,0.); glVertex3f(-125.,-50.,25.);
	glTexCoord2f(10.,0.); glVertex3f(-90.,-120.,-10.);
	glTexCoord2f(10.,5.); glVertex3f(-70.,-120.,-10.);
	// Tunnel gauche bas : arrière
	glTexCoord2f(0.,5.); glVertex3f(-105.,-50.,60.);
	glTexCoord2f(0.,0.); glVertex3f(-125.,-50.,60.);
	glTexCoord2f(10.,0.); glVertex3f(-90.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(-70.,-120.,5.);
	// Tunnel gauche bas : gauche
	glTexCoord2f(0.,5.); glVertex3f(-105.,-50.,25.);
	glTexCoord2f(0.,0.); glVertex3f(-105.,-50.,60.);
	glTexCoord2f(10.,0.); glVertex3f(-70.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(-70.,-120.,-10.);
	// Tunnel gauche bas : gauche
	glTexCoord2f(0.,5.); glVertex3f(-125.,-50.,25.);
	glTexCoord2f(0.,0.); glVertex3f(-125.,-50.,60.);
	glTexCoord2f(10.,0.); glVertex3f(-90.,-120.,5.);
	glTexCoord2f(10.,5.); glVertex3f(-90.,-120.,-10.);
	// Tunnel gauche haut : avant
	glTexCoord2f(0.,5.); glVertex3f(-105.,-50.,25.);
	glTexCoord2f(0.,0.); glVertex3f(-125.,-50.,25.);
	glTexCoord2f(10.,0.); glVertex3f(-140.,25.,-80.);
	glTexCoord2f(10.,5.); glVertex3f(-120.,25.,-80.);
	// Tunnel gauche haut : arrière
	glTexCoord2f(0.,5.); glVertex3f(-105.,-50.,60.);
	glTexCoord2f(0.,0.); glVertex3f(-125.,-50.,60.);
	glTexCoord2f(10.,0.); glVertex3f(-140.,40.,-80.);
	glTexCoord2f(10.,5.); glVertex3f(-120.,40.,-80.);
	// Tunnel gauche haut : gauche
	glTexCoord2f(0.,5.); glVertex3f(-105.,-50.,25.);
	glTexCoord2f(0.,0.); glVertex3f(-105.,-50.,60.);
	glTexCoord2f(10.,0.); glVertex3f(-120.,40.,-80.);
	glTexCoord2f(10.,5.); glVertex3f(-120.,25.,-80.);
	// Tunnel gauche haut : gauche
	glTexCoord2f(0.,5.); glVertex3f(-125.,-50.,25.);
	glTexCoord2f(0.,0.); glVertex3f(-125.,-50.,60.);
	glTexCoord2f(10.,0.); glVertex3f(-140.,40.,-80.);
	glTexCoord2f(10.,5.); glVertex3f(-140.,25.,-80.);
	// Tunnel mural arrière : avant
	glTexCoord2f(0.,5.); glVertex3f(-20.,15.,55.);
	glTexCoord2f(0.,0.); glVertex3f(-20.,0.,55.);
	glTexCoord2f(5.,0.); glVertex3f(20.,0.,55.);
	glTexCoord2f(5.,5.); glVertex3f(20.,15.,55.);
	// Tunnel mural arrière : arrière
	glTexCoord2f(0.,5.); glVertex3f(-20.,15.,75.);
	glTexCoord2f(0.,0.); glVertex3f(-20.,0.,75.);
	glTexCoord2f(5.,0.); glVertex3f(20.,0.,75.);
	glTexCoord2f(5.,5.); glVertex3f(20.,15.,75.);
	// Tunnel mural arrière : haut
	glTexCoord2f(0.,5.); glVertex3f(-20.,15.,55.);
	glTexCoord2f(0.,0.); glVertex3f(-20.,15.,75.);
	glTexCoord2f(5.,0.); glVertex3f(20.,15.,75.);
	glTexCoord2f(5.,5.); glVertex3f(20.,15.,55.);
	// Tunnel mural arrière : bas
	glTexCoord2f(0.,5.); glVertex3f(-20.,0.,55.);
	glTexCoord2f(0.,0.); glVertex3f(-20.,0.,75.);
	glTexCoord2f(5.,0.); glVertex3f(20.,0.,75.);
	glTexCoord2f(5.,5.); glVertex3f(20.,0.,55.);
	// Tunnel mural avant : gauche
	glTexCoord2f(0.,5.); glVertex3f(25.,15.,40.);
	glTexCoord2f(0.,0.); glVertex3f(25.,0.,40.);
	glTexCoord2f(7.,0.); glVertex3f(25.,0.,-40.);
	glTexCoord2f(7.,5.); glVertex3f(25.,15.,-40.);
	// Tunnel mural avant : droite
	glTexCoord2f(0.,5.); glVertex3f(45.,15.,40.);
	glTexCoord2f(0.,0.); glVertex3f(45.,0.,40.);
	glTexCoord2f(7.,0.); glVertex3f(45.,0.,-40.);
	glTexCoord2f(7.,5.); glVertex3f(45.,15.,-40.);
	// Tunnel mural avant : haut
	glTexCoord2f(0.,7.); glVertex3f(25.,15.,40.);
	glTexCoord2f(0.,0.); glVertex3f(25.,15.,-40.);
	glTexCoord2f(5.,0.); glVertex3f(45.,15.,-40.);
	glTexCoord2f(5.,7.); glVertex3f(45.,15.,40.);
	// Tunnel mural avant : bas
	glTexCoord2f(0.,7.); glVertex3f(25.,0.,40.);
	glTexCoord2f(0.,0.); glVertex3f(25.,0.,-40.);
	glTexCoord2f(5.,0.); glVertex3f(45.,0.,-40.);
	glTexCoord2f(5.,7.); glVertex3f(45.,0.,40.);

	glEnd();
	glEndList();

	return;
}
