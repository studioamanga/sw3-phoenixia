/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* main.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Contient la fonction main qui s'occupe de d�marrer le   **
** programme, d'initialiser OpenGL et toutes les variables **
** n�cessaires, avant d'entrer dans la boucle principale   **
** de jeu.                                                 **
**                                                         **
*************************************************************/

#include "sources/headers.hpp"



int main(int argc, char**argv)
{
	// Initialisation d'OpenGL et cr�ation de la fen�tre
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(320,240);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Phoenixia");
	// Initialisation des variables
	Init();

	// Activation de la gestion du clavier
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	// Activation de la fonction de rendu
	glutDisplayFunc(Display);
	// Activation des fonctions de remise � jour
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);

	// Entr�e dans la boucle principale
	glutMainLoop();

	// Destruction des objets dynamiques
	delete fly;
	// Sortie du programme
	return 0;
}
