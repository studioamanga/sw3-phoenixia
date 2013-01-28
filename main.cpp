/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
********* main.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Contient la fonction main qui s'occupe de démarrer le   **
** programme, d'initialiser OpenGL et toutes les variables **
** nécessaires, avant d'entrer dans la boucle principale   **
** de jeu.                                                 **
**                                                         **
*************************************************************/

#include "sources/headers.hpp"



int main(int argc, char**argv)
{
	// Initialisation d'OpenGL et création de la fenêtre
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
	// Activation des fonctions de remise à jour
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);

	// Entrée dans la boucle principale
	glutMainLoop();

	// Destruction des objets dynamiques
	delete fly;
	// Sortie du programme
	return 0;
}
