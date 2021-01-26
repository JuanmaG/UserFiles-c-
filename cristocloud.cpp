#include <iostream>
#include <string.h>
#include <stdlib.h> 

using namespace std;
//DEFINICION DE STRUCTS
struct Fichero{
	string ruta;
	string tipo;
	unsigned long int tamanio;//se va a guardar en bytes
};

struct Usuario{
	string login;
	string nombre;
	string apellido;
	Fichero *v_ficherosusuario;//tipo personasv2
	int DIM_ficherosusuario;
	int total_ficheros;
	string perfil;//ADMIN O USER
};

struct TablaUsuarios{
	Usuario **punteroapuntero;
	int total_tuplas;//reserva siempre exacta
};

/*******************************************************/
/******************SETS Y GETS FICHERO******************/

void setRuta(Fichero *unFichero, string nueva_ruta){
	 unFichero->ruta=nueva_ruta;
}

void setTipo(Fichero *unFichero, string nuevo_tipo){
	unFichero->tipo=nuevo_tipo;
}

void setTamanio(Fichero *unFichero, unsigned long int nuevo_tamanio){
	unFichero->tamanio=nuevo_tamanio;		
}

string getRuta(Fichero *unFichero){
	return unFichero->ruta;
}

string getTipo(Fichero *unFichero){
	return unFichero->tipo;
}
unsigned long int getTamanio(Fichero *unFichero){
	return unFichero->tamanio;
}

/*******************************************************/
/******************SETS Y GETS USUARIO******************/

void setLogin(Usuario *unUsuario, string nuevo_login){
	unUsuario->login=nuevo_login;
}

void setNombre(Usuario *unUsuario, string nuevo_nombre){
	unUsuario->nombre=nuevo_nombre;
}

void setApellido(Usuario *unUsuario, string nuevo_apellido){
	unUsuario->apellido=nuevo_apellido;
}

void setDIMficherosUsuario(Usuario *unUsuario,int nueva_dim){
	unUsuario->DIM_ficherosusuario=nueva_dim;
}

void setTotalFicheros(Usuario *unUsuario,int nuevo_total){
	unUsuario->total_ficheros=nuevo_total;
}

void setPerfil(Usuario *unUsuario, string nuevo_perfil){
	unUsuario->perfil=nuevo_perfil;
}

string getLogin(Usuario *unUsuario){
	return unUsuario->login;
}

string getNombre(Usuario *unUsuario){
	return unUsuario->nombre;
}

string getApellido(Usuario *unUsuario){
	return unUsuario->apellido;
}

Fichero getFichero(Usuario *unUsuario, int posicion){
	return unUsuario->v_ficherosusuario[posicion];
}

int getDIMficherosUsuario(Usuario *unUsuario){
	return unUsuario->DIM_ficherosusuario;
}

int getTotalFicheros(Usuario *unUsuario){
	return unUsuario->total_ficheros;
}

string getPerfil(Usuario *unUsuario){
	return unUsuario->perfil;
}
/*******************************************************/
/******************SETS Y GETS TABLAUSUARIOS************/
void setTotalTuplas(TablaUsuarios *tabla,int nuevo_total){
	tabla->total_tuplas=nuevo_total;
}

Usuario* getUser(TablaUsuarios *tabla,int posicion){
	return tabla->punteroapuntero[posicion];
}

int getTotalTuplas(TablaUsuarios *tabla){
	return tabla->total_tuplas;
}
/*******************************************************/
/***************FUNCIONALIDADES*************************/

void printUser(Usuario *unUsuario, int pos){
	cout <<"*******************USER:" << pos << "*******************"<<endl;
	cout <<"*Login: " << getLogin(unUsuario) << endl;
	cout <<"*Nombre: " << getNombre(unUsuario) << endl;
	cout <<"*Apellido: " << getApellido(unUsuario) << endl;
	cout <<"*DIM: " << getDIMficherosUsuario(unUsuario)<< endl;
	cout <<"*Total de ficheros: " << getTotalFicheros(unUsuario) << endl;
	cout <<"*Tipo de Perfil: " << getPerfil(unUsuario) << endl;
	cout <<"******************************************"<<endl;
}

void printFile(Fichero *unFichero,int pos){
	cout <<"*******************FILE: " << pos << "*******************"<<endl;
	cout << "Ruta: " << getRuta(unFichero) << endl;
	cout << "Tipo: " << getTipo(unFichero) << endl;
	cout << "Tama単o: " << getTamanio(unFichero) << endl;
	cout <<"************************************************"<<endl;
}

void printUserFiles(Usuario *user,int total_files){
	for (int i=0;i<getTotalFicheros(user);i++){
		printFile(&(user->v_ficherosusuario[i]),i);
	}

}
/**
*@brief modulo para insertar un fichero en el vector de ficheros de un usuario y que comprueba si es posible insertarlo,
si no es posible hace una llamada a un modulo para redimensionar y permitir la insercion.
**/
void redimensionarVficheros(Usuario *unUsuario,Fichero *unFichero,int posicion){
	cout << "entra en redimension" << endl;

	Fichero *aux;
	aux=new Fichero[posicion*2];
	for (int i = 0;i<posicion;i++){
		aux[i]=unUsuario->v_ficherosusuario[i];
	}
	delete []unUsuario->v_ficherosusuario;
	setDIMficherosUsuario(unUsuario,(posicion)*2);
	unUsuario->v_ficherosusuario=aux;
	
	cout << "introduce en redimension" << endl;
	unUsuario->v_ficherosusuario[posicion] = *unFichero;
	setTotalFicheros(unUsuario,getTotalFicheros(unUsuario)+1);

}
/*
*@brief modulo que redimensiona el tama単o del vector de punteros a usuario para que podamos introducir
*un usuario
*/
void redimensionarPunteroaPuntero(TablaUsuarios *tabla){
	cout << "entra en redimension de v usuarios" << endl;
	Usuario **aux;
	aux = new Usuario*[getTotalTuplas(tabla)+1];
	for (int i = 0;i<getTotalTuplas(tabla);i++){
		aux[i]=tabla->punteroapuntero[i];
	}
	for (int i = 0;i<getTotalTuplas(tabla);i++){
		tabla->punteroapuntero[i]=0;
	}
	delete []tabla->punteroapuntero;
	tabla->punteroapuntero=aux;
}
/*
*@brief modulo que introduce ficheros en el vector de ficheros de un usuario si hay espacio disponible,
*si no hace una llamadada para pedir mas espacio
*@param Usuario *unUsuario, es el usuario al que se le introducira el fichero
*@param Fichero *unFichero es el fichero a introducir
*@param int posicion es la posicion que ocupara el fichero en el vector
*/
void setVficheros(Usuario *unUsuario, Fichero *unFichero, int posicion){
	
	if (posicion<getDIMficherosUsuario(unUsuario)){	
		cout << "entra" << endl;
		unUsuario->v_ficherosusuario[posicion] = *unFichero;
		setTotalFicheros(unUsuario,getTotalFicheros(unUsuario)+1);
		cout << "Fichero: " << getTotalFicheros(unUsuario) << " introducido con exito" << endl;
	
	}
	else {
		cout << "redimension" << endl;
		redimensionarVficheros(unUsuario,unFichero, posicion);
	}
}
/*
*@brief modulo que permite la creacion de ficheros en nuestro programa
*/
Fichero* createFile(string ruta, string tipo, unsigned long int tamanio){
	Fichero *file = new Fichero;
	if (file==0){
		cerr << " Abortando ejecucion " << endl;
		exit(-1);
	}
	setRuta(file,ruta);
	setTipo(file, tipo);
	setTamanio(file, tamanio);
	
	return file;
}
/*
*@brief modulo que nos crea 4 ficheros y los introduce al vector de ficheros principal para usar por defecto en nuestro programa
*/
void ficherosDefecto(Fichero *file,int &total_files){
	file[0]=*createFile("/home/user/video.mp4",".Mp4",124000);
	file[1]=*createFile("/home/user/image.jpg",".jpeg",1024);
	file[2]=*createFile("/home/user/movie.avi",".avi",12400);
	file[3]=*createFile("/home/user/exec.exe",".exe",11034);
	total_files=4;
	

}
/*
*@brief modulo que crea un usuario posteriormente a introducir sus datos
*/
Usuario* createUser(string login,string nombre,string apellido, int DIM_ficherosusuario,int total_ficheros,string perfil){
	Usuario *user = new Usuario;	
		
	setLogin(user,login);
	setNombre(user,nombre);
	setApellido(user,apellido);
	setDIMficherosUsuario(user,DIM_ficherosusuario);
	setTotalFicheros(user,total_ficheros);
	setPerfil(user,perfil);
	user->v_ficherosusuario=new Fichero[DIM_ficherosusuario];
	//setVficheros(user,a,total_ficheros);

	return user;
}
/*
*@brief modulo que nos crea y a単ade a la tabla los usuarios por defecto
*@param TablaUsuarios *tabla, es la tabla de usuarios
*/
void usuariosPorDefecto(TablaUsuarios *tabla){
	tabla->punteroapuntero[0]=createUser("@jaime","jaime","matas",10,0,"super-admin");
	tabla->punteroapuntero[1]=createUser("@juanma","juan manuel","garrido",10,0,"super-admin");
	tabla->punteroapuntero[2]=createUser("@paco","fran","matias",4,0,"admin");
	tabla->punteroapuntero[3]=createUser("@eusebio","anacleto","bonifacio",2,0,"user");
	tabla->punteroapuntero[4]=createUser("@baguette","pan","frances",2,0,"user");
	tabla->punteroapuntero[5]=createUser("@jose","pepe","alcala",0,0,"tryout");
}
/*
*@brief modulo que crea la tabla de usuarios con la que trabajaremos todo el programa 
*que ademas hace una llamada a la creacion de usuarios por defecto
*@param TablaUsuarios *tabla, es la tabla de usuarios
*/
void createTable(TablaUsuarios *tabla){
	setTotalTuplas(tabla,6);
	tabla->punteroapuntero=new Usuario*[6];
	if(tabla->punteroapuntero==0){
		cout << "abortando" << endl;
	}
	usuariosPorDefecto(tabla);
	
}
/*
*@brief modulo que nos permite la insercion de los datos de un fichero mediante teclado
*y una vez introducidos hace una llamada para crear un fichero con los datos introducidos
*/
void fileInsertion(Fichero *files,int &total_files){
	string ruta,tipo;
	unsigned long int tamanio;

	cout << "Introduzca la ruta: " << endl;
	cin>>ruta;
	cout << "introduzca el tipo: " << endl;
	cin>>tipo;
	cout << "Introduzca el tama単o: " << endl;
	cin>>tamanio;
	files[total_files]=*createFile(ruta,tipo,tamanio);
	total_files++;
	cout << "Total de ficheros: " << total_files << endl;

}
/*
*@brief modulo que nos permite la insercion de los datos de un usuario mediante teclado
*y una vez introducidos hace una llamada para crear un usuario con los datos introducidos
*/
Usuario* userInsertion(Usuario *usuarios){
	string login,nombre,apellido,perfil;
	int DIM_ficherosusuario,total_ficheros;

	cout << "Introduzca el login: " << endl;
	cin>>login;
	cout << "introduzca el nombre: " << endl;
	cin>>nombre;
	cout << "Introduzca el apellido: " << endl;
	cin>>apellido;
	cout << "Introduzca la DIM: " << endl;
	cin>>DIM_ficherosusuario;
	cout << "Introduzca el total de ficheros: " << endl;
	cin>>total_ficheros;
	cout << "Introduzca el tipo de perfil: " << endl;
	cin>>perfil;
	usuarios=createUser(login,nombre,apellido,DIM_ficherosusuario,total_ficheros,perfil);

	return usuarios;

}
/**
*@brief modulo para insertar un fichero en el vector de usuarios de la tabla y que comprueba si es posible insertarlo,
si no es posible hace una llamada a un modulo para redimensionar y permitir la insercion.
**/
void setPunteroApuntero(TablaUsuarios *tabla,Usuario *unUsuario,int posicion){
	if (posicion<getTotalTuplas(tabla)){		
		tabla->punteroapuntero[posicion]=userInsertion(unUsuario);
		setTotalTuplas(tabla,getTotalTuplas(tabla)+1);
	}
	else {
		redimensionarPunteroaPuntero(tabla);
		tabla->punteroapuntero[posicion]=userInsertion(unUsuario);
		setTotalTuplas(tabla,getTotalTuplas(tabla)+1);
	}
}
/*
*@brief modulo que reordena el vector de ficheros despues del borrado de uno de estos.
*@param Usuario *user, es el usuario al que pertenece el fichero
*@param int posicion, es la posicion que ocupa el fichero que fue borrado en el vector de ficheros del usuario
*/
void reordenarVficheros(Usuario *user,int posicion){
	bool actualizado=false;
	for(int i=0;i<getTotalFicheros(user);i++){
		if (i==posicion){
			user->v_ficherosusuario[posicion]=user->v_ficherosusuario[posicion+1];
			actualizado=true;
			i++;	
		}
		else if(actualizado=true){
			user->v_ficherosusuario[i]=user->v_ficherosusuario[i+1];
		}
	}
}
/*
*@brief modulo que elimina un fichero asociado a un usuario
*@param Usuario *user, usuario al que pertenece el fichero
*@param int posicion, posicion que ocupa el fichero en el vector de ficheros
*/
void dropFileFromUser(Usuario *user,int posicion){
	setRuta(&(user->v_ficherosusuario[posicion]),"");
	setTipo(&(user->v_ficherosusuario[posicion]), "");
	setTamanio(&(user->v_ficherosusuario[posicion]), 0);
	cout << "Fichero borrado con exito" << endl;
	reordenarVficheros(user,posicion);
}
/*
*@brief modulo que reordena la tabla de usuarios despues de eliminar uno de estos
*@param TablaUsuarios *tabla,es la tabla de usuarios
*@param int posicion, representa al usuario eliminado
*/
void reordenarTabla(TablaUsuarios *tabla,int posicion){
	bool actualizado=false;
	for (int i=0;i<getTotalTuplas(tabla);i++){
		if (i==posicion){
			tabla->punteroapuntero[i]=tabla->punteroapuntero[i+1];
			actualizado=true;
			i++;	
		}
		else if (actualizado==true){
			tabla->punteroapuntero[i]=tabla->punteroapuntero[i+1];
			cout << "Tabla reordenada" << endl;
		}
	}
}
/*
*@brief modulo que elimina un usuario de la tabla de usuarios
*@param Usuario *user es el usuario a eliminar
*@param TablaUsuarios *tabla es la tabla de usuarios
*@param int posicion es la posicion que ocupa el usuario en la tabla
*/
void deleteUser(Usuario *user,int posicion,TablaUsuarios *tabla){
	setLogin(user,"");
	setNombre(user,"");
	setApellido(user,"");
	setDIMficherosUsuario(user,0);
	setTotalFicheros(user,0);
	setPerfil(user,"");
	delete []user->v_ficherosusuario;
	reordenarTabla(tabla,posicion);
	cout << "Usuario borrado con exito" << endl;
	
}
/*
*@brief modulo que busca un usuario usando el atributo login
*@param TablaUsuarios *tabla
*@param string busqueda es la cadena de texto que se busca
*/	
void buscarUsuario(TablaUsuarios *tabla,string busqueda){
	bool encontrado=false;
	for (int i=0;i<getTotalTuplas(tabla);i++){
		if (getLogin(tabla->punteroapuntero[i])==busqueda){
			cout << "usuario encontrado" << endl;
			printUser(tabla->punteroapuntero[i],i);
			encontrado=true;
		}
	}
	if (encontrado==false){
		cout << "usuario no encontrado" << endl;
	}
}
void borrarTabla(TablaUsuarios *tabla){
	
	
	
	setTotalTuplas(tabla,0);
	
	delete []tabla->punteroapuntero;
	
	delete tabla;
}
int main(){

	int opcion=0, DIM_ficherosusuario, total_ficheros,seleccion_fichero,seleccion_usuario;
	string login,nombre,apellido,perfil;

	bool tabla_creada=false,final=false;

	TablaUsuarios *tabla=0;
	tabla=new TablaUsuarios;
	if (tabla==0){
		cerr << " Abortando ejecucion " << endl;
		exit(-1);
	}
	Usuario *paco=0;
	int total_files=0;

	paco=new Usuario;
	if (paco==0){
		cerr << " Abortando ejecucion " << endl;
		exit(-1);
	}
	Fichero *files=0;
	files=new Fichero[100];
	
		

	if (files==0){
		cerr << " Abortando ejecucion " << endl;
		exit(-1);
	}
	do {
	if (tabla_creada==false){
		cout << "Para poder usar el menu debe crear la tabla pulsando '0'" << endl;
	}
		cout << "Pulse '1' para crear Fichero." << endl;
		cout << "Pulse '2' para crear un usuario." << endl;
		cout << "Pulse '3' para imprimir los ficheros disponibles." << endl; 
		cout << "Pulse '4' para ver la tabla de usuarios." << endl; 
		cout << "Pulse '5' para introducir fichero en un usuario." << endl; 
		cout << "Pulse '6' para imprimir los ficheros de un usuario." << endl;
		cout << "Pulse '7' para borrar un fichero de un usuario." << endl;
		cout << "Pulse '8' para borrar un usuario de la tabla." << endl;	
		cout << "Pulse '9' para borrar la tabla." << endl;
		cout << "pulse '10' para buscar un usuario por atributo login exacto" << endl;
		cout << "pulse '11' para liberar memoria y finalizar el programa" << endl;
		cin>>opcion;
		switch(opcion){
			case 0:
				tabla_creada=true;
				createTable(tabla);
				ficherosDefecto(files,total_files);
			break;
			case 1:
			if (tabla_creada==true)
				fileInsertion(files,total_files);
			break;
			case 2:	
			if (tabla_creada==true)
				setPunteroApuntero(tabla,paco,getTotalTuplas(tabla));
			break;
			case 3: 
			if (tabla_creada==true){
				system("clear");
				if (total_files==0){
					cout << "No hay ficheros disponibles" << endl;	
				}
				else {
					for (int i=0;i<total_files;i++){				
						printFile(&(files[i]),i);
					}
				}
			}
			break;
			case 4:
			if (tabla_creada==true){
				system("clear");
				for (int i=0;i<getTotalTuplas(tabla);i++){				
					printUser(tabla->punteroapuntero[i],i);
				}
			}
			break;
			case 5:
			if (tabla_creada==true){
				system("clear");
				cout << " elija uno de los ficheros " << endl;
				for (int i=0;i<total_files;i++){			
					printFile(&(files[i]),i);
				}				
				cin >> seleccion_fichero;
				system("clear");
				cout << "Elija un usuario " << endl;
				for (int i=0;i<getTotalTuplas(tabla);i++){				
					printUser(tabla->punteroapuntero[i],i);;
				}
				cin >> seleccion_usuario;

					setVficheros(getUser(tabla,seleccion_usuario),&(files[seleccion_fichero]),getTotalFicheros(tabla->punteroapuntero[seleccion_usuario]));
				system("clear");
			}
			break;
			case 6:
			if (tabla_creada==true){
				system("clear");
				cout << "Elija un usuario " << endl;
				for (int i=0;i<getTotalTuplas(tabla);i++){				
					printUser(tabla->punteroapuntero[i],i);;
				}
				cin >> seleccion_usuario;
			printUserFiles(getUser(tabla,seleccion_usuario),total_files);	
			}
			break;
			case 7:
			system("clear");
			if (tabla_creada==true){
				cout << "Elija el usuario del cual quiere borrar el fichero" << endl;
		
				for (int i=0;i<getTotalTuplas(tabla);i++){				
					printUser(tabla->punteroapuntero[i],i);;
				}
				cin >> seleccion_usuario;
				printUserFiles(getUser(tabla,seleccion_usuario),total_files);
				cout << "Elija el fichero" << endl;
						
				cin >> seleccion_fichero;
				dropFileFromUser(getUser(tabla,seleccion_usuario),seleccion_fichero);
				setTotalFicheros(getUser(tabla,seleccion_usuario),getTotalFicheros(getUser(tabla,seleccion_usuario))-1);
			}
			break;
			case 8:
			system("clear");
			if (tabla_creada==true){
				cout << "Elija el usuario que quiere borrar" << endl;
				for (int i=0;i<getTotalTuplas(tabla);i++){				
					printUser(tabla->punteroapuntero[i],i);;
				}
				cin >> seleccion_usuario;
				deleteUser(getUser(tabla,seleccion_usuario),seleccion_usuario,tabla);
				setTotalTuplas(tabla,getTotalTuplas(tabla)-1);
			}
			break;
			case 9:
			system("clear");
			if (tabla_creada==true){
				borrarTabla(tabla);
				tabla_creada=false;
			}
			break;
			case 10:
			system("clear");
			if (tabla_creada==true){
				cout << "introduzca el login que quiera encontrar" << endl;
				cin >> login;
				buscarUsuario(tabla,login);
			}
			break;
			case 11:
			if (tabla_creada==true){
				delete paco;
				delete []files;
				borrarTabla(tabla);
				final=true;
			}
			break;
		}
	} while ((opcion==0 || opcion==1 || opcion == 2 || opcion ==3 || opcion==4 || opcion == 5 || opcion == 6 || opcion == 7 || opcion==8 || opcion==9 || opcion==10 || opcion ==11) && final==false);
	
	

	
	
}
