#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Aloca dinamicamente uma matriz de inteiros (imagem)
int** alocarImagem(int linhas, int colunas) {
    int** imagem = new int*[linhas];
    for (int i = 0; i < linhas; ++i) {
        imagem[i] = new int[colunas];
    }
    return imagem;
}

// Libera a memória da imagem
void liberarImagem(int** imagem, int linhas) {
    for (int i = 0; i < linhas; ++i) {
        delete[] imagem[i];
    }
    delete[] imagem;
}

// Função para carregar imagem PGM ASCII
void carregarImagem(const string& nomeArquivo, int**& imagem, int& linhas, int& colunas) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return;
    }

    string linha;
    // Ler "P2"
    getline(arquivo, linha);
    if (linha != "P2") {
        cout << "Formato PGM inválido (esperado P2)." << endl;
        return;
    }

    // Ignora comentários
    string temp;
    arquivo >> temp;
    while (temp[0] == '#') {
        getline(arquivo, temp);  // ignora a linha do comentário
        arquivo >> temp;
    }

    // Primeira parte das dimensões
    colunas = stoi(temp);
    arquivo >> linhas;

    arquivo >> temp;
    while (temp[0] == '#') {
        getline(arquivo, temp);
        arquivo >> temp;
    }
    int maxValor = stoi(temp);

    // Alocar imagem dinamicamente
    imagem = alocarImagem(linhas, colunas);

    // Ler pixels
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            arquivo >> imagem[i][j];
        }
    }

    cout << "Imagem carregada: " << linhas << " linhas, " << colunas << " colunas, valor maximo: " << maxValor << endl;

    arquivo.close();
}

int main() {
    string nomeArquivo;
    int** imagem = nullptr;
    int linhas = 0, colunas = 0;

    int opcao = 1;
    while (opcao != 0) {
        cout << "\n====== Menu de Opcoes ======" << endl;
        cout << "[1] - Carregar Imagem" << endl;
        cout << "[2] - Menu de Alteracoes da Imagem" << endl;
        cout << "[0] - Encerrar Programa" << endl;
        cout << "=============================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "\nO formato do nome do arquivo deve ser: 'imagem.pgm'" << endl;
                cout << "Digite o nome do arquivo: ";
                cin >> nomeArquivo;
                
                // Liberar imagem anterior, se existir
                if (imagem != nullptr) {
                    liberarImagem(imagem, linhas);
                    imagem = nullptr;
                }

                carregarImagem(nomeArquivo, imagem, linhas, colunas);
                cout << "Imagem carregada com sucesso!" << endl;
                break;

            case 2:
                cout << "Funcionalidade em desenvolvimento..." << endl;
                break;

            case 0:
                cout << "Encerrando o programa..." << endl;
                break;

            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    }

    // Libera a imagem no final do programa
    if (imagem != nullptr) {
        liberarImagem(imagem, linhas);
    }

    return 0;
}
