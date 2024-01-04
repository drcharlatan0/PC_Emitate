#include <iostream>
#include <string>
//#define DEBUG

//version 3

class OC  {
	enum STATE_OC {
		START = 1,
		WAIT,//2
		WORK,//3
		ERROR,//4
		CRASH,//5
		SHUTDOWN,//6
		GET_DATA_TEMPERATURE,//7
	};
	int filled_state_log = 0;
	int log_state[400];
	std::string NAME_CPU;
	float Frequency_Cpu;
	float Ram_frequency;
	char _lang = 'e'; 
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
	void rewrite_info(std::string name_cp, float Frequency_cp,float Ram_frequency ) {
		State_now = START;
		write_state();
		this->NAME_CPU = name_cp;
		this->Frequency_Cpu = Frequency_cp;	
		this->Ram_frequency = Ram_frequency;
		State_now = WAIT;
		write_state();
	}

	int operator()() {
		while (State_now != SHUTDOWN) {
			std::string command;
			if (_lang == 'e'){
			std::cout << "Enter Command:";
		}
			else if (_lang == 'r'){
				std::cout << "Введите команду:";
				}
			std::cin >> command;
			std::cout << std::endl;
			if (command.empty()) {// logic compare (command)
				State_now = ERROR;
			if (_lang == 'e'){
				std::cout << "Wrong command\n";
			}
			else if (_lang == 'r'){
				std::cout << "Неправильная комманда\n";
				}
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
					if(_lang == 'e'){
						std::cout << "Name CPU: " << NAME_CPU << "\t" << Frequency_Cpu << " GHz" << std::endl;
					}
					else if (_lang == 'r'){
						std::cout << "Имя процессора: " << NAME_CPU << "\t" << Frequency_Cpu << " ГГц" << std::endl;
						}
				}
				if (_lang == 'e'){
				std::cout << "RAM Frequency: \t" << Ram_frequency <<std::endl;
				}
				else if (_lang == 'r'){
					std::cout << "Частота ОЗУ: \t" << Ram_frequency <<std::endl;
					}
				State_now = WAIT;
				write_state();
			}

		    else if (command.compare("shutdown") == 0) {
				std::cout << "Shutdown System" << std::endl;
				State_now = SHUTDOWN;
				write_state();
				return 52;
			}
			//else if (command.compare("temperature") == 0){
					//return GET_DATA_TEMPERATURE;
				//}
			else if (command.compare("help") == 0){
				std::cout << "1.info\n2.log_state\n3.log_state\n"<<std::endl;
				}
			else if(command.compare("change_lang") == 0){
				switch (_lang){
					case 'e':{
						_lang = 'r';
						break;
						}
						case 'r':{
							_lang = 'e';
							break;
							}
					}
				}
				//log logic
			else if (command.compare("log_state") == 0){
				for (int i = 0; i < filled_state_log; i++){
					if (log_state[i] == 1){
						std::cout << i << ".Start\n";
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
			else if(command.compare("overdrive") == 0|| command.compare("BIOS") == 0 || command.compare("MIT") == 0){
				return 1;
				}
		}
		return 0;
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
