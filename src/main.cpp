#include <iostream>

using namespace std;

int main(){
    typedef int Imagem[1024][1024];

    string nomeArquivo;

    int opcao=1;
    while (opcao != 0){
        cout << "====== Menu de Opcoes ======" << endl;
        cout << "[1] - Carregar Imagem" << endl;
        cout << "[2] - Menu de Alteracoes da Imagem" << endl;
        cout << "[0] - Encerrar Programa" << endl;
        cout << "============================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "O formato do nome do arquivo deve ser: 'imagem.pgm'" << endl;
                cout << "Digite o nome do arquivo: ";
                cin >> nomeArquivo;
                nomeArquivo += ".pgm";
                cout << "Carregando imagem: " << nomeArquivo << endl;
                break;
            case 2:
                // Menu de Alterações da Imagem
                break;
            case 0:
                cout << "Encerrando o programa..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    }

    return 0;
}