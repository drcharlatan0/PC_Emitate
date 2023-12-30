#include <iostream>
#include <string>
#include <clocale>

// Beta version 1

class OC  {
	enum STATE_OC {
		START = 1,
		WAIT,//2
		WORK,//3
		ERROR,//4
		CRASH,//5
		SHUTDOWN,//6
	};
	int filled_state_log = 0;
	int log_state[400];
	std::string NAME_CPU;
	float Frequency_Cpu;
	float Ram_frequency;
	int State_now = START;
public:
	OC(std::string name_cp, float Frequency_cp,float Ram_frequency ) {
		State_now = START;
		write_state();
		this->NAME_CPU = name_cp;
		this->Frequency_Cpu = Frequency_cp;	
		this->Ram_frequency = Ram_frequency;
		State_now = WAIT;
		write_state();
	}

	void operator()() {
		while (State_now != SHUTDOWN) {
			std::string command;
			std::cout << "Enter Command:";
			std::cin >> command;
			std::cout << std::endl;
			if (command.empty()) {// logic compare (command)
				State_now = ERROR;
				std::cout << "Not command\n";
				State_now = WAIT;
			}
			else if (command.compare("info") == 0) {
				State_now = WORK;
				write_state();
				if (NAME_CPU.empty()) {
					State_now = ERROR;
					std::cout << "Cpu N/A \n";
				}
				else
				{
					std::cout << "Name CPU: " << NAME_CPU << "\t" << Frequency_Cpu << " GHz" << std::endl;

				}
				std::cout << "RAM Frequency: \t" << Ram_frequency <<std::endl;
				State_now = WAIT;
				write_state();
			}

		    else if (command.compare("shutdown") == 0) {
				std::cout << "Shutdown System" << std::endl;
				State_now = SHUTDOWN;
				write_state();
			}
			else if (command.compare("help") == 0){
				std::cout << "1.info\n2.log_state"<<std::endl;
				}
				//log logic
			else if (command.compare("log_state") == 0){
				for (int i = 0; i < filled_state_log; i++){
					if (log_state[i] == 1){
						std::cout << "Start\n";
						}
						else if(log_state[i] == 2){
							std::cout << i << ".Wait\n";
							}
						else if(log_state[i] == 3){
							std::cout << i << ".Work\n";
							}
						else if (log_state[i] == 4){std::cout << "Shutdown\n";}
					}
				}
			else if (command.compare("clear_log") == 0){
					clear_log_stage();
				}
		}
	}
	void write_state(){
		log_state[filled_state_log] = State_now;
		filled_state_log++;
		}
	
	void clear_log_stage(){
		for (int i = 0; i < filled_state_log; i++){
			log_state[i] = 0;
			filled_state_log--;
			}
		}
	
};

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
		if (code_cpu == -1) {
			State_now = ERROR_CPU;// error cpu (cpu n/a)
		}
		if (code_cpu == 1) {
			name_proccesor = "Athlon";
		}
		else if (code_cpu == 2) {
			name_proccesor = "Phenom";
		}
		//Set Frequency
		if (code_cpu == 1 && model_cpu == 3400) {
			Frequency_Cpu = 2.300;
			Ram_frequency = 1333;
		}
		else if (code_cpu == 1 && model_cpu == 3440) {
			Frequency_Cpu = 2.400;
			Ram_frequency = 1333;
		}
		else if (code_cpu == 1 && model_cpu == 3480) {
			Frequency_Cpu = 2.500;
			Ram_frequency = 1600;
		}
		else if (code_cpu == 2 && model_cpu == 3400) {
			Frequency_Cpu = 2.500;
			Ram_frequency = 1600;
		}
		else if (code_cpu == 2 && model_cpu == 3440) {
			Frequency_Cpu = 2.700;
			Ram_frequency = 1600;
		}
		else if (code_cpu == 2 && model_cpu == 3480) {
			Frequency_Cpu = 3.000;
			Ram_frequency = 1600;
		}
		else{State_now = ERROR_CPU;}// Error cpu n/a 
		check();
		// Start or not
		if (State_now != ON) {
			return -1;
		}
		else if (State_now == ON) {
			return 0;
		}
		return 404;
	}

	void GET_Temperature_Cpu(int *Temperature) {// use ptr*
		if (State_now == ACTIVE_COMMAND) {
			*Temperature = 15 + std::rand() % 60;
		}
		else if (State_now == NOT_ACTIVE_COMMAND) {
			*Temperature = 15 + std::rand() % 30;
		}
	}
	//GET
	std::string GET_NAME_CPU() {
		return name_proccesor;
	}
	
	int GET_MODEL_CPU() {
		return model_cpu;
	}

	float GET_Frequency_CPU() {
		return Frequency_Cpu;
	}

	float GET_Frequence_RAM() {
		return Ram_frequency;
	}
	void check() {
		if (Ram_frequency < 0) {
			State_now = ERROR_RAM;
		}
		else if (Ram_frequency > 1700 + std::rand() % 2000) {
			State_now = ERROR_RAM;
		}
		if (Frequency_Cpu < 0 || Frequency_Cpu  > 3.000) {
			State_now = ERROR_CPU;
		}
		if (State_now != ERROR_CPU && State_now != ERROR_RAM && State_now != ERROR_BIOS) {
			State_now = ON;
		}
	}

	void SET_STATUS(int numb_state) {
		this->State_now = numb_state;
	}
	void MIT(){// overdrive
		State_now = BIOS;
		std::cout<<"Welcom MIT state\n" << "1.RAM\n2.CPU\nEnter chose:";
		int chose = 0;
		std::cin >> chose;
		std::cout << std::endl;
		if (chose == 1){
			CPU_OVERDRIVE();
			}
		else if (chose == 2){
			RAM_OVERDRIVE();
			}
		else {State_now = ERROR_BIOS;}
		}
		
		void RAM_OVERDRIVE(){
			std::cout << "Enter RAM frequency(now frequency "<< Ram_frequency << "):";
			std::cin >> Ram_frequency;
			std::cout << std::endl;
			int random = 1600 + std::rand() % 2000;
			if (Ram_frequency > random ){
				State_now = ERROR_RAM;
				Ram_frequency = 800;	
				}
			}
		void CPU_OVERDRIVE(){
			std::cout << "Enter CPU Frequency (now Frequency " <<Frequency_Cpu << ")";
			std::cin >> Frequency_Cpu;
			std::cout << std::endl;
			int random = 2500 + std::rand() % 3100;
			if (Frequency_Cpu > random){
				State_now = ERROR_CPU;				
				}
			}
};

void set_data_cpu(int *code_cpu, int *model_cpu) {
	std::string tmp;
	std::cout << "Enter name proccessor:";
	std::cin >> tmp;
	std::cout << std::endl;
	std::cout << "Enter model cpu:";
	std::cin >> *model_cpu;
	std::cout << std::endl;
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
}

int main() {
	int code_cpu = 0;
	int model_cpu = 0;
	set_data_cpu(&code_cpu, &model_cpu);
	Matherboart mainboart(code_cpu, model_cpu);
	if (mainboart() == -1) {
		std::cout << "Matherboart not starting";
		return -1;
	}
	OC oc(mainboart.GET_NAME_CPU(),mainboart.GET_Frequency_CPU(),mainboart.GET_Frequence_RAM());
	oc();
	return 0;
}
