/************************************************************
********************** STUDIO AMANGA ************************
******************** S-W 3 : PHOENIXIA **********************
*************************************************************
**                                                         **
******** serie.cpp **** auteur : Vincent Tourraine **********
**                                                         **
** Structures, classes et fonctions liées aux entitées     **
** drones et à leur Intelligence Artificielle              **
**                                                         **
*************************************************************/



// Ensemble de drones
class cl_Serie
{
private :
  // Skin
  cl_model * model;
public :
  float yOsc, rayon;
  int effet;
  // Liste des shokers ( element 1 )
  cl_drone * Drones;
  // Liste des shokers ( dernier element )
  cl_drone * LastDrone;
  // Nombre de drone
  short nbDrones;
  // Model (skin) : texture + 2 matériaux
  GLuint text_shoker;
  int id_shokerPIQ, id_shokerCOR;


  // Detruire un drone
  void Delete(int id);
  // Affiche tous les shokers
  void afficher(void);
  // Constructeur
  cl_Serie(char Type, short nb, swVertex positions[]);
  // Destructeur
  ~cl_Serie();

  friend class cl_shoker;
};

cl_Serie* Crystals;
cl_Serie* Shokers;

