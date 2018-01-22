#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include <ctype.h>
#include <gtk/gtk.h>

/*
+-------------------------------+
|			Estructuras			|
+-------------------------------+
 */
 /*se encarga de almacenar las entradas de donde se saca la informacion*/
 struct entryMemoria{
	 GtkWidget*entryop;
	 GtkWidget*entryfuente;
	 GtkWidget*entrydestino;
	 GtkWidget*entrycuarto;
	 GtkWidget*entrydato;
	 int direccion;
 };
 /*estructura usada para retornar informacion de la interpretacion de una microinstruccion*/
struct SalidaM{
	int test;/*hay que saltar a una linea*/
	int testn;/*linea a la que pasar*/
	int error;/*hubo un error, detener el programa*/
	int ok; /*no hay informacion que comunicar, seguir a la siguiente micro*/
};
/*estructura con datos importantes para la ALU*/
struct Adatos{
	int tam;	/*el numero de bits con los que se hace la operacion*/
	int16_t ultimo; /*el ultimo resultado que arrojo la alu*/
	int32_t ultimo32;	/*el ultimo pero en 32 bits*/
};
/*estrutura con los registros de la alu*/
struct Aregistros{
	int16_t b1;
	int16_t b2;
	int16_t b3;
	int16_t b4;
};
/* guarda los datos de la ALU*/
struct ALU{
	struct Adatos datos;
	struct Aregistros registros;

};
/*estructura donde se guardan las banderas*/
struct Banderas{
	int cf;
	int sf;
	int  zf;
	int intf;

};
/*estructura de una celda de memoria*/
struct CeldaM{
	int16_t numero;	/*numero que se va a guardar*/
	int16_t codop;	/*el codigo de operacion*/
	int16_t codf;	/*el codigo fuente*/
	int16_t codd;/*el codigo destino*/
	int16_t cuarto; /*el cuarto operando*/
};
/*estructura donde se almacenan las partes h y l de un registro*/
struct RegistroT{
	int8_t h;
	int8_t l;
};
/*estructura donde se almacenan los registros*/
struct RegistrosT{
	struct RegistroT a;
	struct RegistroT b;
	struct RegistroT c;
	struct RegistroT d;
};
struct Procesador{
	struct ALU alu;
	struct Banderas flags;
	struct RegistrosT registros;
	uint8_t pc;
	struct CeldaM ir;
	uint8_t mar;
	struct CeldaM mbr;
	uint16_t bd;
};
struct Instruccion{
	int codigo;
	char* nemonico;
};
/*
+-------------------------------+
|			Funciones			|
+-------------------------------+
 */
 /*
static void
activate (GtkApplication* app,
          gpointer        user_data);

static void
print_hello (GtkWidget *widget,
             gpointer   data);
			 */
/*convierte los registros h y l al registro x*/
int16_t hlToX(struct RegistroT r);

/*
**Funciones de la ALU**
*todas dejan el resultado en el b3
*si se produce un segundo valor como resultado de la operacion este se deja en b4
*/
/*suma de la alu*/
void aluadd(void);
/*chequea las banderas*/
void checkFlags(void);
/*resta de la alu*/
void alusub(void);
/*multiplicacion de la alu*/
void alumul(void);
/*division de la alu*/
void aludiv(void);
/*and de la alu*/
void aluand(void);
/*or de la alu*/
void aluor(void);
/*xor de la alu*/
void aluxor(void);
/*not de la alu*/
void alunot(void);
/*shl de la alu*/
void alushl(void);
/*shr de la alu*/
void alushr(void);
/**Funciones de parseo
*/
/*parsea un archivo de microinstrucciones, se usa para ejecutar una instruccion de asm*/
/*lee las instrucciones del asm*/
int cargaInstrucciones();
/*parsea el archivo de ensamblador*/
int parseASM(char*archivo,int mempos);
/*line to lower*/
char* lineLower(char* linea);
/*interpreta una linea de asm y retorna una celda de memoria con la informacion*/
struct CeldaM interpretASM(char *line);
/*compara una expresion con una regex*/
int reg_match(const char* str,const char* pattern);
/*hace match de una expresion con una regex*/
int match(const char *string, char *pattern);
/*incrementa el pc*/
void incPC(void);
/*interpreta una linea de microinstrucciones*/
struct SalidaM interpretMicro(char*line2);
/*parsea el archivo de microinstrucciones y ejecuta las instrucciones*/
int parseMicro(char* archivo,int mempos);
/**GUI
*
*/
static void hello( GtkWidget *widget,
                   gpointer   data );
/* another callback */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data );
static void destroy( GtkWidget *widget,
                     gpointer   data );
/*muestra la ayuda*/
static void show_ayuda( GtkWidget *widget,
                      gpointer   data );
/*acerca de*/
static void show_acercade( GtkWidget *widget,
                      gpointer   data );
/*info2*/
static void show_info2( GtkWidget *widget,
                      gpointer   data );
/*chequea si el valor introducido para un registro es valido*/
int valorValido(const gchar*valor);
/*atiende la salida de una popup*/
static void atender_popup_mar( GtkWidget *widget,
                      gpointer   data );
void close_window(GtkWidget *widget, gpointer window);
/*cuando se presiona el boton del mar*/
static void show_btnMAR( GtkWidget *widget,
                      gpointer   data );
/*cuando se presiona el boton del mar*/
static void show_btnPC( GtkWidget *widget,
                      gpointer   data );
/*atiende la salida de la popup del mar*/
static void atender_popup_pc( GtkWidget *widget,
                      gpointer   data );
/*cuando se presiona el boton del mar*/
static void show_btnMEM( GtkWidget *widget,
                      gpointer   data );
/*atiende la salida de la popup del mar*/
static void atender_popup_mem( GtkWidget *widget,
                      GObject*   data );
/*cuando se presiona el boton del mar*/
static void show_btnIR( GtkWidget *widget,
                      gpointer   data );
/*atiende la salida de la popup del mar*/
static void atender_popup_ir( GtkWidget *widget,
                      GObject*   data );
/*cuando se presiona el boton del mar*/
static void show_btnRegistros( GtkWidget *widget,
                      gpointer   data );
/*atiende la salida de la popup del mar*/
static void atender_popup_registros( GtkWidget *widget,
                      GObject*   data );
/*cuando se presiona el boton del mar*/
static void show_btnMBR( GtkWidget *widget,
                      gpointer   data );
/*atiende la salida de la popup del mar*/
static void atender_popup_mbr( GtkWidget *widget,
                      GObject*   data );
/*atiende el in*/
static void show_btnMBR2( GtkWidget *widget,
                      gpointer   data );
/*atiende el out*/
static void atender_popup_mbr2( GtkWidget *widget,
                      GObject*   data );
/*hace una lectura de la memoria*/
void lectura();
/*ejecuta el ciclo de fetch*/
int fetch(GtkWidget *widget,
                      gpointer   tipo);  
/*muestra un mensaje al usuario*/
void mostrarMensaje(char*mensaje);
/*escribe al text view*/
void writeEntry(char*texto);
/*limpia la afoc*/
void clearValores(void);
/*limpia una afoc*/
static void resetAFOC( GtkWidget *widget,
                      gpointer   data );
/*atiende el in*/
static void loadAFOC( GtkWidget *widget,
                      gpointer   data );
/*atiende el out*/
static void atender_lafoc( GtkWidget *widget,
                      GObject*   data );
static void nuevaMicro( GtkWidget *widget,
                      gpointer   data );
static void atender_nuevamicro( GtkWidget *widget,
                      GObject*   data );
/*crear interrupcion*/
static void nuevaInterrupcion( GtkWidget *widget,
                      gpointer   data );
/*cuando se presiona el boton del mar*/
static void show_btnALU( GtkWidget *widget,
                      gpointer   data );
/*atiende la salida de la popup del mar*/
static void atender_popup_alu( GtkWidget *widget,
                      GObject*   data );
/*cuando se presiona el boton del mar*/
static void show_btnFlags( GtkWidget *widget,
                      gpointer   data );
/*atiende la salida de la popup del mar*/
static void atender_popup_flags( GtkWidget *widget,
                      GObject*   data );
/*atiende el in*/
static void loadASM( GtkWidget *widget,
                      gpointer   data );
/*atiende el out*/
static void atender_lasm( GtkWidget *widget,
                      GObject*   data );


