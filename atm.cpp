using namespace std;

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <ostream>
#include <sstream>
#include <stdlib.h>

#define PASSWORD "12345"
#define TRANSAKSI_SETOR	"SETOR"
#define TRANSAKSI_TARIK	"TARIK"


fstream file_log("log_transaksi.txt", ios::app);

class mesinATM{
	
		char password[99];
		int selected_menu;
		typedef struct{
			char berita_transaksi[99];
			int nominal_transaksi;
			int current_saldo;
		}RecordTransaksi;
		
		RecordTransaksi rTransaksiBaca;
		RecordTransaksi rTransaksiTarik;
		RecordTransaksi rTransaksiSetor;
		
		
	
	public :
	void initScreen(){
		do{
			system("cls");
			cout << "\a" ;
			cout << "============================================ \n";
			cout << " Selamat datang di Bank KAMI \n";
			cout << "============================================ \n";
			cout << "Silahkan masukkan password Anda : ";
			cin >> password ;
		}while(strcmp(PASSWORD,password) != 0);
	}
	
	
	void menuScreen(){
		do{
			system("cls");
			cout << "============================================ \n";
			cout << " Menu Transaksi Anda \n";
			cout << "============================================ \n";
			cout << "1. Setor\n";
			cout << "2. Tarik Tunai\n";
			cout << "3. Cek Saldo\n";
			cout << "4. Cetak Resi\n";
			cout << "5. Keluar\n";
			cout << "============================================ \n";
			cout << "Pilihan ANda (1/2/3/4/5) : ";
			cin >> selected_menu ;
		}while(selected_menu < 1 || selected_menu > 5);
		if(selected_menu == 1){
			setorScreen();
		}else
		if(selected_menu == 2){
			tarikTunaiScreen();
		}else
		if(selected_menu == 3){
			cekSaldoScreen();
		}else
		if(selected_menu == 4){
			cetakResiScreen();
		}else
		if(selected_menu == 5){	
			exit(EXIT_SUCCESS);
		}
	}
	
	void setorScreen(){
		int jawab;
		do{
			system("cls");
			cout << "============================================ \n";
			cout << "1. Menu Setor Tunai \n";
			cout << "============================================ \n";
			cout << "Nominal yang Anda setorkan : ";
			cin >> rTransaksiSetor.nominal_transaksi;
			strcpy(rTransaksiSetor.berita_transaksi,TRANSAKSI_SETOR);
			if (file_log.is_open()) {
				int st = saldoTerakhir(); 
				if(st == -1){ // jika log masih kosong return = 1
					file_log << rTransaksiSetor.berita_transaksi << "\t" << rTransaksiSetor.nominal_transaksi << "\t" << rTransaksiSetor.nominal_transaksi << endl ;	
				}else{
					rTransaksiSetor.current_saldo = st + rTransaksiSetor.nominal_transaksi;
					file_log << rTransaksiSetor.berita_transaksi << "\t" << rTransaksiSetor.nominal_transaksi << "\t" << rTransaksiSetor.current_saldo << endl ;
				}
				cout << "Setor tunai sebesar Rp. " << rTransaksiSetor.nominal_transaksi << " berhasil!" << "\n" ;
		        cout << "Apakah Anda akan melakukan setor lagi ?" << "\n" << "[Ya = Tekan 1] / [Tidak = Tekan 0] ";
		        cin >> jawab;
		    } else {
		        cout << "File log error bos!";
		    }
		}while(jawab == 1);
		menuScreen();
	}
	
	void tarikTunaiScreen(){
		int jawab;
		do{
			system("cls");
			cout << "============================================ \n";
			cout << "2. Menu Tarik Tunai \n";
			cout << "============================================ \n";
			cout << "Nominal tarik tunai : ";
			cin >> rTransaksiTarik.nominal_transaksi;
			if (file_log.is_open()) {
				int st = saldoTerakhir(); 
				if(st >= 1 && st <= 10000 ){ // jika saldo dibawah 10000
					cout << "Mohon Maaf Anda Tidak Dapat Melakukan Penarikan!" << "\n" <<"Sisa saldo anda hari ini Rp. " << st << "\n";
					system("pause");
					menuScreen();
				}else
				if((st - rTransaksiTarik.nominal_transaksi) <= 10000){ // jika saldo dibawah 10000
					cout << "Mohon Maaf Anda Tidak Dapat Melakukan Penarikan!" << "\n" <<"Anda harus Menyisakan Dana dalam Rekening Anda minimal Rp.10000" << "\n";
					system("pause");
					menuScreen();
				}else{
					strcpy(rTransaksiTarik.berita_transaksi,TRANSAKSI_TARIK);
					rTransaksiTarik.current_saldo = st - rTransaksiTarik.nominal_transaksi;
					file_log << rTransaksiTarik.berita_transaksi << "\t" << rTransaksiTarik.nominal_transaksi << "\t" << rTransaksiTarik.current_saldo << endl ;
					cout << "Tarik tunai sebesar Rp. " << rTransaksiTarik.nominal_transaksi << " berhasil!" << "\n" ;
			        cout << "Apakah Anda akan melakukan tarik tunai lagi ?" << "\n" << "[Ya = Tekan 1] / [Tidak = Tekan 0] ";
			        cin >> jawab;
				}
		    } else {
		        cout << "File log error bos!";
		    }
		}while(jawab == 1);
		menuScreen();
	}
	
	void cekSaldoScreen(){
		int st = saldoTerakhir();
		system("cls");
		cout << "============================================ \n";
		cout << "3. Cek Saldo\n";
		cout << "============================================ \n";
		cout << "Saldo ANda saat ini : " << st << "\n";
		system("pause");
		menuScreen(); 
	}
	
	void cetakResiScreen(){
		int st = saldoTerakhir();
		system("cls");
		fstream file_log_bacadata("log_transaksi.txt", ios::in);
		string baris_text;
		if (file_log_bacadata.is_open()) {
			while (getline(file_log_bacadata, baris_text)) {
	            istringstream ss(baris_text);
		        ss >> rTransaksiBaca.berita_transaksi >> rTransaksiBaca.nominal_transaksi >> rTransaksiBaca.current_saldo;
			}
			cout << "============================================ \n";
			cout << "4. Cetak Resi\n";
			cout << "============================================ \n";
			cout << "                 PT BANK KAMI         \n";
			cout << "--------------------------------------------\n";
			cout << rTransaksiBaca.berita_transaksi << " TUNAI Rp. " << rTransaksiBaca.nominal_transaksi << "\n";
			cout << "Saldo Anda saat ini Rp. " << rTransaksiBaca.current_saldo << "\n";
			cout << "Terima kasih atas kunjungan Anda\n";
			cout << "--------------------------------------------\n";
			system("pause");
			menuScreen();
	    } else {
	        exit(EXIT_SUCCESS); 
	    } 
	}
	
	
	int saldoTerakhir(){
		fstream file_log_bacadata("log_transaksi.txt", ios::in);
		string baris_text;
		if (file_log_bacadata.is_open()) {
			while (getline(file_log_bacadata, baris_text)) {
	            istringstream ss(baris_text);
		        ss >> rTransaksiBaca.berita_transaksi >> rTransaksiBaca.nominal_transaksi >> rTransaksiBaca.current_saldo;
			}
			return rTransaksiBaca.current_saldo;
	    } else {
	        exit(EXIT_SUCCESS); 
	    }
	}
};//akhir dari class


int main(){
	mesinATM myATM;
	myATM.initScreen();
	myATM.menuScreen();
getch();	
}




