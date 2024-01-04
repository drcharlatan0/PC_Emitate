#include <iostream>
#include <string>
#include <clocale>
#include "matherboart.h"
#include "oc.h"
//#define test

//plan.txt
//Прописать логику взаимодействия ос с материнкой 
// Version 3




void set_data_cpu(int *code_cpu, int *model_cpu) {
	std::string tmp;
	std::cout << "Enter name proccessor:";
	std::cin >> tmp;
	std::cout << std::endl;
	std::cout << "Enter model cpu:";
	std::cin >> *model_cpu;
	std::cout << std::endl;
	//#ifdef test
	//*code_cpu = 2;
	//*model_cpu = 3440;
	//#endif
	if (tmp.empty()) {
		std:: cout << "Error\n Cpu n/a";
		*code_cpu = -1;
	}
	if (tmp.compare("Athlon") == 0) {
		*code_cpu = 1;
	}
	else if (tmp.compare("athlon") == 0) {
		*code_cpu = 1;
	}
	if (tmp.compare("Phenom") == 0) {
		*code_cpu = 2;
	}
	else if (tmp.compare("phenom") == 0) {
		*code_cpu = 2;
	}
	else {
		*code_cpu = -1;
		}
	#ifdef test
	*code_cpu = 2;
	*model_cpu = 3440;
	#endif
}

int main() {
	setlocale(LC_ALL,"ru");
	int code_cpu = 0;
	int model_cpu = 0;
	set_data_cpu(&code_cpu, &model_cpu);
	Matherboart mainboart(code_cpu, model_cpu);
	if (mainboart() == -1) {
		std::cout << "Matherboart not starting";
		return -1;
	}
	OC oc(mainboart.GET_NAME_CPU(),mainboart.GET_Frequency_CPU(),mainboart.GET_Frequence_RAM());
	bool exit = false;
	int return_oc = 0;
		while (exit != true){
		return_oc = oc();
		if (return_oc == 1){
		mainboart.MIT();
		return_oc = 0;
	}
		if (mainboart.check()!= 0){
			std::cout << "Fatal error" << std::endl;
			break;
			}
		else if (mainboart.check() == 0){oc.rewrite_info(mainboart.GET_NAME_CPU(),mainboart.GET_Frequency_CPU(),mainboart.GET_Frequence_RAM());}
		if (return_oc == 52){
			exit = true;
			}			
	}
	return 0;
}
