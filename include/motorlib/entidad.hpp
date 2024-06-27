#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "obj3dlib.hpp"
#include "comportamientolib.hpp"
#include "motorlib/util.h"

// Macro clase para englobar entidades de juego
// Contiene la informacion para pintar y ejecutar en el juego las entidades
// Las entidades son el jugador y los npcs

enum Tipo
{
  jugador,
  npc
};
enum SubTipo
{
  jugador_,
  colaborador,
  aldeano,
  lobo,
  __NONE__
};

class Entidad
{
private:
  Tipo tipo;
  SubTipo subtipo;
  Orientacion orient;
  unsigned int f, c;
  unsigned int num_destinos;
  vector<unsigned int> destino;
  vector<bool> alcanzados;
  bool completoLosObjetivos;

  Objeto3D *modelo;
  Comportamiento *comportamiento;

  // Colision
  bool colision = false;
  int colisiones = 0;
  int empujones = 0;

  // reset
  bool reset = false;

  // notificar coordenadas del agente
  bool mensaje = false;

  // notificar coordenadas del colaborador
  bool mensaje2 = false;


  // vida
  int vida = 3000;
  int muertes_innecesarias = 0;

  // bateria
  int bateria = 3000;

  bool hitbox = true;
  int desactivado = 0;

  Action last_action = actIDLE;
  int misiones = 0;
  int puntuacion = 0;
  bool done = false;
  double tiempo = 0;
  double tiempoMaximo = 300 * CLOCKS_PER_SEC;
  int tiempo_sig_accion = 0;
  int bateria_sig_accion = 0;
  int bateria_sig_accion_clb = 0;
  int nivel = 1;

  bool tiene_zapatillas = false;
  bool tiene_bikini = false;

  Entidad* EntidadColaborador;


  vector<vector<unsigned char>> visionAux;

  Action ActionSent;

  // Indica si llego a la casilla objetivo
  bool llegoObjetivo;

public:
  Entidad(Tipo paramTipo, SubTipo paramSubTipo, Orientacion paramOrient, unsigned int paramF, unsigned int paramC, Objeto3D *mod, Comportamiento *comp, int numberdest, vector<unsigned int> CasillasObjetivo, int v)
  {
    tipo = paramTipo;
    subtipo = paramSubTipo;
    orient = paramOrient;
    f = paramF;
    c = paramC;
    modelo = mod;
    comportamiento = comp;
    num_destinos = numberdest;
    destino = CasillasObjetivo;
    for (int i = 0; i < num_destinos; i++)
      alcanzados.push_back(false);
    vida = v;
    completoLosObjetivos = false;
    ActionSent = act_CLB_STOP;
    llegoObjetivo = false;
  }

  ~Entidad()
  {
    delete modelo;
    delete comportamiento;
  }

  void draw(int modo)
  {
    if (hitbox)
    {
      modelo->draw(modo);
    }
  }

//  Action think(int acc, vector<vector<unsigned char>> vision, int level);

  Action think(int acc, vector <vector< unsigned char> > vision, int level);


  // Programar funciones para la interacción con el entorno
  void setPosicion(unsigned int paramF, unsigned int paramC)
  {
    f = paramF;
    c = paramC;
  }
  // void setObjetivo(unsigned int paramF, unsigned int paramC) {destF = paramF; destC = paramC;}
  void setOrientacion(Orientacion paramOrient) { orient = paramOrient; }
  void giro45Dch(){orient = static_cast<Orientacion> ((orient+1)%8);}
  void giroDch(){orient = static_cast<Orientacion> ((orient+2)%8);}
  void giro45Izq(){orient = static_cast<Orientacion> ((orient+7)%8);}
  void giroIzq(){orient = static_cast<Orientacion> ((orient+6)%8);}

  int isMemberObjetivo(unsigned int paramF, unsigned int paramC);
  bool allObjetivosAlcanzados();
  bool allLessOneObjetivosAlcanzados();
  void setObjetivos(vector<unsigned int> v);
  void actualizarAlcanzados();
  void anularAlcanzados();
  unsigned int getNumObj() { return num_destinos; }
  unsigned int getObjFil(int pos);
  unsigned int getObjCol(int pos);

  Tipo getTipo() { return tipo; }
  SubTipo getSubTipo() { return subtipo; }

  unsigned char getSubTipoChar();

  Orientacion getOrientacion() { return orient; }
  unsigned int getFil() { return f; }
  unsigned int getCol() { return c; }
  bool getHitbox() { return hitbox; }

  bool interact(Action accion, int valor);

  void resetEntidad();
  void resetSignal(){reset = true;}
  void seAostio()
  {
    colision = true;
    colisiones++;
  }
  void notify() { mensaje = true; }
  bool hasToNotify() { return mensaje; }
  void setNotifyOff() { mensaje = false; }



  void setCompletoLosObjetivos() { completoLosObjetivos = true; }
  bool SeHanConseguidoLosObjetivos() { return completoLosObjetivos; }

  void setLastAction(Action accion) {last_action = accion; }
  Action getLastAction() {return last_action; }

  vector<vector<unsigned char>> getMapaResultado() { return comportamiento->getMapaResultado(); }
  vector<vector<unsigned char>> getMapaEntidades() { return comportamiento->getMapaEntidades(); }
  vector<vector<unsigned char>> getMapaPlan() { return comportamiento->getMapaPlan(); }

  bool vivo() { return vida > 0; }

  string toString();

  void setVision(vector<vector<unsigned char>> vision) { visionAux = vision; }
  vector<vector<unsigned char>> getVision(){return visionAux;}

  void perderPV(int valor) { vida -= valor; }
  void ganarPV(int valor) { vida += valor; }
  int getInstantesPendientes() { return vida; }

  int getColisiones() { return colisiones; }
  int getMuertesI() { return muertes_innecesarias; }

  void Increment_Empujones() {empujones++;}
  int getEmpujones() {return empujones;}

  void setTiempo(double valor) { tiempo = valor; }
  double getTiempo() { return tiempo; }
  double getTiempoMaximo() { return tiempoMaximo; }
  void addTiempo(double valor) { tiempo += valor; }

  void setMisiones(int value) {misiones = value;}
  int getMisiones() { return misiones; }
  void incrMisiones() {misiones++;}
  
  void setPuntuacion(int value) {puntuacion = value;}
  int getPuntuacion() { return puntuacion;}
  void incrPuntuacion(int value) {puntuacion += value;}

  bool isActived() { return desactivado != -1; }
  void Active() { desactivado = 0; }

  void setMensajeOff() { mensaje = false; }
  void setColisionOff() { colision = false; }
  void setResetOff() { reset = false; }
  void setHitbox(bool valor) { hitbox = valor; }

  bool fin() { return done; }
  void resetFin() { done = false; }

  bool ready() { return tiempo_sig_accion == 0 and bateria > 0; }
  void decTiempo_sig_accion()
  {
    if (tiempo_sig_accion > 0)
      tiempo_sig_accion--;
  }
  void fixTiempo_sig_accion(unsigned char celda);
  int getTsig_accion() { return tiempo_sig_accion; }

  int getBateria() const { return bateria; }
  void setBateria(int valor) { bateria = valor; }
  void fixBateria_default() { bateria_sig_accion = 0; }
  int fixBateria_sig_accion_jugador(unsigned char celdaJugador, Action accion);
  int fixBateria_sig_accion_colaborador(unsigned char celdaColaborador, Action accion);

  void decBateria_sig_accion();
  int getBsig_accion() { return bateria_sig_accion; }
  void increaseBateria(int valor)
  {
    bateria += valor;
    if (bateria > 3000)
      bateria = 3000;
  }

  bool Has_Zapatillas() { return tiene_zapatillas; }
  bool Has_Bikini() { return tiene_bikini; }
  void Cogio_Zapatillas(bool valor) { tiene_zapatillas = valor; }
  void Cogio_Bikini(bool valor) { tiene_bikini = valor; }
  void SetActionSent(Action ac){ActionSent = ac;}
  Action GetActionSent(){return ActionSent;}

  void set_Nivel(int level) { nivel = level; }
  int get_Nivel() { return nivel; }

  void SetColaborador (Entidad *x) {EntidadColaborador = x;}

  void SetLlegoOff(){llegoObjetivo = false;}
  void SetLlegoOn(){llegoObjetivo = true;}
  bool GetLlego(){return llegoObjetivo;}
};
#endif
