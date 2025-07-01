#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Aloca dinamicamente uma matriz de inteiros (imagem)
// Retorna um ponteiro para uma matriz de linhas x colunas
int** alocarImagem(int linhas, int colunas) {
    int** imagem = new int*[linhas];
    for (int i = 0; i < linhas; ++i) {
        imagem[i] = new int[colunas];
    }
    return imagem;
}

// Libera a memória alocada para a matriz de inteiros (imagem)
// Recebe o ponteiro da matriz e o número de linhas
void liberarImagem(int** imagem, int linhas) {
    for (int i = 0; i < linhas; ++i) {
        delete[] imagem[i];
    }
    delete[] imagem;
}

// Função para carregar uma imagem PGM (formato ASCII)
// Lê o arquivo, ignora comentários, lê dimensões, valor máximo e pixels
// Aloca dinamicamente a matriz imagem e preenche com os valores do arquivo
void carregarImagem(const string& nomeArquivo, int**& imagem, int& linhas, int& colunas) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return;
    }

    string linha;
    // Ler "P2" (identificador do formato PGM ASCII)
    getline(arquivo, linha);
    if (linha != "P2") {
        cout << "Formato PGM inválido (esperado P2)." << endl;
        return;
    }

    // Ignora comentários e lê as dimensões
    string temp;
    arquivo >> temp;
    while (temp[0] == '#') {
        getline(arquivo, temp);  // ignora a linha do comentário
        arquivo >> temp;
    }

    // Lê o número de colunas e linhas
    colunas = stoi(temp);
    arquivo >> linhas;

    // Ignora comentários e lê o valor máximo
    arquivo >> temp;
    while (temp[0] == '#') {
        getline(arquivo, temp);
        arquivo >> temp;
    }
    int maxValor = stoi(temp);

    // Aloca a matriz imagem dinamicamente
    imagem = alocarImagem(linhas, colunas);

    // Lê os pixels da imagem e armazena na matriz
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            arquivo >> imagem[i][j];
        }
    }

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
                
                // Libera a imagem anterior, se existir
                if (imagem != nullptr) {
                    liberarImagem(imagem, linhas);
                    imagem = nullptr;
                }

                // Carrega a nova imagem
                carregarImagem(nomeArquivo, imagem, linhas, colunas);
                cout << "\nImagem carregada com sucesso!" << endl;
                break;

            case 2:
                if (imagem == nullptr) {
                    cout << "\nNenhuma imagem carregada. Por favor, carregue uma imagem primeiro." << endl;
                }else {
                    // Exibe o menu de alterações da imagem
                    cout << "\n====== Menu de Alteracoes da Imagem ======" << endl;
                    cout << "[1] - Escurecer ou Clarear Imagem" << endl;
                    cout << "[2] - Rotacionar Imagem" << endl;
                    cout << "[3] - Negativar a Imagem" << endl;
                    cout << "[4] - Binarizar Imagem" << endl;
                    cout << "[5] - Iconizar Imagem" << endl;
                    cout << "[0] - Voltar ao Menu Principal" << endl;
                    cout << "===========================================" << endl;
                }
                break;

            case 0:
                cout << "Encerrando o programa..." << endl;
                break;

            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    }

    // Libera a imagem no final do programa, se existir
    if (imagem != nullptr) {
        liberarImagem(imagem, linhas);
    }

    return 0;
}
