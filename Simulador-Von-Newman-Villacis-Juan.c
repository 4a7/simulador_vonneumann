/*
+-------------------------------+
|	Codigos de instrucciones	|
+-------------------------------+
0: mov-/
1: out-/
2: in--
3: jmp-/
4: jz-/
5: cmp#include <string.h>
6: cli-/
7: sti-/
+-------------------------------+
|			Tabla de R/M		|
+-------------------------------+
0: ax
1: bx
2: cd
3: dx
4: al
5: bl
6: cl
7: dl
8: ah
9: bh
10: ch
11: dh
12: [dir]
13: [bl]
14: [bh]
16: es inmediato
*/
/*
cc n.c `pkg-config --cflags --libs gtk+-2.0`
*/
#include "Simulador-Von-Newman-Villacis-Juan.h"
int MEMSIZE=256;
int ETAPA_FETCH=1;
int NUMERO_LINEA=1;
char* PATH_MICROS="datos//codigo//micro";
char* pathinstrucciones="datos//codigo//micro//";
char* pathinstrucciones2="datos//codigo//micro//instruccion.es";
/*instanciacion de parametros*/
struct CeldaM memoria[256];
struct Instruccion instrucciones[256];
struct Procesador p;
char*direccionamiento[16]={"ax","bx","cx","dx","al","bl","cl","dl","ah","bh","ch","dh","[]","[bl]","[bh]","-"};
static int counter = 0;
GtkTextBuffer* buffer;
GtkTextIter end;
GtkWidget*destruir;
GtkWidget *window;
GtkWidget *btnPC;
GtkWidget *btnIR;
GtkWidget *btnUC;
GtkWidget *button;
GtkWidget *box1;
GtkWidget *vbox1;
GtkWidget *vbox2;
GtkWidget *vbox3;
GtkWidget *vbox4;
GtkWidget *vbox5;
GtkWidget *hboxMABR;
GtkWidget *btnBD;
GtkWidget *btnRT;
GtkWidget *btnFlags;
GtkWidget *btnALU;
GtkWidget *btnMBR;
GtkWidget *btnMAR;
GtkWidget *btnMem;
GtkWidget *btnFwd;
GtkWidget *btnNext;
GtkWidget *menubar;
GtkWidget *ayudamenu;
GtkWidget *ayudami;
GtkWidget *ayudami2;
GtkWidget *info2;
GtkWidget *acercademi2;
GtkWidget *herramientasmenu;
GtkWidget *herramientasmi;
GtkWidget *loadasmmi2;
GtkWidget *vbox6;
GtkWidget *entry_cmd;
GtkWidget *btnLAFOC;
GtkWidget *btnRAFOC;
GtkWidget *btnNueva;
GtkWidget *btnInt;
GtkWidget *btnLASM;

/* Our new improved callback.  The data passed to this function
 * is printed to stdout. */
static void callback( GtkWidget *widget,
                      gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (gchar *) data);
}

/* another callback */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

int main (int    argc,
      char **argv)
{
	/*instrucciones de inicio*/
	cargaInstrucciones();
	parseMicro("datos//codigo//asm.txt",12);
	g_print("imprimiendo");
	
	/*fin de instrucciones de inicio*/
	
	/*
  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
*/
/* GtkWidget is the storage type for widgets */
    

	
	
  GtkWidget *fileMenu;
  GtkWidget *fileMi;
  GtkWidget *quitMi;
    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* This is a new call, which just sets the title of our
     * new window to "Hello Buttons!" */
    gtk_window_set_title (GTK_WINDOW (window), "Simulador de Von Neumann");
	gtk_window_set_default_size(GTK_WINDOW(window),400,300);
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* Crea la caja donde se guarda todo */
    box1 = gtk_hbox_new (FALSE, 0);
	
	/*barra de menu*/
	menubar = gtk_menu_bar_new();
	/*menu de ayuda*/
	ayudamenu=gtk_menu_new();
	ayudami=gtk_menu_item_new_with_label("Ayuda");
	ayudami2=gtk_menu_item_new_with_label("Ayuda");
	acercademi2=gtk_menu_item_new_with_label("Acerca de");
	info2=gtk_menu_item_new_with_label("Ayuda para microprogramas");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ayudami), ayudamenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(ayudamenu),ayudami2);
	gtk_menu_shell_append(GTK_MENU_SHELL(ayudamenu),acercademi2);
	gtk_menu_shell_append(GTK_MENU_SHELL(ayudamenu),info2);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), ayudami);
	/*menu de herramientas*/
	herramientasmenu=gtk_menu_new();
	herramientasmi=gtk_menu_item_new_with_label("Microinstrucciones");
	loadasmmi2=gtk_menu_item_new_with_label("Ayuda para microinstrucciones");
	/*acercademi2=gtk_menu_item_new_with_label("Acerca de");*/
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(herramientasmi), herramientasmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(herramientasmenu),loadasmmi2);
	gtk_box_pack_start(GTK_BOX(box1), menubar, FALSE, FALSE, 0);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), herramientasmi);
	
	g_signal_connect_swapped (GTK_OBJECT(ayudami2), "activate",
		      G_CALLBACK (show_ayuda), NULL);
	g_signal_connect_swapped (GTK_OBJECT(acercademi2), "activate",
		      G_CALLBACK (show_acercade), NULL);
	g_signal_connect_swapped (GTK_OBJECT(loadasmmi2), "activate",
		      G_CALLBACK (show_info2), NULL);
	
	/*primera vbox*/
	
	vbox1=gtk_vbox_new(FALSE,0);
	btnUC = gtk_button_new_with_label (" UC ");
	gtk_box_pack_start (GTK_BOX(vbox1), btnUC, TRUE, TRUE, 0);
	btnIR = gtk_button_new_with_label ("IR");
	gtk_box_pack_start (GTK_BOX(vbox1), btnIR, TRUE, TRUE, 0);
	btnPC = gtk_button_new_with_label ("PC");
	gtk_box_pack_start (GTK_BOX(vbox1), btnPC, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX (box1), vbox1, TRUE, TRUE, 0);
	
	g_signal_connect (btnUC, "clicked",
		      G_CALLBACK (hello), NULL);
	g_signal_connect (btnIR, "clicked",
		      G_CALLBACK (show_btnIR), (gpointer) "button 2");
	g_signal_connect (btnPC, "clicked",
		      G_CALLBACK (show_btnPC), (gpointer) "button 2");
	gtk_widget_set_sensitive (btnUC,
                          FALSE);
	/*la segunda vbox*/
	
	vbox2=gtk_vbox_new(FALSE,0);
	btnBD = gtk_button_new_with_label ("Bus\nde\ndatos");
	gtk_box_pack_start (GTK_BOX(vbox2), btnBD, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX (box1), vbox2, TRUE, TRUE, 0);
	gtk_widget_set_sensitive (btnBD,
                          FALSE);
	
	/*tercera vbox*/
	
	vbox3=gtk_vbox_new(FALSE,0);
	btnRT = gtk_button_new_with_label ("Registros");
	gtk_box_pack_start (GTK_BOX(vbox3), btnRT, TRUE, TRUE, 0);
	btnFlags = gtk_button_new_with_label ("Banderas");
	gtk_box_pack_start (GTK_BOX(vbox3), btnFlags, TRUE, TRUE, 0);
	btnALU = gtk_button_new_with_label ("ALU");
	gtk_box_pack_start (GTK_BOX(vbox3), btnALU, TRUE, TRUE, 0);
	hboxMABR=gtk_hbox_new(FALSE,0);
	btnMAR= gtk_button_new_with_label ("MAR");
	gtk_box_pack_start (GTK_BOX(hboxMABR), btnMAR, TRUE, TRUE, 0);
	btnMBR= gtk_button_new_with_label ("MBR");
	gtk_box_pack_start (GTK_BOX(hboxMABR), btnMBR, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX (vbox3), hboxMABR, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX (box1), vbox3, TRUE, TRUE, 0);
	
	g_signal_connect (btnMAR, "clicked",
		      G_CALLBACK (show_btnMAR), (gpointer) "button 2");
	g_signal_connect (btnMBR, "clicked",
		      G_CALLBACK (show_btnMBR), (gpointer) "button 2");
	g_signal_connect (btnRT, "clicked",
		      G_CALLBACK (show_btnRegistros), (gpointer) "button 2");
	g_signal_connect (btnALU, "clicked",
		      G_CALLBACK (show_btnALU), (gpointer) "button 2");
	g_signal_connect (btnFlags, "clicked",
		      G_CALLBACK (show_btnFlags), (gpointer) "button 2");
	
	/*cuarta vbox*/
	
	vbox4=gtk_vbox_new(FALSE,0);
	int ii=0;
	int jj=0;
	int numero_btn;
	char texto_btn[6];
	GtkWidget*v;
	GtkWidget*b;
	int prueba;
	for (ii;ii<16;ii++){
		v=gtk_hbox_new(FALSE,0);
		jj=0;
		for(jj=0;jj<16;jj++){
			numero_btn=(16*ii)+jj;
			sprintf(texto_btn, "%d", numero_btn);
			prueba=((16*ii)+jj);
			/*g_print("%s",texto_btn);*/
			b=gtk_button_new_with_label (texto_btn);
			gtk_widget_set_size_request(GTK_WIDGET(b),35,21);
			g_signal_connect (b, "clicked",
		      G_CALLBACK (show_btnMEM),(gpointer)prueba );
			gtk_box_pack_start(GTK_BOX (v), b, FALSE, FALSE, 0);
			gtk_widget_show (b);
		}
		
		gtk_box_pack_start(GTK_BOX (vbox4), v, FALSE, FALSE, 0);
		gtk_widget_show (v);
	}
	/*btnMem = gtk_button_new_with_label ("Memoria");*/
	
	gtk_box_pack_start(GTK_BOX (box1), vbox4, TRUE, TRUE, 0);
	
	
	
	
	/*sexto vbox*/
	GtkWidget* scrolledwindow;
	
	vbox6=gtk_vbox_new(FALSE,0);
	scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request (scrolledwindow, 300, 200);
    entry_cmd = gtk_text_view_new();
	gtk_text_view_set_editable (entry_cmd,FALSE);
	gtk_text_view_set_left_margin (GTK_TEXT_VIEW(entry_cmd),5);
	gtk_text_view_set_right_margin (GTK_TEXT_VIEW(entry_cmd),5);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(entry_cmd));
	writeEntry("Iniciando la simulacion...");
	writeEntry("Cargando instrucciones...");
	writeEntry("Todos los procesos completados");
	writeEntry("Usar > para ejecutar una microinstruccion");
	writeEntry("Y >>> para ejecutar una de ASM");
	/*gtk_entry_set_max_length (GTK_ENTRY (entry_cmd),0);*/
	gtk_container_add(GTK_CONTAINER(scrolledwindow), entry_cmd);
	gtk_box_pack_start (GTK_BOX (vbox6), scrolledwindow, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX (box1), vbox6, TRUE, TRUE, 0);
	
	
	/*quinto vbox*/
	
	vbox5=gtk_vbox_new(FALSE,0);
	btnNext= gtk_button_new_with_label ( ">>>");
	gtk_box_pack_start(GTK_BOX (vbox5), btnNext, TRUE, TRUE, 0);
	btnFwd= gtk_button_new_with_label (">");
	gtk_box_pack_start(GTK_BOX (vbox5), btnFwd, TRUE, TRUE, 0);
	btnLAFOC= gtk_button_new_with_label ("Load\nAFOC");
	gtk_box_pack_start(GTK_BOX (vbox5), btnLAFOC, TRUE, TRUE, 0);
	btnRAFOC= gtk_button_new_with_label ("Reset\nAFOC");
	gtk_box_pack_start(GTK_BOX (vbox5), btnRAFOC, TRUE, TRUE, 0);
	btnNueva= gtk_button_new_with_label ("Nueva\nInstruccion");
	gtk_box_pack_start(GTK_BOX (vbox5), btnNueva, TRUE, TRUE, 0);
	btnInt= gtk_button_new_with_label ("Inte\nrrupcion");
	gtk_box_pack_start(GTK_BOX (vbox5), btnInt, TRUE, TRUE, 0);
	btnLASM= gtk_button_new_with_label ("Load\nASM");
	gtk_box_pack_start(GTK_BOX (vbox5), btnLASM, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX (box1), vbox5, TRUE, TRUE, 0);
    
	g_signal_connect (btnNext, "clicked",
		      G_CALLBACK (fetch), 1);
	g_signal_connect (btnFwd, "clicked",
		      G_CALLBACK (fetch), 0);
	g_signal_connect (btnLAFOC, "clicked",
		      G_CALLBACK (loadAFOC), 0);
	g_signal_connect (btnRAFOC, "clicked",
		      G_CALLBACK (resetAFOC), 0);
	g_signal_connect (btnNueva, "clicked",
		      G_CALLBACK (nuevaMicro), 0);
	g_signal_connect (btnInt, "clicked",
		      G_CALLBACK (nuevaInterrupcion), 0);
	g_signal_connect (btnLASM, "clicked",
		      G_CALLBACK (loadASM), 0);
	
	
	/* Put the box into the main window. */
    gtk_container_add (GTK_CONTAINER (window), box1);
    /* The order in which we show the buttons is not really important, but I
     * recommend showing the window last, so it all pops up at once. */
	/*se ensenan los botones*/
	/*primer vbox*/
	gtk_widget_show (btnPC);
	gtk_widget_show (btnIR);
	gtk_widget_show (btnUC);
	gtk_widget_show (vbox1);
	/*segundo vbox*/
	gtk_widget_show (btnBD);
	gtk_widget_show (vbox2);
	/*tercer vbox*/
	gtk_widget_show (btnMAR);
	gtk_widget_show (btnMBR);
	gtk_widget_show (btnALU);
	gtk_widget_show (btnFlags);
	gtk_widget_show (btnRT);
	gtk_widget_show (hboxMABR);
	gtk_widget_show (vbox3);
	/*cuarto vbox*/
	gtk_widget_show (vbox4);
	/*quinto vbox*/
	gtk_widget_show (btnNext);
	gtk_widget_show (btnFwd);
	gtk_widget_show (btnLAFOC);
	gtk_widget_show (btnRAFOC);
	gtk_widget_show (btnNueva);
	gtk_widget_show (btnInt);
	gtk_widget_show (vbox5);
	gtk_widget_show(btnLASM);
	
	
	/*sexto vbox*/
	gtk_widget_show (entry_cmd);
	gtk_widget_show (vbox6);
	gtk_widget_show (scrolledwindow);
	
	/*menu superior*/
	gtk_widget_show (menubar);
	/*ayuda*/
	gtk_widget_show (ayudami);
	gtk_widget_show (ayudami2);
    gtk_widget_show (acercademi2);
	/*herramientas*/
	gtk_widget_show (herramientasmi);
	gtk_widget_show (loadasmmi2);

    gtk_widget_show (box1);

    gtk_widget_show (window);
    
    /* Rest in gtk_main and wait for the fun to begin! */
    gtk_main ();

    return 0;

	/*
	int vvv[240]={0};
	int i;
	for(i=0;i<235;i++){
		vvv[i]=i;
	}
	int8_t v=230;
	uint8_t v2=230;
	printf("s: %d\n",vvv[230]);
	printf("s: %d\n",vvv[v]);
	//printf("u: %d\n",v2);
	p.alu.datos.tam=8;
	p.alu.registros.b1=258;
	p.alu.registros.b2=42;
	alushl();
	printf("R: %d\n",p.alu.registros.b3);
	printf("CF: %d\n",p.flags.cf);
	printf("ZF: %d\n",p.flags.zf);
	printf("SF: %d\n",p.flags.sf);
	printf("u: %d\n",p.alu.datos.ultimo);
	printf("u32: %d\n",p.alu.datos.ultimo32);
	*/
	/*
	
	
	for(int i=0;i<256;i++){
		printf("%d %s\n",instrucciones[i].codigo,instrucciones[i].nemonico);
	}
	*/
	
	
	/*
	parseASM("./p.asm",2);
	for(int i=0;i<MEMSIZE;i++){
		printf("%d-",memoria[i].codop);
	}
	struct CeldaM instruccion=interpretASM("sti");
	printf("codop: %d\n",instruccion.codop);
	printf("codf: %d\n",instruccion.codf);
	printf("codd: %d\n",instruccion.codd);
	printf("cuarto: %d\n",instruccion.cuarto);
	interpretMicro("test: if,2");
	*/
	

}
/*convierte los registros h y l al registro x*/
int16_t hlToX(struct RegistroT r){
	int16_t s;
	int8_t h=r.h;
	int8_t l=r.l;
	s=h;
	s=s<<8;
	s=s|(l&0xFF);
	return s;
}
int8_t xToH(int16_t r){
	int8_t h=((r>>8)&0xFF);
	return h;
}
int8_t xToL(int16_t r){
	int8_t h=(r&0xFF);
	g_print("xToL recib: %d %d",r,h);
	return h;
}
/*suma de la alu*/
void aluadd(void){
	int32_t b2=p.alu.registros.b2;
	int32_t b1=p.alu.registros.b1;
	p.alu.registros.b3=p.alu.registros.b2+p.alu.registros.b1;
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=(b1+b2);
	checkFlags();
}
/*resta de la alu*/
void alusub(void){
	int32_t b2=p.alu.registros.b2;
	int32_t b1=p.alu.registros.b1;
	p.alu.registros.b3=p.alu.registros.b1-p.alu.registros.b2;
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=(b1-b2);
	checkFlags();
}
/*multiplicacion de la alu*/
void alumul(void){
	int32_t b2=p.alu.registros.b2;
	int32_t b1=p.alu.registros.b1;
	p.alu.registros.b3=p.alu.registros.b1*p.alu.registros.b2;
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=(b1*b2);
	checkFlags();
}
/*division de la alu*/
void aludiv(void){
	int32_t b2=p.alu.registros.b2;
	int32_t b1=p.alu.registros.b1;
	p.alu.registros.b3=p.alu.registros.b1/p.alu.registros.b2;
	p.alu.registros.b4=p.alu.registros.b1%p.alu.registros.b2;
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=(b1/b2);
	checkFlags();
}
/*and de la alu*/
void aluand(void){
	p.alu.registros.b3=(p.alu.registros.b2&p.alu.registros.b1);
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=p.alu.registros.b3;
	checkFlags();

}
/*or de la alu*/
void aluor(void){
	p.alu.registros.b3=(p.alu.registros.b1|p.alu.registros.b2);
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=p.alu.registros.b3;
	checkFlags();
}
/*xor de la alu*/
void aluxor(void){
	p.alu.registros.b3=(p.alu.registros.b1^p.alu.registros.b2);
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=p.alu.registros.b3;
	checkFlags();
	
}
/*not de la alu*/
void alunot(void){
	p.alu.registros.b3=~(p.alu.registros.b1);
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=p.alu.registros.b3;
	checkFlags();
}
/*shl de la alu*/
void alushl(void){
	if(p.alu.datos.tam==16){
		p.alu.registros.b3=p.alu.registros.b1<<1;
	}
	else{
		p.alu.registros.b3=(p.alu.registros.b1&0xFF)<<1;
	}
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=p.alu.registros.b3;
	checkFlags();
}
/*shr de la alu*/
void alushr(void){
	if(p.alu.datos.tam==16){
		p.alu.registros.b3=p.alu.registros.b1>>1;
	}
	else{
		p.alu.registros.b3=(p.alu.registros.b1&0xFF)>>1;
	}
	p.alu.datos.ultimo=p.alu.registros.b3;
	p.alu.datos.ultimo32=p.alu.registros.b3;
	checkFlags();
}


/*chequea las banderas*/
void checkFlags(void){
	int32_t ultimo32=p.alu.datos.ultimo;
	if(p.alu.datos.tam==16){
		int16_t val=p.alu.datos.ultimo;
		/*zf*/
		if(val==0){
			p.flags.zf=1;
		}
		else{
			p.flags.zf=0;
		}
		/*sf*/
		if(val<0){
			p.flags.sf=1;
		}
		else{
			p.flags.sf=0;
		}
		/*cf*/
		if(p.alu.datos.ultimo32!=val){
			p.flags.cf=1;
		}
		else{
			p.flags.cf=0;
		}
	}
	else{
		int8_t val=p.alu.datos.ultimo;
		/*zf*/
		if(val==0){
			p.flags.zf=1;
		}
		else{
			p.flags.zf=0;
		}
		/*sf*/
		if(val<0){
			p.flags.sf=1;
		}
		else{
			p.flags.sf=0;
		}
		/*cf*/
		if(p.alu.datos.ultimo32!=val){
			p.flags.cf=1;
		}
		else{
			p.flags.cf=0;
		}
	}
}
/*lee las instrucciones del asm*/
int cargaInstrucciones(){
	g_print("ejecutando instruccion");
	FILE*fp;
	int codigo;
	char pathinstruccionesl2[200];
	strcpy(pathinstruccionesl2,PATH_MICROS);
	char pathinstruccionesl3[200];
	strcpy(pathinstruccionesl3,PATH_MICROS);
	char*path1="//instruccion.es";
	char*path2="//instruccion2.es";
	strcat(pathinstruccionesl2,path1);
	strcat(pathinstruccionesl3,path2);
	/*strcat(pathinstruccionesl3,"//instruccion2.es");*/
	g_print("%s %s",pathinstruccionesl2,pathinstruccionesl3);
	fp = fopen(pathinstruccionesl2, "r");
	if (fp == NULL)
        return 0;
    int i=0;
    char nemonico[256];
	while (fscanf(fp, "%d %s", &codigo, nemonico) == 2){
		
		char*ptrbuffer=strdup(nemonico);
		instrucciones[i].codigo=codigo;
		instrucciones[i].nemonico=ptrbuffer;
		g_print("%s %d \n",nemonico,codigo);
		i++;
	}
	fclose(fp);
	fp = fopen(pathinstruccionesl3, "r");
	if (fp == NULL)
        return 0;
	while (fscanf(fp, "%d %s", &codigo, nemonico) == 2){
		
		char*ptrbuffer=strdup(nemonico);
		instrucciones[i].codigo=codigo;
		instrucciones[i].nemonico=ptrbuffer;
		g_print("33 %s %d \n",nemonico,codigo);
		i++;
	}
	for(i;i<256;i++){
		instrucciones[i].codigo=-1;
	}
	fclose(fp);
	return 1;
}
/*parsea el archivo de ensamblador y lo carga a la memoria*/
int parseASM(char*archivo,int mempos){
	FILE*fp;
	fp = fopen(archivo, "r");
	if (fp == NULL)
        return 0;
    char line[256];
	struct CeldaM temp;
    while (fgets(line, sizeof(line), fp)) {
		if(mempos>=MEMSIZE){
			mempos=0;
		}
		/*convertir la linea  a minuscula*/
		
    	temp=interpretASM(line);
		memoria[mempos].codop=temp.codop;
		memoria[mempos].codf=temp.codf;
		memoria[mempos].codd=temp.codd;
		memoria[mempos].cuarto=temp.cuarto;
		mempos++;
    }
    fclose(fp);
    return 1;
}
/*interpreta una linea de asm y retorna una celda de memoria con la informacion*/
struct CeldaM interpretASM(char *line3){
	struct CeldaM salida;
	char* pch;
	regex_t re;
    int ret;
	

	/*line3[strlen(line3)-1] = '\0';*/
	char* line = strdup(line3);
	
	/*char*line;*/
	/*strncpy(line, line3, strlen(line3)-1);*/
	line[strlen(line)-1] = '\0';
	int valor;
	pch = strtok (line," ,.-");
	int operador=0;
	salida.codop=-1;
	salida.codf=-1;
	salida.codd=-1;
	salida.cuarto=-1;
	char *nueva;
	char*nonueva;
	  while (pch != NULL)
	  {
		  
		 /* pch[strcspn(pch, "\n")] = '\0';*/
	  	/*busca la instruccion*/
	  	if(operador==0){
	  		int j;
	  		for(j=0;instrucciones[j].codigo!=-1;j++){
	  			if(strcmp(instrucciones[j].nemonico,pch)==0){
	  				salida.codop=instrucciones[j].codigo;
					break;
	  			}
	  		}
	  	}
	  	/*busca los operandos*/
	  	else{
	  		if(operador==1 || operador==2){
	  			valor=-1;
				int i;
	  			for(i=0;direccionamiento[i]!="-";i++){
					nonueva=strdup(direccionamiento[i]);
					/*g_print("Comparando: -%s- -%s-\n",pch,direccionamiento[i]);*/
					nueva=strcat(nonueva, "\n");
					g_print("%s \n %s",nueva,pch);
			  		if(strcmp(direccionamiento[i],pch)==0 || strcmp(pch,nueva)==0){
		  				valor=i;
						g_print("%s IGUAL**\N",pch);
						break;
		  			}
			  	}
			  	if(strcmp(pch,"[bh]")==0){
			  		valor=14;
			  	}
			  	if(strcmp(pch,"[bl]")==0){
			  		valor=13;
			  	}
				/*si es un inmediato*/
				if(match(pch,"^[0-9]$") || match(pch,"^[0-9][0-9]$") || match(pch,"^[0-2][0-9][0-9]$")){
					int inm=atoi(pch);
					valor=16;
			  		salida.cuarto=inm;
			  	}
				/*si es un modo de direccionamiento indirecto*/
			  	if(match(pch,"^\[[0-9]+\]$") || match(pch,"^\[[0-9][0-9]+\]$") || match(pch,"^\[[0-2][0-9][0-9]+\]$")){
					
					pch++;
					pch[strlen(pch)-1] = 0;
					int inm=atoi(pch);
					salida.cuarto=inm;
			  		valor=12;
			  	}
			  	
			  	if(valor!=-1){
			  		if(operador==2){
			  			salida.codf=valor;
			  		}
			  		else{
			  			salida.codd=valor;
			  		}
			  	}
	  		}
	  	}
	  	
	  	operador++;
		pch = strtok (NULL, " ,");
	  }
	 free(line);
	return salida;
}
/*compara una expresion con una regex*/
int reg_match(const char* str,const char* pattern){
	regex_t re;
	int ret;
	if (regcomp(&re, pattern, REG_EXTENDED) != 0)
        return 0;

    ret = regexec(&re, str, (size_t) 0, NULL, 0);
    regfree(&re);

    if (ret == 0)
        return 1;

    return 0;
}
/*incrementa el pc*/
void incPC(void){
	if(p.pc==256){
		p.pc=0;
	}
	else{
		p.pc++;
	}
}
/*dice si una tira hace match con una regex*/
int
match(const char *string, char *pattern)
{
    int    status;
    regex_t    re;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return(0);      /* Report error. */
    }
    status = regexec(&re, string, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        return(0);      /* Report error. */
    }
    return(1);
}

/*parsea el archivo de microinstrucciones y ejecuta las instrucciones*/
int parseMicro(char* archivo,int mempos){
	FILE*fp;
	fp = fopen(archivo, "r");
	if (fp == NULL){
		g_print("saliendo de la funcion");
		return 0;
	}
        
    char line[256];
	struct CeldaM temp;
	g_print("inicio de la ejecucion..");
    while (fgets(line, sizeof(line), fp)) {
		if(mempos>=MEMSIZE){
			mempos=0;
		}
		/*
		line[strlen(line)-1] = '\0';
		g_print("****%s*************************",line);
		*/
		line[strcspn(line, "\n")] = '\0';
    	temp=interpretASM(line);
		memoria[mempos].codop=temp.codop;
		memoria[mempos].codf=temp.codf;
		memoria[mempos].codd=temp.codd;
		memoria[mempos].cuarto=temp.cuarto;
		mempos++;
    }
    fclose(fp);
    return 1;
	
}
/*interpreta y ejecuta una linea de microinstrucciones*/
struct SalidaM interpretMicro(char*line2){
	struct SalidaM salida;
	int inm=0;/*donde se guardan los inmediatos de los parametros*/
	char*regsops[22]={"ax","bx","cx","dx","al","bl","cl","dl","ah","bh","ch","dh","b1","b2","b3","b4","mar","mbr","bd","ir","if","pc"};
	char*aluops[10]={"add","sub","mul","div","and","or","xor","not","shl","shr"};
	char*memops[2]={"read","write"};
	char*flagsops[4]={"cf","zf","sf","if"};
	char* pch;
	char* line = strdup(line2);
	line[strlen(line)-1] = '\0';
	int alu,registro,mem,test,in,out;
	int registrod,registrof;/*saber cual es el registrof y el d*/
	int aluop,memop,flagop,testf;/*saber cuales son con los que se van a trabajar*/
	int testn=0;/*linea a la que se podria saltar*/
	pch = strtok (line," :,<-");
	alu=registro=mem=test=in=out=0;
	registrod=registrof=0;
	aluop=memop=flagop=0;
	char*a;
	char*b;
	char copia[10];
	char*copia2;
	
	
	int operador=0;/*por cual operador se va analizando*/
	while (pch != NULL){
		g_print("xxx");
		/*
		copia2=NULL;
		copia2=strdup(pch);
		
		g_print("PCH: -%s-",copia2);
		copia2[strlen(copia2)-1] = '\0';
		*/
		char*copia2;
		copia2=strdup(pch);
		copia2[strlen(copia2)-1] = '\0';
		g_print("PCH: -%s-",copia2);
		if(operador==0){
			int j=0;
			if(strcmp(pch,"alu")==0){
				alu=1;
			}
			else if(strcmp(pch,"mem")==0){
				mem=1;
			}
			else if(strcmp(pch,"test")==0){
				test=1;
			}
			else if(strcmp(pch,"in")==0 || strcmp(copia2,"in")==0){
				g_print("IN");
				in=1;
				break;
			}
			else if(strcmp(pch,"out")==0 || strcmp(copia2,"out")==0){
				g_print("OUT");
				out=1;
				break;
			}
			else{
				for(j=0;j<22;j++){
					if(strcmp(pch,regsops[j])==0){
						
						if(j<4){
							p.alu.datos.tam=16;
						}
						else if (j>=4 && j<12){
							p.alu.datos.tam=8;
						}
						registro=1;
						registrod=j;
						g_print("R11 %s %d\n",regsops[j],j);
						g_print("dddddddddddddddddddddddddddddddddddddddddddd");
						break;
					}
				}
			}
		}
		else if (operador==1){
			int j;
			/*buscar si es un registro*/
			/*buscar si es de la alu*/
			for(j=0;j<22;j++){
				g_print("antesssssssssssssssssssssssssssssssssssssssss%ds",j);
				a=strdup(regsops[j]);
				b=strcat(a, "\n");
				if((strcmp(pch,regsops[j])==0 || strcmp(pch,b)==0 || strcmp(copia2,regsops[j])==0)&& registro==1){
					g_print("R3 %s %d\n",regsops[j],j);
					registro=1;
					registrof=j;
					break;
				}
			}
			
			for(j=0;j<10;j++ && alu==1){
				a=strdup(aluops[j]);
				strcat(a, "\n");
				if(strcmp(pch,aluops[j])==0 || strcmp(pch,a)==0  || strcmp(copia2,aluops[j])==0){
					aluop=j;
					break;
				}
			}
			
			/*buscar si es una operacion de memoria*/
			for(j=0;j<2;j++){
				a=strdup(memops[j]);
				strcat(a, "\n");
				if((strcmp(pch,memops[j])==0 || strcmp(pch,a)==0  || strcmp(copia2,memops[j])==0) && mem==1){
					memop=j;
					break;
				}
			}
			/*buscar si es una bandera*/
			for(j=0;j<4;j++){
				a=strdup(flagsops[j]);
				strcat(a, "\n");
				if((strcmp(pch,flagsops[j])==0 || strcmp(pch,a)==0 || strcmp(copia2,flagsops[j])==0) && test==1){
					flagop=j;
					break;
				}
			}
		}
		else{
			if(match(pch,"^[0-9]$") || match(pch,"^[0-9][0-9]$") || match(pch,"^[0-2][0-9][0-9]$") || match(copia2,"^[0-9]$") || match(copia2,"^[0-9][0-9]$") || match(copia2,"^[0-2][0-9][0-9]$")){
				inm=atoi(copia2);
				inm--;
				g_print("INMEDIATO: %d",inm);
				testn=16;
			}
		}
	  	operador++;
		pch = strtok (NULL, " ,<-");
	}
	/*es una operacion de registros*/
	if(alu==1){
		g_print("Caso de alu: %d\n",aluop);
		switch(aluop){
			case 0:
				aluadd();
				break;
			case 1:
				g_print("fffffffffffffffffffffffffffff");
				alusub();
				break;
			case 2:
				alumul();
				break;
			case 3:
				if(p.alu.datos.tam==8){
					if((0xFF&p.alu.registros.b2)==0){
						salida.error=1;
					}
				}
				else{
					if(p.alu.registros.b2==0){
						salida.error=1;
					}
				}
				if(salida.error!=1){
					aludiv();
				}
				break;
			case 4:
				aluand();
				break;
			case 5:
				aluor();
				break;
			case 6:
				aluxor();
				break;
			case 7:
				alunot();
				break;
			case 8:
				alushl();
				break;
			case 9:
				alushr();
				break;
		}
	}
	else if (mem==1){
		switch(memop){
			case 0:/*read*/
				p.mbr.numero=memoria[p.mar%MEMSIZE].numero;
				break;
			case 1:/*write*/
			g_print("ESCRIBIENDOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
				memoria[p.mar%MEMSIZE].numero=p.mbr.numero;
				break;
		}
	}
	else if (registro==1){
		int16_t varfuente=0;
		switch (registrof){
			case 0:
				/*g_print("moviendo a variable");*/
				varfuente=hlToX(p.registros.a);
				break;
			case 1:
				varfuente=hlToX(p.registros.b);
				g_print("VARFUENTE: %d",varfuente);
				break;
			case 2:
				varfuente=hlToX(p.registros.c);
				break;
			case 3:
				varfuente=hlToX(p.registros.d);
				break;
			case 4:
				varfuente=p.registros.a.l;
				break;
			case 5:
				varfuente=p.registros.b.l;
				break;
			case 6:
				varfuente=p.registros.c.l;
				break;
			case 7:
				varfuente=p.registros.d.l;
				break;
			case 8:
				varfuente=p.registros.a.h;
				break;
			case 9:
				varfuente=p.registros.b.h;
				break;
			case 10:
				varfuente=p.registros.c.h;
				break;
			case 11:
				varfuente=p.registros.d.h;
				break;
			case 12:
				varfuente=p.alu.registros.b1;
				break;
			case 13:
				varfuente=p.alu.registros.b2;
				break;
			case 14:
				varfuente=p.alu.registros.b3;
				break;
			case 15:
				varfuente=p.alu.registros.b4;
				break;
			case 16:
				varfuente=p.mar;
				break;
			case 17:
				varfuente=p.mbr.numero;
				break;
			case 18:
				varfuente=p.bd;
				break;
			case 19:
				varfuente=p.ir.cuarto;
				break;
			case 21:
				varfuente=p.pc;
				break;
		}
		switch (registrod){
			case 0:
			g_print("VAR_RECIBIDA: %d %d %d ",varfuente,xToH(varfuente),xToL(varfuente));
				p.registros.a.h=xToH(varfuente);
				p.registros.a.l=xToL(varfuente);
				/*g_print("%d %d",p.registros.a.h,p.registros.a.l);*/
				break;
			case 1:
				p.registros.b.h=xToH(varfuente);
				p.registros.b.l=xToL(varfuente);
				break;
			case 2:
				p.registros.c.h=xToH(varfuente);
				p.registros.c.l=xToL(varfuente);
				break;
			case 3:
				p.registros.d.h=xToH(varfuente);
				p.registros.d.l=xToL(varfuente);
				break;
			case 4:
				p.registros.a.l=varfuente;
				break;
			case 5:
				p.registros.b.l=varfuente;
				break;
			case 6:
				p.registros.c.l=varfuente;
				break;
			case 7:
				p.registros.d.l=varfuente;
				break;
			case 8:
				p.registros.a.h=varfuente;
				break;
			case 9:
				p.registros.b.h=varfuente;
				break;
			case 10:
				p.registros.c.h=varfuente;
				break;
			case 11:
				p.registros.d.h=varfuente;
				break;
			case 12:
				p.alu.registros.b1=varfuente;
				break;
			case 13:
				p.alu.registros.b2=varfuente;
				break;
			case 14:
				p.alu.registros.b3=varfuente;
				break;
			case 15:
				p.alu.registros.b4=varfuente;
				break;
			case 16:
				p.mar=varfuente;
				break;
			case 17:
				p.mbr.numero=varfuente;
				break;
			case 18:
				p.bd=varfuente;
				break;
			case 19:
				p.ir.cuarto=varfuente;
				break;
			case 20:
				p.flags.intf=1;
				break;
			case 21:
				p.pc=varfuente;
		}
	}
	else if (test==1){
		switch(flagop){
			case 0:
				if(p.flags.cf==0){
					salida.test=1;
					salida.testn=testn;
					NUMERO_LINEA=inm;
				}
				else{
					salida.test=0;
				}
				break;
			case 1:
				if(p.flags.zf==0){
					salida.test=1;
					salida.testn=testn;
					NUMERO_LINEA=inm;
				}
				else{
					salida.test=0;
				}
				break;
			case 2:
				if(p.flags.sf==0){
					salida.test=1;
					salida.testn=testn;
					NUMERO_LINEA=inm;
				}
				else{
					salida.test=0;
				}
				break;
			case 3:
				if(p.flags.intf==0){
					salida.test=1;
					salida.testn=testn;
					NUMERO_LINEA=inm;
				}
				else{
					salida.test=0;
				}
				break;
		}
	}
	else if (in==1){
		printf("IN->MBR");
		show_btnMBR2(NULL,NULL);
	}
	else if (out==1){
		printf("MBR->OUT");
		writeEntry("Valor del OUT:");
		int someInt = p.mbr.numero;
		char str33[12];
		sprintf(str33, "%d", someInt);
		char*abc;
		abc=strdup(str33);
		writeEntry(abc);
	}
	printf("registros: %d\n",registro);
	printf("alu: %d\n",alu);
	printf("mem: %d\n",mem);
	printf("test: %d\n",test);
	printf("in: %d\n",in);
	printf("out: %d\n",out);
	printf("regf: %d\n",registrof);
	printf("regd: %d\n",registrod);
	printf("aluop: %d\n",aluop);
	printf("memop: %d\n",memop);
	printf("flagop: %d\n",flagop);
	return salida;
}


static void hello( GtkWidget *widget,
                   gpointer   data )
{
    g_print ("Hello World\n");
}



/* Another callback */
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

/*muestra la ayuda*/
static void show_ayuda( GtkWidget *widget,
                      gpointer   data )
{
	g_print("entro");
	GtkWidget*dialog = gtk_message_dialog_new (GTK_WINDOW(window),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "Este programa es complejo, entonces esta ayuda no puede ser muy especifica, pero se incluyen algunas cosas basicas. Se recomienda ver el manual de usuario para aprender como funciona. El boton >>> se usa para ejecutar una insturccion de ASm, el de > es para ejecutar una microinstruccion. Cada boton con un numero representa una posicion en la memoria, el boton Load AFOC carga una nueva AFOC, el boton Reset AFOC limpia la AFOC, el boton Nueva Instruccion se usa para crear una nueva instruccion, el boton Interrupcion ocasiona una interrupcion y el boton Load ASM carga un archivo de ASM. Del otro lado de la GUI estan los botones con los componentes de la AFOC, cuando se hace clic en ellos se puede ver su contenido. Para salir de esta ayuda se debe presionar dos veces el boton de salida en la parte de abajo de esta caja de texto");
 gtk_dialog_run (GTK_DIALOG (dialog));
 //gtk_widget_destroy (dialog); 
 g_signal_connect_swapped (GTK_OBJECT (dialog), "response",
                           G_CALLBACK (gtk_widget_destroy),
                           GTK_OBJECT (dialog));
}
/*acerca de*/
static void show_acercade( GtkWidget *widget,
                      gpointer   data )
{
	g_print("entro");
	GtkWidget*dialog = gtk_message_dialog_new (GTK_WINDOW(window),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "Lenguajes de Programacion\nSegundo semestre - 2017\nHecho por Juan Villacis");
 gtk_dialog_run (GTK_DIALOG (dialog));
 /*//gtk_widget_destroy (dialog); */
 g_signal_connect_swapped (GTK_OBJECT (dialog), "response",
                           G_CALLBACK (gtk_widget_destroy),
                           GTK_OBJECT (dialog));
}
/*informacion para microprogramas*/
static void show_info2( GtkWidget *widget,
                      gpointer   data )
{
	g_print("entro");
	GtkWidget*dialog = gtk_message_dialog_new (GTK_WINDOW(window),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "Los codigos para escribir microprogramas son \n\
Instrucciones     R/M\n\
 0: mov                   0: ax \n\
 1:out                      1: bx\n\
 2: in                         2: cd\n\
 3: jmp                     3: dx\n\
 4: jz                          4: al\n\
 5: cmp                    5: bl\n\
 6: cli                         6: cl\n\
 7: sti                        7: dl\n\
                                    8: ah\n\
                                    9: bh\n\
                                    10: ch\n\
                                    11: dh\n\
                                   12: [dir]\n\
                                    13: [bl]\n\
                                     14: [bh]\n\
                                     16: es inmediato\n\
                                  -1: para cualquier operador no definido");

 gtk_dialog_run (GTK_DIALOG (dialog));
 /*//gtk_widget_destroy (dialog); */
 g_signal_connect_swapped (GTK_OBJECT (dialog), "response",
                           G_CALLBACK (gtk_widget_destroy),
                           GTK_OBJECT (dialog));
}



/*cuando se presiona el boton del mar*/
static void show_btnMAR( GtkWidget *widget,
                      gpointer   data )
{
	char str[12];
	sprintf(str, "%d", p.mar);
	char* line = strdup(str);
	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "MAR");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 150, 150);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("MAR: ");
	GtkWidget*entry = gtk_entry_new();
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_popup_mar),(gpointer)entry);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entry), line);
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	gtk_widget_show(label);
	gtk_widget_show(entry);
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*atiende la salida de la popup del mar*/
static void atender_popup_mar( GtkWidget *widget,
                      gpointer   data )
{	
	g_print("atendiendo popup\n");
	int16_t numero=valorValido(gtk_entry_get_text((GtkEntry*)data));
	
	if(numero>=0){
		p.mar=numero;
		g_print("%d\n",p.mar);
		mostrarMensaje("Salvado Correctamente");
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}

}


/*cuando se presiona el boton del pc*/
static void show_btnPC( GtkWidget *widget,
                      gpointer   data )
{
	char str[12];
	sprintf(str, "%d", p.pc);
	char* line = strdup(str);
	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "PC");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 150, 150);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("PC: ");
	GtkWidget*entry = gtk_entry_new();
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_popup_pc),(gpointer)entry);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entry), line);
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	gtk_widget_show(label);
	gtk_widget_show(entry);
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*atiende la salida de la popup del pc*/
static void atender_popup_pc( GtkWidget *widget,
                      gpointer   data )
{	
	g_print("atendiendo popup pc\n");
	int16_t numero=valorValido(gtk_entry_get_text((GtkEntry*)data));
	
	if(numero>=0&&numero<256){
		p.pc=numero;
		g_print("%d\n",p.pc);
		mostrarMensaje("Salvado Correctamente");
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	

}

/*cuando se presiona el boton del pc*/
static void show_btnMEM( GtkWidget *widget,
                      gpointer   data )
{
	char str[12];
	sprintf(str, "%d", data);
	char* line = strdup(str);
	char cop[6];
	char cfue[6];
	char cdes[6];
	char ccua[6];
	char cdat[6];
	sprintf(cop,"%d",memoria[(int)data].codop);
	char*linecop=strdup(cop);
	sprintf(cfue,"%d",memoria[(int)data].codf);
	char*linecfue=strdup(cfue);
	sprintf(cdes,"%d",memoria[(int)data].codd);
	char*linecdes=strdup(cdes);
	sprintf(ccua,"%d",memoria[(int)data].cuarto);
	char*lineccua=strdup(ccua);
	sprintf(cdat,"%d",memoria[(int)data].numero);
	char*linedat=strdup(cdat);

	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "Celda de Memoria");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 250, 200);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("MEM: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	GtkWidget*h1box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Operando: ");
	GtkEntry*entryop = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h1box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h1box), entryop, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryop), linecop);
	gtk_widget_show(label);
	gtk_widget_show(entryop);
	gtk_box_pack_start (GTK_BOX (vbox), h1box, TRUE, TRUE, 0);
	gtk_widget_show(h1box);
	
	GtkWidget*h2box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Destino: ");
	GtkEntry*entrydestino = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h2box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h2box), entrydestino, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrydestino), linecdes);
	gtk_widget_show(label);
	gtk_widget_show(entrydestino);
	gtk_box_pack_start (GTK_BOX (vbox), h2box, TRUE, TRUE, 0);
	gtk_widget_show(h2box);
	
	GtkWidget*h3box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Fuente: ");
	GtkEntry*entryfuente = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h3box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h3box), entryfuente, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryfuente), linecfue);
	gtk_widget_show(label);
	gtk_widget_show(entryfuente);
	gtk_box_pack_start (GTK_BOX (vbox), h3box, TRUE, TRUE, 0);
	gtk_widget_show(h3box);
	
	GtkWidget*h4box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Cuarto: ");
	GtkEntry*entrycuarto = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h4box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h4box), entrycuarto, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrycuarto), lineccua);
	gtk_widget_show(label);
	gtk_widget_show(entrycuarto);
	gtk_box_pack_start (GTK_BOX (vbox), h4box, TRUE, TRUE, 0);
	gtk_widget_show(h4box);
	
	GtkWidget*h5box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Dato: ");
	GtkEntry*entrydato = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h5box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h5box), entrydato, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrydato), linedat);
	gtk_widget_show(label);
	gtk_widget_show(entrydato);
	gtk_box_pack_start (GTK_BOX (vbox), h5box, TRUE, TRUE, 0);
	gtk_widget_show(h5box);
	
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "entryop", entryop);
	g_object_set_data(G_OBJECT(btnsalvar), "entrydestino", entrydestino);
	g_object_set_data(G_OBJECT(btnsalvar), "entryfuente", entryfuente);
	g_object_set_data(G_OBJECT(btnsalvar), "entrycuarto", entrycuarto);
	g_object_set_data(G_OBJECT(btnsalvar), "entrydato", entrydato);
	g_object_set_data(G_OBJECT(btnsalvar), "direccion", data);
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_popup_mem),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*atiende la salida de la popup del pc*/
static void atender_popup_mem( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");

	
	GtkEntry *entryop = g_object_get_data (context_object, "entryop");
	GtkEntry *entrydato = g_object_get_data (context_object, "entrydato");
	GtkEntry *entryfuente = g_object_get_data (context_object, "entryfuente");
	GtkEntry *entrydestino = g_object_get_data (context_object, "entrydestino");
	GtkEntry *entrycuarto = g_object_get_data (context_object, "entrycuarto");
	int dir=g_object_get_data (context_object, "direccion");
	g_print("--\n");
	int16_t numeroop=valorValido(gtk_entry_get_text(entryop));
	int16_t numerofuente=valorValido(gtk_entry_get_text(entryfuente));
	int16_t numerodestino=valorValido(gtk_entry_get_text(entrydestino));
	int16_t numerocuarto=valorValido(gtk_entry_get_text(entrycuarto));
	int16_t numerodato=valorValido(gtk_entry_get_text(entrydato));
	
	/*
	if(numeroop>=0&&numerofuente>=0&&numerodestino>=0&&numerocuarto>=0&&numerodato>=0){
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	memoria[dir].numero=numerodato;
		memoria[dir].codop=numeroop;
		memoria[dir].codf=numerofuente;
		memoria[dir].codd=numerodestino;
		memoria[dir].cuarto=numerocuarto;
		g_print("--%d\n",numeroop);
		mostrarMensaje("Salvado Correctamente");
}


/*cuando se presiona el boton del pc*/
static void show_btnIR( GtkWidget *widget,
                      gpointer   data )
{
	char str[12];
	sprintf(str, "%d", data);
	char* line = strdup(str);
	char cop[6];
	char cfue[6];
	char cdes[6];
	char ccua[6];
	char cdat[6];
	sprintf(cop,"%d",p.ir.codop);
	char*linecop=strdup(cop);
	sprintf(cfue,"%d",p.ir.codf);
	char*linecfue=strdup(cfue);
	sprintf(cdes,"%d",p.ir.codd);
	char*linecdes=strdup(cdes);
	sprintf(ccua,"%d",p.ir.cuarto);
	char*lineccua=strdup(ccua);
	sprintf(cdat,"%d",p.ir.numero);
	char*linedat=strdup(cdat);

	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "IR");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 250, 200);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("IR: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	GtkWidget*h1box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Operando: ");
	GtkEntry*entryop = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h1box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h1box), entryop, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryop), linecop);
	gtk_widget_show(label);
	gtk_widget_show(entryop);
	gtk_box_pack_start (GTK_BOX (vbox), h1box, TRUE, TRUE, 0);
	gtk_widget_show(h1box);
	
	GtkWidget*h2box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Destino: ");
	GtkEntry*entrydestino = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h2box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h2box), entrydestino, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrydestino), linecdes);
	gtk_widget_show(label);
	gtk_widget_show(entrydestino);
	gtk_box_pack_start (GTK_BOX (vbox), h2box, TRUE, TRUE, 0);
	gtk_widget_show(h2box);
	
	GtkWidget*h3box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Fuente: ");
	GtkEntry*entryfuente = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h3box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h3box), entryfuente, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryfuente), linecfue);
	gtk_widget_show(label);
	gtk_widget_show(entryfuente);
	gtk_box_pack_start (GTK_BOX (vbox), h3box, TRUE, TRUE, 0);
	gtk_widget_show(h3box);
	
	GtkWidget*h4box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Cuarto: ");
	GtkEntry*entrycuarto = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h4box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h4box), entrycuarto, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrycuarto), lineccua);
	gtk_widget_show(label);
	gtk_widget_show(entrycuarto);
	gtk_box_pack_start (GTK_BOX (vbox), h4box, TRUE, TRUE, 0);
	gtk_widget_show(h4box);
	
	GtkWidget*h5box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Dato: ");
	GtkEntry*entrydato = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h5box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h5box), entrydato, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrydato), linedat);
	gtk_widget_show(label);
	gtk_widget_show(entrydato);
	gtk_box_pack_start (GTK_BOX (vbox), h5box, TRUE, TRUE, 0);
	gtk_widget_show(h5box);
	
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "entryop", entryop);
	g_object_set_data(G_OBJECT(btnsalvar), "entrydestino", entrydestino);
	g_object_set_data(G_OBJECT(btnsalvar), "entryfuente", entryfuente);
	g_object_set_data(G_OBJECT(btnsalvar), "entrycuarto", entrycuarto);
	g_object_set_data(G_OBJECT(btnsalvar), "entrydato", entrydato);
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_popup_ir),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*atiende la salida de la popup del pc*/
static void atender_popup_ir( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");

	
	GtkEntry *entryop = g_object_get_data (context_object, "entryop");
	GtkEntry *entrydato = g_object_get_data (context_object, "entrydato");
	GtkEntry *entryfuente = g_object_get_data (context_object, "entryfuente");
	GtkEntry *entrydestino = g_object_get_data (context_object, "entrydestino");
	GtkEntry *entrycuarto = g_object_get_data (context_object, "entrycuarto");
	int16_t numeroop=valorValido(gtk_entry_get_text(entryop));
	int16_t numerofuente=valorValido(gtk_entry_get_text(entryfuente));
	int16_t numerodestino=valorValido(gtk_entry_get_text(entrydestino));
	int16_t numerocuarto=valorValido(gtk_entry_get_text(entrycuarto));
	int16_t numerodato=valorValido(gtk_entry_get_text(entrydato));
	/*
	if(numeroop>=0&&numerofuente>=0&&numerodestino>=0&&numerocuarto>=0&&numerodato>=0){
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	p.ir.numero=numerodato;
		p.ir.codop=numeroop;
		p.ir.codf=numerofuente;
		p.ir.codd=numerodestino;
		p.ir.cuarto=numerocuarto;
		mostrarMensaje("Salvado Correctamente");
}

/*cuando se presiona el boton del pc*/
static void show_btnRegistros( GtkWidget *widget,
                      gpointer   data )
{
	char str[12];
	sprintf(str, "%d", data);
	char* line = strdup(str);
	char al[6];
	char ah[6];
	char bl[6];
	char bh[6];
	char cl[6];
	char ch[6];
	char dl[6];
	char dh[6];

	sprintf(al,"%d",p.registros.a.l);
	char*lal=strdup(al);
	sprintf(ah,"%d",p.registros.a.h);
	char*lah=strdup(ah);
	
	sprintf(bl,"%d",p.registros.b.l);
	char*lbl=strdup(bl);
	sprintf(bh,"%d",p.registros.b.h);
	char*lbh=strdup(bh);
	
	sprintf(cl,"%d",p.registros.c.l);
	char*lcl=strdup(cl);
	sprintf(ch,"%d",p.registros.c.h);
	char*lch=strdup(ch);
	
	sprintf(dl,"%d",p.registros.d.l);
	char*ldl=strdup(dl);
	sprintf(dh,"%d",p.registros.d.h);
	char*ldh=strdup(dh);
	

	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "Registros");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 400, 200);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("Registros: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	GtkWidget*h1box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("AH/AL: ");
	GtkWidget*eah = gtk_entry_new();
	GtkWidget*eal = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h1box), label, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (eah), lah);
	gtk_entry_set_text (GTK_ENTRY (eal), lal);
	gtk_box_pack_start (GTK_BOX (h1box), eah, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h1box), eal, TRUE, TRUE, 0);
	gtk_widget_show(label);
	gtk_widget_show(eah);
	gtk_widget_show(eal);
	gtk_box_pack_start (GTK_BOX (vbox), h1box, TRUE, TRUE, 0);
	gtk_widget_show(h1box);
	
	GtkWidget*h2box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("BH/BL: ");
	GtkWidget*ebh = gtk_entry_new();
	GtkWidget*ebl = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h2box), label, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (ebh), lbh);
	gtk_entry_set_text (GTK_ENTRY (ebl), lbl);
	gtk_box_pack_start (GTK_BOX (h2box), ebh, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h2box), ebl, TRUE, TRUE, 0);
	gtk_widget_show(label);
	gtk_widget_show(ebh);
	gtk_widget_show(ebl);
	gtk_box_pack_start (GTK_BOX (vbox), h2box, TRUE, TRUE, 0);
	gtk_widget_show(h2box);
	
	GtkWidget*h3box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("CH/CL: ");
	GtkWidget*ech = gtk_entry_new();
	GtkWidget*ecl = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h3box), label, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (ech), lch);
	gtk_entry_set_text (GTK_ENTRY (ecl), lcl);
	gtk_box_pack_start (GTK_BOX (h3box), ech, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h3box), ecl, TRUE, TRUE, 0);
	gtk_widget_show(label);
	gtk_widget_show(ech);
	gtk_widget_show(ecl);
	gtk_box_pack_start (GTK_BOX (vbox), h3box, TRUE, TRUE, 0);
	gtk_widget_show(h3box);
	
	GtkWidget*h4box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("DH/DL: ");
	GtkWidget*edh = gtk_entry_new();
	GtkWidget*edl = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h4box), label, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (edh), ldh);
	gtk_entry_set_text (GTK_ENTRY (edl), ldl);
	gtk_box_pack_start (GTK_BOX (h4box), edh, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h4box), edl, TRUE, TRUE, 0);
	gtk_widget_show(label);
	gtk_widget_show(edh);
	gtk_widget_show(edl);
	gtk_box_pack_start (GTK_BOX (vbox), h4box, TRUE, TRUE, 0);
	gtk_widget_show(h4box);
	
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "eah", eah);
	g_object_set_data(G_OBJECT(btnsalvar), "eal", eal);
	
	g_object_set_data(G_OBJECT(btnsalvar), "ebh", ebh);
	g_object_set_data(G_OBJECT(btnsalvar), "ebl", ebl);
	
	g_object_set_data(G_OBJECT(btnsalvar), "ech", ech);
	g_object_set_data(G_OBJECT(btnsalvar), "ecl", ecl);
	
	g_object_set_data(G_OBJECT(btnsalvar), "edh", edh);
	g_object_set_data(G_OBJECT(btnsalvar), "edl", edl);
	
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_popup_registros),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*atiende la salida de la popup del pc*/
static void atender_popup_registros( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");

	
	GtkEntry *eah = g_object_get_data (context_object, "eah");
	GtkEntry *eal = g_object_get_data (context_object, "eal");
	
	GtkEntry *ebh = g_object_get_data (context_object, "ebh");
	GtkEntry *ebl = g_object_get_data (context_object, "ebl");
	
	GtkEntry *ech = g_object_get_data (context_object, "ech");
	GtkEntry *ecl = g_object_get_data (context_object, "ecl");
	
	GtkEntry *edh = g_object_get_data (context_object, "edh");
	GtkEntry *edl = g_object_get_data (context_object, "edl");
	
	int16_t ah=valorValido(gtk_entry_get_text(eah));
	int16_t al=valorValido(gtk_entry_get_text(eal));
	
	int16_t bh=valorValido(gtk_entry_get_text(ebh));
	int16_t bl=valorValido(gtk_entry_get_text(ebl));
	
	int16_t ch=valorValido(gtk_entry_get_text(ech));
	int16_t cl=valorValido(gtk_entry_get_text(ecl));
	
	int16_t dh=valorValido(gtk_entry_get_text(edh));
	int16_t dl=valorValido(gtk_entry_get_text(edl));
	
	/*
	if(eah>=0&&eal>=0&&ebh>=0&&ebl>=0&&ech>=0&&ecl>=0&&edh>=0&&edl>=0){
		/*p.pc=numero;
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	p.registros.a.h=ah;
		p.registros.a.l=al;
		p.registros.b.h=bh;
		p.registros.b.l=bl;
		p.registros.c.h=ch;
		p.registros.c.l=cl;
		p.registros.d.h=dh;
		p.registros.d.l=dl;
		mostrarMensaje("Salvado Correctamente");
}






/*chequea si el valor introducido para un registro es valido*/
int valorValido(const gchar*pch){
	int inm=-1;
	if(match(pch,"^[0-9]$") || match(pch,"^[0-9][0-9]$") || match(pch,"^[0-2][0-9][0-9]$")){
		inm=atoi(pch);
	}
	return inm;
}


/*cuando se presiona el boton del mbr*/
static void show_btnMBR( GtkWidget *widget,
                      gpointer   data )
{
	char str[12];
	sprintf(str, "%d", data);
	char* line = strdup(str);
	char cop[6];
	char cfue[6];
	char cdes[6];
	char ccua[6];
	char cdat[6];
	sprintf(cop,"%d",p.mbr.codop);
	char*linecop=strdup(cop);
	sprintf(cfue,"%d",p.mbr.codf);
	char*linecfue=strdup(cfue);
	sprintf(cdes,"%d",p.mbr.codd);
	char*linecdes=strdup(cdes);
	sprintf(ccua,"%d",p.mbr.cuarto);
	char*lineccua=strdup(ccua);
	sprintf(cdat,"%d",p.mbr.numero);
	char*linedat=strdup(cdat);

	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "MBR");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 250, 200);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("MBR: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	GtkWidget*h1box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Operando: ");
	GtkEntry*entryop = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h1box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h1box), entryop, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryop), linecop);
	gtk_widget_show(label);
	gtk_widget_show(entryop);
	gtk_box_pack_start (GTK_BOX (vbox), h1box, TRUE, TRUE, 0);
	gtk_widget_show(h1box);
	
	GtkWidget*h2box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Destino: ");
	GtkEntry*entrydestino = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h2box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h2box), entrydestino, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrydestino), linecdes);
	gtk_widget_show(label);
	gtk_widget_show(entrydestino);
	gtk_box_pack_start (GTK_BOX (vbox), h2box, TRUE, TRUE, 0);
	gtk_widget_show(h2box);
	
	GtkWidget*h3box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Fuente: ");
	GtkEntry*entryfuente = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h3box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h3box), entryfuente, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryfuente), linecfue);
	gtk_widget_show(label);
	gtk_widget_show(entryfuente);
	gtk_box_pack_start (GTK_BOX (vbox), h3box, TRUE, TRUE, 0);
	gtk_widget_show(h3box);
	
	GtkWidget*h4box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Cuarto: ");
	GtkEntry*entrycuarto = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h4box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h4box), entrycuarto, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrycuarto), lineccua);
	gtk_widget_show(label);
	gtk_widget_show(entrycuarto);
	gtk_box_pack_start (GTK_BOX (vbox), h4box, TRUE, TRUE, 0);
	gtk_widget_show(h4box);
	
	GtkWidget*h5box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Dato: ");
	GtkEntry*entrydato = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h5box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h5box), entrydato, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrydato), linedat);
	gtk_widget_show(label);
	gtk_widget_show(entrydato);
	gtk_box_pack_start (GTK_BOX (vbox), h5box, TRUE, TRUE, 0);
	gtk_widget_show(h5box);
	
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "entryop", entryop);
	g_object_set_data(G_OBJECT(btnsalvar), "entrydestino", entrydestino);
	g_object_set_data(G_OBJECT(btnsalvar), "entryfuente", entryfuente);
	g_object_set_data(G_OBJECT(btnsalvar), "entrycuarto", entrycuarto);
	g_object_set_data(G_OBJECT(btnsalvar), "entrydato", entrydato);
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_popup_mbr),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*atiende la salida de la popup del pc*/
static void atender_popup_mbr( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");

	
	GtkEntry *entryop = g_object_get_data (context_object, "entryop");
	GtkEntry *entrydato = g_object_get_data (context_object, "entrydato");
	GtkEntry *entryfuente = g_object_get_data (context_object, "entryfuente");
	GtkEntry *entrydestino = g_object_get_data (context_object, "entrydestino");
	GtkEntry *entrycuarto = g_object_get_data (context_object, "entrycuarto");
	int16_t numeroop=valorValido(gtk_entry_get_text(entryop));
	int16_t numerofuente=valorValido(gtk_entry_get_text(entryfuente));
	int16_t numerodestino=valorValido(gtk_entry_get_text(entrydestino));
	int16_t numerocuarto=valorValido(gtk_entry_get_text(entrycuarto));
	int16_t numerodato=valorValido(gtk_entry_get_text(entrydato));
	/*
	if(numeroop>=0&&numerofuente>=0&&numerodestino>=0&&numerocuarto>=0&&numerodato>=0){
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	p.mbr.numero=numerodato;
		p.mbr.codop=numeroop;
		p.mbr.codf=numerofuente;
		p.mbr.codd=numerodestino;
		p.mbr.cuarto=numerocuarto;
		mostrarMensaje("Salvado Correctamente");
}

/*cuando se presiona el boton del pc*/
static void show_btnMBR2( GtkWidget *widget,
                      gpointer   data )
{
	char str[12];
	sprintf(str, "%d", data);
	char* line = strdup(str);
	char cop[6];
	char cfue[6];
	char cdes[6];
	char ccua[6];
	char cdat[6];
	sprintf(cop,"%d",p.mbr.codop);
	char*linecop=strdup(cop);
	sprintf(cfue,"%d",p.mbr.codf);
	char*linecfue=strdup(cfue);
	sprintf(cdes,"%d",p.mbr.codd);
	char*linecdes=strdup(cdes);
	sprintf(ccua,"%d",p.mbr.cuarto);
	char*lineccua=strdup(ccua);
	sprintf(cdat,"%d",p.mbr.numero);
	char*linedat=strdup(cdat);

	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "MBR");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 200, 200);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("MBR: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	GtkWidget*h5box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Dato: ");
	GtkEntry*entrydato = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h5box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h5box), entrydato, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrydato), linedat);
	gtk_widget_show(label);
	gtk_widget_show(entrydato);
	gtk_box_pack_start (GTK_BOX (vbox), h5box, TRUE, TRUE, 0);
	gtk_widget_show(h5box);
	
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "entrydato", entrydato);
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_popup_mbr2),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*atiende la salida de la popup del pc*/
static void atender_popup_mbr2( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");
	GtkEntry *entrydato = g_object_get_data (context_object, "entrydato");
	int16_t numerodato=valorValido(gtk_entry_get_text(entrydato));
	/*
	if(numeroop>=0&&numerofuente>=0&&numerodestino>=0&&numerocuarto>=0&&numerodato>=0){
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	p.mbr.numero=numerodato;
	mostrarMensaje("Salvado Correctamente");
}





/*carga una afoc*/
static void loadAFOC( GtkWidget *widget,
                      gpointer   data )
{


	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "Load AFOC");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 200, 150);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("Load AFOC: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	GtkWidget*h5box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Path: ");
	GtkEntry*entrydato = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h5box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h5box), entrydato, TRUE, TRUE, 0);
	gtk_widget_show(label);
	gtk_widget_show(entrydato);
	gtk_box_pack_start (GTK_BOX (vbox), h5box, TRUE, TRUE, 0);
	gtk_widget_show(h5box);
	
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "entrydato", entrydato);
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_lafoc),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*termina de cargas la afoc*/
static void atender_lafoc( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");
	GtkEntry *entrydato = g_object_get_data (context_object, "entrydato");
	PATH_MICROS=strdup(gtk_entry_get_text(entrydato));
	cargaInstrucciones();
	/*
	if(numeroop>=0&&numerofuente>=0&&numerodestino>=0&&numerocuarto>=0&&numerodato>=0){
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	mostrarMensaje("Cargada Correctamente");
}
/*limpia una afoc*/
static void resetAFOC( GtkWidget *widget,
                      gpointer   data )
{
	clearValores();
}

/*crea una nueva microinstruccion*/
static void nuevaMicro( GtkWidget *widget,
                      gpointer   data )
{	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "Load AFOC");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 250, 150);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("Nemonico: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	GtkWidget*h5box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Nemonico: ");
	GtkEntry*entrydato = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h5box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h5box), entrydato, TRUE, TRUE, 0);
	gtk_widget_show(label);
	gtk_widget_show(entrydato);
	gtk_box_pack_start (GTK_BOX (vbox), h5box, TRUE, TRUE, 0);
	gtk_widget_show(h5box);
	
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "entrydato", entrydato);
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_nuevamicro),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*termina de crear una nueva microinstruccion*/
static void atender_nuevamicro( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");
	GtkEntry *entrydato = g_object_get_data (context_object, "entrydato");
	char*nemo=gtk_entry_get_text(entrydato);
	int i=0;
	int max=0;
	for(i=0;i<256;i++){
		if(instrucciones[i].codigo>max){
			max=instrucciones[i].codigo;
		}
	}
	max++;
	char str[10];
    sprintf(str, "%d", max);
	char instruc[20];
	strcpy(instruc,nemo);
	strcat(str," ");
	strcat(str,instruc);
	strcat(str,"\n");
	
	
	char path[200];
	strcpy(path,PATH_MICROS);
	char*path1="//instruccion2.es";
	strcat(path,path1);
	FILE*fp;
	fp = fopen(path, "a");
	if (fp == NULL){
		g_print("*sale");
		return 0;
	}
	g_print(path);
	/*fprintf(fp, "%s", "\n");*/
	fprintf(fp, "%s", str);
	/*fprintf(fp, "%s", "\n");*/
	fclose(fp);
	for(i=0;i<256;i++){
		if(instrucciones[i].codigo>-1){
			instrucciones[i].codigo=max;
			instrucciones[i].nemonico=strdup(nemo);
		}
	}
	
	/*
	if(numeroop>=0&&numerofuente>=0&&numerodestino>=0&&numerocuarto>=0&&numerodato>=0){
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	char str2[10];
    sprintf(str2, "%d", max);
	char mensaje[200]="Creada correctamente\nEl codigo es: ";
	strcat(mensaje,str2);
	mostrarMensaje(mensaje);
}

/*limpia una afoc*/
static void nuevaInterrupcion( GtkWidget *widget,
                      gpointer   data )
{
	p.flags.intf=1;
	g_print("%FLAGS: d",p.flags.intf);
}




/*cuando se presiona el boton del pc*/
static void show_btnFlags( GtkWidget *widget,
                      gpointer   data )
{
	char zf[6];
	sprintf(zf,"%d",p.flags.zf);
	char*linezf=strdup(zf);
	char cf[6];
	sprintf(cf,"%d",p.flags.cf);
	char*linecf=strdup(cf);
	char sf[6];
	sprintf(sf,"%d",p.flags.sf);
	char*linesf=strdup(sf);
	char intf[6];
	sprintf(intf,"%d",p.flags.intf);
	char*lineintf=strdup(intf);
	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "Flags");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 250, 200);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("Flags: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	GtkWidget*h1box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("CF: ");
	GtkEntry*entrycf = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h1box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h1box), entrycf, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrycf), linecf);
	gtk_widget_show(label);
	gtk_widget_show(entrycf);
	gtk_box_pack_start (GTK_BOX (vbox), h1box, TRUE, TRUE, 0);
	gtk_widget_show(h1box);
	
	GtkWidget*h2box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("SF: ");
	GtkEntry*entrysf = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h2box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h2box), entrysf, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrysf), linesf);
	gtk_widget_show(label);
	gtk_widget_show(entrysf);
	gtk_box_pack_start (GTK_BOX (vbox), h2box, TRUE, TRUE, 0);
	gtk_widget_show(h2box);
	
	GtkWidget*h3box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("IF: ");
	GtkEntry*entryif = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h3box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h3box), entryif, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryif), lineintf);
	gtk_widget_show(label);
	gtk_widget_show(entryif);
	gtk_box_pack_start (GTK_BOX (vbox), h3box, TRUE, TRUE, 0);
	gtk_widget_show(h3box);
	
	GtkWidget*h4box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("ZF: ");
	GtkEntry*entryzf = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h4box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h4box), entryzf, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryzf), linezf);
	gtk_widget_show(label);
	gtk_widget_show(entryzf);
	gtk_box_pack_start (GTK_BOX (vbox), h4box, TRUE, TRUE, 0);
	gtk_widget_show(h4box);
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "entrycf", entrycf);
	g_object_set_data(G_OBJECT(btnsalvar), "entryzf", entryzf);
	g_object_set_data(G_OBJECT(btnsalvar), "entryif", entryif);
	g_object_set_data(G_OBJECT(btnsalvar), "entrysf", entrysf);
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_popup_flags),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*atiende la salida de la popup del pc*/
static void atender_popup_flags( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");

	
	GtkEntry *entrycf = g_object_get_data (context_object, "entrycf");
	GtkEntry *entryzf = g_object_get_data (context_object, "entryzf");
	GtkEntry *entrysf = g_object_get_data (context_object, "entrysf");
	GtkEntry *entryif = g_object_get_data (context_object, "entryif");

	int16_t numerozf=valorValido(gtk_entry_get_text(entryzf));
	int16_t numerosf=valorValido(gtk_entry_get_text(entrysf));
	int16_t numerocf=valorValido(gtk_entry_get_text(entrycf));
	int16_t numeroif=valorValido(gtk_entry_get_text(entryif));
	/*
	if(numeroop>=0&&numerofuente>=0&&numerodestino>=0&&numerocuarto>=0&&numerodato>=0){
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	p.flags.zf=numerozf;
	p.flags.cf=numerocf;
	p.flags.sf=numerosf;
	p.flags.intf=numeroif;
	mostrarMensaje("Salvado Correctamente");
}

/*cuando se presiona el boton del pc*/
static void show_btnALU( GtkWidget *widget,
                      gpointer   data )
{
	char zf[6];
	sprintf(zf,"%d",p.alu.registros.b1);
	char*linezf=strdup(zf);
	char cf[6];
	sprintf(cf,"%d",p.alu.registros.b2);
	char*linecf=strdup(cf);
	char sf[6];
	sprintf(sf,"%d",p.alu.registros.b3);
	char*linesf=strdup(sf);
	char intf[6];
	sprintf(intf,"%d",p.alu.registros.b4);
	char*lineintf=strdup(intf);
	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "Flags");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 250, 200);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("Flags: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	
	GtkWidget*h4box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("b1: ");
	GtkEntry*entryzf = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h4box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h4box), entryzf, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryzf), linezf);
	gtk_widget_show(label);
	gtk_widget_show(entryzf);
	gtk_box_pack_start (GTK_BOX (vbox), h4box, TRUE, TRUE, 0);
	gtk_widget_show(h4box);
	
	GtkWidget*h1box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("b2: ");
	GtkEntry*entrycf = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h1box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h1box), entrycf, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrycf), linecf);
	gtk_widget_show(label);
	gtk_widget_show(entrycf);
	gtk_box_pack_start (GTK_BOX (vbox), h1box, TRUE, TRUE, 0);
	gtk_widget_show(h1box);
	
	GtkWidget*h2box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("b3: ");
	GtkEntry*entrysf = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h2box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h2box), entrysf, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entrysf), linesf);
	gtk_widget_show(label);
	gtk_widget_show(entrysf);
	gtk_box_pack_start (GTK_BOX (vbox), h2box, TRUE, TRUE, 0);
	gtk_widget_show(h2box);
	
	GtkWidget*h3box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("b4: ");
	GtkEntry*entryif = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h3box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h3box), entryif, TRUE, TRUE, 0);
	gtk_entry_set_text (GTK_ENTRY (entryif), lineintf);
	gtk_widget_show(label);
	gtk_widget_show(entryif);
	gtk_box_pack_start (GTK_BOX (vbox), h3box, TRUE, TRUE, 0);
	gtk_widget_show(h3box);
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "entrycf", entrycf);
	g_object_set_data(G_OBJECT(btnsalvar), "entryzf", entryzf);
	g_object_set_data(G_OBJECT(btnsalvar), "entryif", entryif);
	g_object_set_data(G_OBJECT(btnsalvar), "entrysf", entrysf);
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_popup_mbr),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*atiende la salida de la popup del pc*/
static void atender_popup_alu( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");

	
	GtkEntry *entrycf = g_object_get_data (context_object, "entrycf");
	GtkEntry *entryzf = g_object_get_data (context_object, "entryzf");
	GtkEntry *entrysf = g_object_get_data (context_object, "entrysf");
	GtkEntry *entryif = g_object_get_data (context_object, "entryif");

	int16_t numerozf=valorValido(gtk_entry_get_text(entryzf));
	int16_t numerosf=valorValido(gtk_entry_get_text(entrysf));
	int16_t numerocf=valorValido(gtk_entry_get_text(entrycf));
	int16_t numeroif=valorValido(gtk_entry_get_text(entryif));
	/*
	if(numeroop>=0&&numerofuente>=0&&numerodestino>=0&&numerocuarto>=0&&numerodato>=0){
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	p.alu.registros.b1=numerozf;
	p.alu.registros.b2=numerocf;
	p.alu.registros.b3=numerosf;
	p.alu.registros.b4=numeroif;
	mostrarMensaje("Salvado Correctamente");
}



/*carga una afoc*/
static void loadASM( GtkWidget *widget,
                      gpointer   data )
{


	
	GtkWidget *popup_window;
	destruir=popup_window;
    popup_window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_title (GTK_WINDOW (popup_window), "Load ASM");
    gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW (popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW (popup_window), TRUE);
    gtk_widget_set_size_request (popup_window, 300, 150);
    gtk_window_set_transient_for(GTK_WINDOW (popup_window),GTK_WINDOW (window));
	gtk_window_set_modal(GTK_WINDOW (popup_window),TRUE);
    gtk_window_set_position (GTK_WINDOW (popup_window),GTK_WIN_POS_CENTER);
	
	
	GtkWidget*vbox=gtk_vbox_new(FALSE,0);
	GtkWidget*label=gtk_label_new("Load ASM: ");
	gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);
	
	GtkWidget*h5box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Path: ");
	GtkEntry*entrydato = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h5box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h5box), entrydato, TRUE, TRUE, 0);
	gtk_widget_show(label);
	gtk_widget_show(entrydato);
	gtk_box_pack_start (GTK_BOX (vbox), h5box, TRUE, TRUE, 0);
	gtk_widget_show(h5box);
	
	GtkWidget*h6box=gtk_hbox_new(FALSE,0);
	label=gtk_label_new("Pos en mem: ");
	GtkEntry*entrypos = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (h6box), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (h6box), entrypos, TRUE, TRUE, 0);
	gtk_widget_show(label);
	gtk_widget_show(entrypos);
	gtk_box_pack_start (GTK_BOX (vbox), h6box, TRUE, TRUE, 0);
	gtk_widget_show(h6box);
	
	
	GtkWidget*btnsalvar=gtk_button_new_with_label ("Salvar");
	GtkWidget*btnsalir=gtk_button_new_with_label ("Salir");
	g_object_set_data(G_OBJECT(btnsalvar), "entrydato", entrydato);
	g_object_set_data(G_OBJECT(btnsalvar), "entrypos", entrypos);
	g_signal_connect (btnsalvar, "clicked",
                        G_CALLBACK (atender_lasm),btnsalvar);
	g_signal_connect (btnsalir, "clicked",
                        G_CALLBACK (close_window),G_OBJECT (popup_window));
	
	
	gtk_box_pack_start (GTK_BOX (vbox), btnsalvar, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), btnsalir, TRUE, TRUE, 0);
	/*gtk_entry_set_text (GTK_ENTRY (entry), line);*/
	gtk_container_add (GTK_CONTAINER (popup_window), vbox);
	
	gtk_widget_show(btnsalvar);
	gtk_widget_show(btnsalir);
	
	gtk_widget_show(vbox);
	gtk_widget_show(popup_window);
	
}

/*termina de cargas la afoc*/
static void atender_lasm( GtkWidget *widget,
                      GObject *context_object )
{	
	g_print("atendiendo popup memoria\n");
	GtkEntry *entrydato = g_object_get_data (context_object, "entrydato");
	GtkEntry *entrypos = g_object_get_data (context_object, "entrypos");
	int pos=valorValido(gtk_entry_get_text(entrypos));
	char *path=strdup(gtk_entry_get_text(entrydato));
	char pathfinal[200];
	strcpy(pathfinal,path);
	parseMicro(pathfinal,pos);
	/*
	if(numeroop>=0&&numerofuente>=0&&numerodestino>=0&&numerocuarto>=0&&numerodato>=0){
		
	}
	else{
		mostrarMensaje("Entrada Invalida");
	}
	*/
	mostrarMensaje("Cargada Correctamente");
}













void close_window(GtkWidget *widget, gpointer window)
{
    gtk_widget_destroy(GTK_WIDGET(window));
}
/*muestra un mensaje al usuario*/
void mostrarMensaje(char*mensaje){
	GtkWidget*dialog = gtk_message_dialog_new (GTK_WINDOW(window),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  mensaje);
 gtk_window_set_gravity (GTK_WINDOW(dialog),
                             GDK_GRAVITY_NORTH_EAST);
 gtk_window_move (GTK_WINDOW(dialog),
                             0,0);
 gtk_dialog_run (GTK_DIALOG (dialog));
 gtk_window_set_keep_above(GTK_WINDOW(dialog), TRUE);
 gtk_widget_destroy (dialog); 
}


/*---------------------------------------*/

/*hace una lectura de la memoria*/
void lectura(){
	int pc=p.pc;
	p.ir.codop=memoria[pc].codop;
	p.ir.codf=memoria[pc].codf;
	p.ir.codd=memoria[pc].codd;
	p.ir.cuarto=memoria[pc].cuarto;
	p.ir.numero=memoria[pc].numero;
}
int fetch(GtkWidget *widget,
                      gpointer   tipo){
	if(ETAPA_FETCH==1){
		/*enviar mensaje a la consola*/
		g_print("Se realizo una lectura\n");
		g_print("Se realizao una lectura de la memoria\n");
		g_print("Se movieron cosasal BD\n");
		g_print("Se incremento elPC\n");
		writeEntry("En subciclo de busqueda");
		ETAPA_FETCH++;
	}
	if(ETAPA_FETCH==2){
		/*enviar mensaje a la consola*/
		lectura();
		writeEntry("En subciclo de decodificacion");
		writeEntry("En subciclo indirecto");
		incPC();
		ETAPA_FETCH++;
	}
	/*aunque hay dos etapas de fetch para el 3 y el 4 solo se tomara una porque se unificaran*/
	if(ETAPA_FETCH==3){
		if(tipo==0){
			/*ejecutar un solo paso de la microinstruccion*/
			g_print("cosas");
			char nombrearchivo[20];
			char *nombre="";
			char *nombre2="a";
			char adig1[5];
			char adig2[5];
			char adig3[5];
			/*char path[60]="datos//codigo//micro//";*/
			char path[200];
			sprintf(adig1, "%d", p.ir.codop);
			sprintf(adig2, "%d", p.ir.codd);
			sprintf(adig3, "%d", p.ir.codf);
			if(p.ir.codop==3 || p.ir.codop==3){
				if(p.ir.cuarto>=0){
					p.ir.cuarto--;
				}
			}
			char*dig1=strdup(adig1);
			char*dig2=strdup(adig2);
			char*dig3=strdup(adig3);
			strcat(dig1, "_");
			strcat(dig1, dig2);
			strcat(dig1, "_");
			strcat(dig1, dig3);
			strcat(dig1, ".txt");
			/*path="//";*/
			char pathm[200];
			strcpy(path,PATH_MICROS);
			strcat(path,"//");
			char novdig[200];
			strcpy(novdig,dig1);
			strcat(path,novdig);
			g_print(path);
			char*pathf=strdup(path);
			FILE*fp;
			
			fp = fopen(pathf, "r");
			if (fp == NULL){
				g_print("*sal%se",pathf);
				return 0;
			}
				
			char line[256];
			struct CeldaM temp;
			int cont=1;
			while (fgets(line, sizeof(line), fp)) {
				/*convertir la linea  a minuscula*/
				g_print("Se saca linea: %s",line);
				if(cont==NUMERO_LINEA){
					interpretMicro(line);
					g_print(line);
					if(fgets(line, sizeof(line), fp)){
						NUMERO_LINEA++;
						g_print("Mas Linea: %s %d\n",line,NUMERO_LINEA);
					}
					else{
						g_print("Se acabo la instruccion");
						NUMERO_LINEA=1;
						ETAPA_FETCH++;
					}
					writeEntry("Microinstruccion ejecutada");
					break;
				}
				cont++;
			}
			fclose(fp);
		}
		else{/*ejecutar toda la instruccion de asm*/
			g_print("cosas");
			char nombrearchivo[20];
			char *nombre="";
			char *nombre2="a";
			char adig1[5];
			char adig2[5];
			char adig3[5];
			/*char path[60]="datos//codigo//micro//";*/
			char path[200];
			sprintf(adig1, "%d", p.ir.codop);
			sprintf(adig2, "%d", p.ir.codd);
			sprintf(adig3, "%d", p.ir.codf);
			char*dig1=strdup(adig1);
			char*dig2=strdup(adig2);
			char*dig3=strdup(adig3);
			strcat(dig1, "_");
			strcat(dig1, dig2);
			strcat(dig1, "_");
			strcat(dig1, dig3);
			strcat(dig1, ".txt");
			/*path="//";*/
			char pathm[200];
			strcpy(path,PATH_MICROS);
			strcat(path,"//");
			char novdig[200];
			strcpy(novdig,dig1);
			strcat(path,novdig);
			g_print(path);
			char*pathf=strdup(path);
			FILE*fp;
			
			fp = fopen(pathf, "r");
			if (fp == NULL){
				g_print("*sale");
				return 0;
			}
				
			char line[256];
			struct CeldaM temp;
			int cont=1;
			while (fgets(line, sizeof(line), fp)) {
				/*convertir la linea  a minuscula*/
				if(cont>=NUMERO_LINEA){
					g_print("Se saca linea: %s",line);
					interpretMicro(line);
					g_print(line);
					NUMERO_LINEA++;
					writeEntry("Microinstruccion ejecutada...");
				}
				cont++;

			}
			fclose(fp);
			g_print("Se acabo la instruccion");
			NUMERO_LINEA=1;
			ETAPA_FETCH++;
			
			
		}
	}
	if(ETAPA_FETCH==4){
		writeEntry("En subciclo antes interrupciones");
		writeEntry("En subciclo de interrupciones...");
		g_print("%FLAGS: d",p.flags.intf);
		if(p.flags.intf!=0){
			mostrarMensaje("Atendiendo Interrupcion");
		}
		ETAPA_FETCH=1;
		
	}
	return 1;
}
void writeEntry(char*texto){
	gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, texto, -1);
	gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, "\n", -1);
}
/*limpia todos los datos de la memoria y de el procesador y registros*/
void clearValores(void){
	int i=0;
	/*limpiar la memoria*/
	for(i=0;i<256;i++){
		memoria[i].numero=0;
		memoria[i].codd=0;
		memoria[i].codf=0;
		memoria[i].codop=0;
		memoria[i].cuarto=0;
	}
	/*limpiar el procesador*/
	p.mar=0;
	p.ir.codop=0;
	p.ir.codd=0;
	p.ir.codf=0;
	p.ir.cuarto=0;
	p.ir.numero=0;
	
	p.mbr.codop=0;
	p.mbr.codd=0;
	p.mbr.codf=0;
	p.mbr.cuarto=0;
	p.mbr.numero=0;
	
	p.pc=0;
	p.bd=0;
	
	p.registros.a.h=0;
	p.registros.a.l=0;
	p.registros.b.h=0;
	p.registros.b.l=0;
	p.registros.c.h=0;
	p.registros.c.l=0;
	p.registros.d.h=0;
	p.registros.d.l=0;
	
	p.flags.zf=0;
	p.flags.intf=0;
	p.flags.cf=0;
	p.flags.sf=0;
	
	p.alu.registros.b1=0;
	p.alu.registros.b2=0;
	p.alu.registros.b3=0;
	p.alu.registros.b4=0;
	
	ETAPA_FETCH=1;
	NUMERO_LINEA=1;
	PATH_MICROS="datos//codigo//micro";
	cargaInstrucciones();
	mostrarMensaje("Registros borrados");
}
