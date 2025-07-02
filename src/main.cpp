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
    // Retorna um ponteiro para uma matriz de linhas x colunas
    return imagem;
}

// Libera a memória alocada para a matriz de inteiros (imagem)
void liberarImagem(int** imagem, int linhas) {
    for (int i = 0; i < linhas; ++i) {
        delete[] imagem[i];
    }
    delete[] imagem;
}

// Função para carregar uma imagem PGM (formato ASCII)
void carregarImagem(const string& nomeArquivo, int**& imagem, int& linhas, int& colunas, int& maxValor) {
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
    maxValor = stoi(temp);

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

// Função para salvar uma imagem PGM (formato ASCII)
void salvarImagem(int** imagem, int linhas, int colunas, int maxValor, const string& base, const string& extensao, const string& registro) {
    // Gera nome único
    string nomeArquivo = gerarNomeUnico(base, extensao, registro);

    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << endl;
        return;
    }

    // Escreve o cabeçalho do PGM
    arquivo << "P2\n";
    arquivo << colunas << " " << linhas << "\n";
    arquivo << maxValor << "\n";

    // Escreve os pixels da imagem
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            arquivo << imagem[i][j] << " ";
        }
        arquivo << "\n";
    }
    arquivo.close();

    // Registra o nome no arquivo de nomes
    ofstream arq(registro, ios::app);
    arq << nomeArquivo << endl;
    arq.close();

    cout << "Imagem salva como: " << nomeArquivo << endl;
}

// Função para clarar ou escurecer a imagem
void ajustarBrilho(int** imagem, int linhas, int colunas, int ajuste) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            imagem[i][j] += ajuste;
            // Garante que os valores estejam dentro do intervalo [0, maxValor]
            if (imagem[i][j] < 0) imagem[i][j] = 0;
            if (imagem[i][j] > 255) imagem[i][j] = 255; // Considerando maxValor como 255 para PGM
        }
    }
}

// Gera um nome único para o arquivo PGM, consultando nomes.txt
string gerarNomeUnico(const string& base, const string& extensao, const string& registro) {
    int contador = 1;
    string nome;
    bool existe;
    do {
        nome = base + "_" + to_string(contador) + extensao;
        existe = false;
        ifstream arq(registro);
        string nomeLido;
        while (getline(arq, nomeLido)) {
            if (nomeLido == nome) {
                existe = true;
                break;
            }
        }
        contador++;
    } while (existe);
    return nome;
}

int main() {
    string nomeArquivo;
    int** imagem = nullptr;
    int linhas = 0, colunas = 0, maxValor = 0;

    string nomes[100]; // Array para armazenar nomes de arquivos
    int qtdNomes = 0; // Quantidade de nomes lidos
    int contadorImagens = 0; // Contador para gerar nomes únicos de arquivos

    // Lê os nomes dos arquivos do arquivo nomes.txt
    ifstream arquivoNomes("nomes.txt");
    // Verifica se o arquivo nomes.txt foi aberto corretamente
    if (!arquivoNomes.is_open()) {
        cout << "Erro ao abrir o arquivo de nomes: nomes.txt" << endl;
        return 1;
    }
    // Lê os nomes dos arquivos do arquivo nomes.txt
    for(int i = 0; i < 100; ++i) {
        arquivoNomes >> nomes[i];
        if (arquivoNomes.eof()) break; // Para se chegar ao final do arquivo
        qtdNomes++;
    }
    arquivoNomes.close();

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
                carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
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
                    cout << "Escolha uma opcao: ";
                    cin >> opcao;

                    switch (opcao) {
                        case 1: {
                            int ajuste;
                            cout << "Digite o valor de ajuste de brilho (positivo para clarear, negativo para escurecer): ";
                            cin >> ajuste;

                            ajustarBrilho(imagem, linhas, colunas, ajuste);
                            cout << "Brilho ajustado com sucesso!" << endl;

                            // Salva a imagem ajustada
                            
                            break;
                        }
                        case 2:
                            // Implementar rotacionar imagem
                            cout << "Funcionalidade de rotacionar imagem ainda não implementada." << endl;
                            break;
                        case 3:
                            // Implementar negativar imagem
                            cout << "Funcionalidade de negativar imagem ainda não implementada." << endl;
                            break;
                        case 4:
                            // Implementar binarizar imagem
                            cout << "Funcionalidade de binarizar imagem ainda não implementada." << endl;
                            break;
                        case 5:
                            // Implementar iconizar imagem
                            cout << "Funcionalidade de iconizar imagem ainda não implementada." << endl;
                            break;
                        case 0:
                            cout << "\nVoltando ao menu principal..." << endl;
                            break;
                        default:
                            cout << "Opcao invalida. Tente novamente." << endl;
                    }
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
