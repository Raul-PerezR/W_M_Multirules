#ifndef _PATRONESH_
#define _PATRONESH_

#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include <set>
#include "VectorVar.h"
#include "example_set.h"
#include "vectordouble.h"

using namespace std;

struct TestResult
{
  vector<double> cubiertos;
  vector<double> no_cubiertos;
  vector<double> acc;
  vector<double> error_intrinseco_porClase;
  double acierto_global;
  double acierto_sinNoCubiertos;
  double porcentaje_nuevos_patrones;
  double error_intrinseco;
};


struct info
{
  vector<double> conseq;
  vector<int> eje_list;
  int clase;
  double weight;
};

struct info2
{
  double adaptacion;
  string subCadena;
};

struct infoUp
{
  double key;
  int variable;
  int posCadenainicio;
  vector<info2> trozoAcambiar;
};

struct ProgramParameters
{
  int num_par;           // Partition Number
  bool Nit;              //-NotInferenceTraining
  int LM;                //-LearningModel
  int tm;                //-times
  double th;             //-threshold
  int ld;                //-ld hamming distance for inference 5 or 6
  int sz;                //-size
  int w;                 //-weightRuleModel
  int IM;                //-InferenceModel
  int RSC;               //-RuleSelectionCriteria
  int nLab;              //-nlabel
  int seed;              //-sd
  int d_distance;        //-d
  int maxrules;          //-maxrules
  double percentTestSet; //-PerCentOnTest
  bool NormalizedMu;     //-NormalizedMu
  bool wCP;              //-wCP
  int acc;               //-acc 
  bool allContinuous;    //-allContinuous
  string outputFile;     //-O
};

void ProcesarResultados(TestResult &result, ProgramParameters InputParam);

void PintaResultadosTraining(const TestResult &result);
void PintaResultadosTest(const TestResult &result, bool conClases, ProgramParameters InputParam);
void CalcularMediaTestResult(vector<TestResult> lista, TestResult &result, ProgramParameters InputParam);
void SavePattern(const char *nomfich);



class Pattern
{
private:
  unordered_map<string, info> diccionario;
  //diccionario.max_load_factor(3.0);
  int n_ejemplos;
  int n_clases;

  int BetterEtiqueta(const VectorVar &V, int variable, const example_set &E, int ejemplo);

public:
  Pattern()
  {
    diccionario.max_load_factor(3.0);
    n_ejemplos = 0;
    n_clases = 2;
  }

  Pattern(const VectorVar &V)
  {
    diccionario.max_load_factor(3.0);
    n_ejemplos = 0;
    n_clases = V.SizeDomain(V.Consecuente());
  }

  Pattern(const Pattern &x);
  Pattern &operator=(const Pattern &x);
  void CambiarDiccionario(const unordered_map<string, info> &new_dicionario);


  void PintaPatrones();

  void ExtraerPatronesBasicos(const example_set &Es, const VectorVar &V, TestResult &result, ProgramParameters InputParam);
  void ExtraerPatronesBasicosOriginalWM(const example_set &Es, const VectorVar &V, TestResult &result, ProgramParameters InputParam);
  void ExtraerPatronesBasicosAproximacionTFMRuben_Veces(const example_set &Es, const VectorVar &V, TestResult &result, vector<vector<string>> &RSC, const ProgramParameters &InputParam);
  void ExtraerPatronesBasicosAproximacion_Umbral_w_Normalizado(const example_set &E, const VectorVar &V, TestResult &result, const ProgramParameters &InputParam);
  void ExtraerPatronesBasicosAproximacionTFMRuben_Umbral(const example_set &Es, const VectorVar &V, TestResult &result, const ProgramParameters &InputParam);
  void ExtraerPatronesBasicosAproximacionTFMRuben_DHamming(const example_set &Es, const VectorVar &V, TestResult &result, const ProgramParameters &InputParam);
  void ExtraerPatronesBasicosAproximacionMixed_Umbral_Norm_and_hamming(const example_set &E, const VectorVar &V, TestResult &result, const ProgramParameters &InputParam);

  void CalculandoPeso_TFMRuben_Veces(const example_set &Es, const VectorVar &V, TestResult &result, const ProgramParameters &InputParam);

  void Aprendizaje_RecursivoUnEjemplo_WM_TFM_Ruben_Veces_NoModificaDicionario(const example_set &Es, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, const vector<infoUp> &trozos, int &current_tries, vector<string> &listaDeReglas, int number_tries, int sz, int RSC);  
  void Aprendizaje_RecursivoUnEjemplo_WM_TFM_Ruben_Veces(const example_set &Es, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, const vector<infoUp> &trozos, int &current_tries, vector<string> &listaDeReglas, int number_tries, int sz, int RSC);  
  void Aprendizaje_RecursivoUnEjemplo_WM_TFM_Ruben_Umbral(const example_set &E, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, const vector<infoUp> &trozos, int &considered, double &Threshold, int sz);
  void Aprendizaje_RecursivoUnEjemplo_WM_Umbral_Normalizado(const example_set &Es, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, const vector<infoUp> &trozos, int &considered, double Threshold, int sz);
  void Aprendizaje_RecursivoUnEjemplo_WM_Umbral_Norm_and_Hamming(const example_set &Es, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, const vector<infoUp> &trozos, int &considered, double Threshold, int distance, int Limit_distance, int sz);
  void Aprendizaje_RecursivoUnEjemplo_WM_TFM_Ruben_DistanciaHammning(const example_set &E, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, const vector<infoUp> &trozos, int distance, int Limit_distance, int sz);

  void TestearPatronesBasicos(const example_set &Es, const VectorVar &V, TestResult &result, ProgramParameters InputParam);
  int TestearUnEjemploPatronesBasicos(const example_set &Es, int eje, const VectorVar &V, double &peso);

  int InferenciaRecursivaOptimalizadaConProfundidadLimitada(const example_set &E, const VectorVar &V, const int eje, double &mu, string &antecedenteSeleccionado, bool normalizada, int prof);
  void TestearRecursivoUnEjemploEficenteConProfundidadLimitada(const example_set &E, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, double &umbral, int &clase, const vector<infoUp> &trozos, string &antecedenteSeleccionado, int prof);

  int InferenciaRecursivaOptimalizadaConProfundidadLimitada_SalidaPorProfundidades(const example_set &E, const VectorVar &V, const int eje, double &mu, string &antecedenteSeleccionado, bool normalizada, int prof);
  void TestearRecursivoUnEjemploEficenteConProfundidadLimitada_SalidaPorProfundidades(const example_set &E, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, vector<double> &umbral, vector<int> &clase, const vector<infoUp> &trozos, string &antecedenteSeleccionado,
                                                                                      int prof, vector<pair<string, double>> &estructura);

  int InferenciaRecursivaOptimalizada(const example_set &E, const VectorVar &V, const int eje, double &mu, string &antecedenteSeleccionado, bool normalizada, int TriesNumber);
  void TestearRecursivoUnEjemploEficente(const example_set &E, const VectorVar &V, const int eje,
                                         string cadena, int actualVar, double adapt, double &umbral, int &clase, const vector<infoUp> &trozos, string &antecedenteSeleccionado, int &TriesNunmber);

  void TestearRecursivoUnEjemplo(const example_set &E, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, double &umbral, int &clase, string &antecedenteSeleccionado);
  void TestearRecursivo(const example_set &Es, const VectorVar &V, TestResult &result, bool normalizada, int TriesNumber, ProgramParameters InputParam);
  void TestearRecursivoUnEjemplo(const example_set &E, const VectorVar &V, const int eje, string cadena, int actualVar, double adapt, double &umbral, int &clase, string &antecedenteSeleccionado, bool normalizada, int &TriesNumber);

  int TesteoDistanciaHamming(const example_set &Es, const VectorVar &V, const int eje);
  void TestearRecursivoVariosDicionarios(const example_set &Es, const VectorVar &V, const Pattern &P3, const VectorVar &V3, const Pattern &P2, const VectorVar &V2, TestResult &result);

  int TestearPatronesBasicosClassicOriginal_UnEjemplo(const example_set &Es, const VectorVar &V, const int eje, double &mu, string &antecedente, bool normalizada);
  int TestearPatronesBasicosClassic_UnEjemplo(const example_set &Es, const VectorVar &V, const int eje, double &mu, string &antecedente, bool normalizada);
  void TestearPatronesBasicosClassic(const example_set &Es, const VectorVar &V, TestResult &result, ProgramParameters InputParam);
  void TestearPatronesBasicosClassicDisparos(const example_set &Es, const VectorVar &V, TestResult &result, vector<pair<int, pair<string, double>>> &disparos, ProgramParameters InputParam);
  void CalculoExactoDeAdaptacionesAPatrones(const example_set &E, const VectorVar &V);
  void CalcularPesoYClases(int weightRuleModel, const vector<double> &Cs);
  void Listar_Patrones();
  pair<string,info> BetterPatron(const vector<string> & listaPatrones);
  pair<string,info> ObtenerPatron(string antecedente);


  int N_Pattern() { return diccionario.size(); }
  int N_Patrones_paraClase(int clase) const;
  int N_Ejemplos_paraClase(int clase) const;
  void ReducirPatrones(const set<string> &conjunto);

  int InferirDiccionarioPatrones(vectordouble &ejemplo, const VectorVar &V);
  double InferirDicionario(const example_set &E, const VectorVar &V);
};

#endif
