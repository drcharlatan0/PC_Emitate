#include <iostream>
#include <string>
//#define DEBUG

//version 3

class Matherboart {
	enum  PCstate {
		ON = 0,
		OFF = 1,
		ACTIVE_COMMAND,//2
		NOT_ACTIVE_COMMAND,//3
		BIOS,//4
		ERROR_CPU,//5
		ERROR_RAM,//6
		ERROR_BIOS,//7
		PREPARE//8
	};
	int code_cpu;
	 std::string name_proccesor;
	 int Temperature_Cpu;
	int model_cpu;
	 float Frequency_Cpu;
	 float Ram_frequency;
	int State_now;
public:
	Matherboart(int code_cpu, int model_cpu) {
		State_now = PREPARE;
		this->code_cpu = code_cpu;
		this->model_cpu = model_cpu;
	}
	int operator()() {//Prepare matherboart 
		State_now = PREPARE;
		#ifdef DEBUG
		std::cout << "Status: " << State_now << std::endl; 
		#endif 
		if (code_cpu == -1) {
			State_now = ERROR_CPU;// error cpu (cpu n/a)
		#ifdef DEBUG
		std::cout << "Status: " << State_now << std::endl; 
		#endif 
		}
		if (code_cpu == 1) {
			name_proccesor = "Athlon";
		#ifdef DEBUG
		std::cout << "Set proccesor name: " << name_proccesor << std::endl; 
		#endif 
		}
		else if (code_cpu == 2) {
			name_proccesor = "Phenom";
		#ifdef DEBUG
		std::cout << "Set proccesor name: " << name_proccesor << std::endl; 
		#endif 
		}
		//Set Frequency
		if (code_cpu == 1 && model_cpu == 3400) {
			Frequency_Cpu = 2.300;
			Ram_frequency = 1333;
			#ifdef DEBUG
			std::cout << "set Frequency CPU: " << Frequency_Cpu << std::endl << "set Frequency RAM: " << Ram_frequency <<std::endl; 
			#endif
		}
		else if (code_cpu == 1 && model_cpu == 3440) {
			Frequency_Cpu = 2.400;
			Ram_frequency = 1333;
			#ifdef DEBUG
			std::cout << "set Frequency CPU: " << Frequency_Cpu << std::endl << "set Frequency RAM: " << Ram_frequency <<std::endl; 
			#endif
		}
		else if (code_cpu == 1 && model_cpu == 3480) {
			Frequency_Cpu = 2.500;
			Ram_frequency = 1600;
			#ifdef DEBUG
			std::cout << "set Frequency CPU: " << Frequency_Cpu << std::endl << "set Frequency RAM: " << Ram_frequency <<std::endl; 
			#endif
		}
		else if (code_cpu == 2 && model_cpu == 3400) {
			Frequency_Cpu = 2.500;
			Ram_frequency = 1600;
			#ifdef DEBUG
			std::cout << "set Frequency CPU: " << Frequency_Cpu << std::endl << "set Frequency RAM: " << Ram_frequency <<std::endl; 
			#endif
		}
		else if (code_cpu == 2 && model_cpu == 3440) {
			Frequency_Cpu = 2.700;
			Ram_frequency = 1600;
			#ifdef DEBUG
			std::cout << "set Frequency CPU: " << Frequency_Cpu << std::endl << "set Frequency RAM: " << Ram_frequency <<std::endl; 
			#endif
		}
		else if (code_cpu == 2 && model_cpu == 3480) {
			Frequency_Cpu = 3.000;
			Ram_frequency = 1600;
			#ifdef DEBUG
			std::cout << "set Frequency CPU: " << Frequency_Cpu << std::endl << "set Frequency RAM: " << Ram_frequency <<std::endl; 
			#endif
		}
		else{
			State_now = ERROR_CPU;
			#ifdef DEBUG
			std::cout << "set Frequency CPU: " << Frequency_Cpu << std::endl << "set Frequency RAM: " << Ram_frequency <<std::endl; 
			#endif
			}// Error cpu n/a 
		check();
		#ifdef DEBUG
		std::cout << "call check function" <<std::endl;
		#endif 
		// Start or not
		if (State_now != ON) {
			return -1;
			#ifdef DEBUG
			std::cout << "Boart not start" << std::endl; 
			#endif 
		}
		else if (State_now == ON) {
			return 0;
			#ifdef DEBUG
			std::cout << "End matherboart func"<<std::endl;
			#endif 
		}
		return 404;
	}

	void GET_Temperature_Cpu(int *Temperature) {// use ptr*
		if (State_now == ACTIVE_COMMAND) {
			*Temperature = 15 + std::rand() % 60;
			#ifdef DEBUG
			std::cout << "Temperature ready wich active command" << std::endl;
			#endif
		}
		else if (State_now == NOT_ACTIVE_COMMAND) {
			*Temperature = 15 + std::rand() % 30;
			#ifdef DEBUG
			std::cout << "Temperature ready wich no active command" << std::endl;
			#endif
		}
	}
	//GET
	std::string GET_NAME_CPU() {
		#ifdef DEBUG
		std::cout << "Get name CPU " << std::endl; 
		#endif 
		return name_proccesor;
	}
	
	int GET_MODEL_CPU() {
		#ifdef DEBUG
		std::cout << "Get model cpu " << std::endl; 
		#endif 
		return model_cpu;
	}

	float GET_Frequency_CPU() {
		#ifdef DEBUG
		std::cout << "Get frequency CPU " << std::endl; 
		#endif 
		return Frequency_Cpu;
	}

	float GET_Frequence_RAM() {
		#ifdef DEBUG
		std::cout << "Get Frequency Ram " << std::endl; 
		#endif 
		return Ram_frequency;
	}
	int check() {
		#ifdef DEBUG
		std::cout << "Start check function" << std::endl;
		#endif
		if (Ram_frequency < 0) {
			#ifdef DEBUG
			std::cout << "ERROR: RAM FREQUENCY < 0 " << std::endl;
			#endif 
			State_now = ERROR_RAM;
			return -2;
		}
		else if (Ram_frequency > 1700 + std::rand() % 2000) {
			#ifdef DEBUG
			std::cout << "ERROR: RAM FREQUENCY" << std::endl;
			#endif 
			State_now = ERROR_RAM;
			State_now = ERROR_RAM;
			return -2;
		}
		if (Frequency_Cpu < 0 || Frequency_Cpu  > 3.000) {
			#ifdef DEBUG
			std::cout << "ERROR: CPU FREQUENCY" <<std::endl;
			#endif
			State_now = ERROR_CPU;
			return -1;
		}
		if (State_now != ERROR_CPU && State_now != ERROR_RAM && State_now != ERROR_BIOS) {
			#ifdef DEBUG
			std::cout << "OK \nend function" << std::endl;
			#endif 
			State_now = ON;
			return 0;
		}
			#ifdef DEBUG
			std::cout << "OK \nend function" << std::endl;
			#endif 
		return 404;
		
	}

	void SET_STATUS(int numb_state) {
		#ifdef DEBUG
		std::cout << "start SET_STATUS\n";
		#endif
		this->State_now = numb_state;
	}
	void MIT(){// overdrive
		#ifdef DEBUG
		std::cout << "start MIT Function";
		#endif 
		State_now = BIOS;
		#ifdef DEBUG 
		std::cout << "State: " << State_now << std::endl;
		#endif 
		std::cout<<"Welcom MIT state\n" << "1.RAM\n2.CPU\nEnter chose:";
		int chose = 0;
		std::cin >> chose;
		#ifdef DEBUG
		std::cout << "write chose \n";
		#endif
		std::cout << std::endl;
		if (chose == 2){
			#ifdef DEBUG
			std::cout << "call function CPU_OVERDRIVE\n";
			#endif
			CPU_OVERDRIVE();
			}
		else if (chose == 1){
			#ifdef DEBUG
			std::cout << "call function RAM_OVERDRIVE\n";
			#endif
			RAM_OVERDRIVE();
			}
		else {
			#ifdef DEBUG
			std::cout << "ERROR";
			#endif  
			State_now = ERROR_BIOS;
			}
		}
		
		void RAM_OVERDRIVE(){
			#ifdef DEBUG
			std::cout << "start RAM_OVERDRIVE\n";
			#endif
			std::cout << "Enter RAM frequency(now frequency "<< Ram_frequency << "):";
			std::cin >> Ram_frequency;
			#ifdef DEBUG 
			std::cout << "Write RAM_FREQUENCY\n";
			#endif 
			std::cout << std::endl;
			int random = 1600 + std::rand() % 2000;
			#ifdef DEBUG
			std::cout << "random set\n";
			#endif 
			if (Ram_frequency > random ){
				#ifdef DEBUG
				std::cout << "ERROR:RAM\nRAM FREQUENCY:800\n";
				#endif
				State_now = ERROR_RAM;
				Ram_frequency = 800;	
				}
			}
		void CPU_OVERDRIVE(){
				#ifdef DEBUG
				std::cout <<"start CPU_OVERDRIVE";
				#endif
			std::cout << "Enter CPU Frequency (now Frequency " <<Frequency_Cpu << ")";
			std::cin >> Frequency_Cpu;
			#ifdef DEBUG
			std::cout << "write Frequency CPU\n";
			#endif
			std::cout << std::endl;
			int random = 2500 + std::rand() % 3100;
			if (Frequency_Cpu > random){
				#ifdef DEBUG
				std::cout << "ERROR:CPU";
				#endif
				State_now = ERROR_CPU;	
				}
				#ifdef DEBUG
				std::cout <<"end funcion \n";
				#endif
			}
};

