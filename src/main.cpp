/* 
 * Arquivo:   main.cpp
 * Autor: 2024.2.08.001
 * Name:Carlos Eduardo Pereira dos Santos
 * Disciplina: AEDs I (Prática)
 * Criado em 03 de Julho de 2025, 11:20
 * Local: Unifal Santa Clara
 
    Objetivo:
  * Programa para edição de imagens PGM em modo texto.
  * Permite carregar, salvar, clarear/escurecer, rotacionar, espelhar, negativar, binarizar e iconizar imagens.
  * Cada alteração gera um novo arquivo PGM com nome único.
  * Projeto para praticar manipulação de matrizes e ponteiros em C++.
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Protótipos das funções
int** alocarImagem(int linhas, int colunas);
void liberarImagem(int** imagem, int linhas);
void carregarImagem(const string& nomeArquivo, int**& imagem, int& linhas, int& colunas, int& maxValor);
string gerarNomeUnico(const string& base, const string& extensao, const string& registro);
void salvarImagem(int** imagem, int linhas, int colunas, int maxValor, const string& base, const string& extensao, const string& registro);
void ajustarBrilho(int** imagem, int linhas, int colunas, int ajuste);
void rotacionarDireita(int**& imagem, int& linhas, int& colunas);
void rotacionarEsquerda(int**& imagem, int& linhas, int& colunas);
void espelharHorizontal(int**& imagem, int linhas, int colunas);
void espelharVertical(int**& imagem, int linhas, int colunas);
void negativarImagem(int** imagem, int linhas, int colunas, int maxValor);
void binarizarImagem(int**& imagem, int linhas, int colunas, int limiar);
void iconizarImagem(int**& imagem, int& linhas, int& colunas, int tamanhoIcone);

int main() {
    string nomeArquivo, registro = "nomes.txt"; // Arquivo para registrar nomes de imagens
    int** imagem = nullptr;
    int linhas = 0, colunas = 0, maxValor = 0;

    int opcao = 1;
    while (opcao != 0) {
        cout << "\n========= Menu de Opcoes =========" << endl;
        cout << "[1] - Carregar Imagem" << endl;
        cout << "[2] - Menu de Alteracoes da Imagem" << endl;
        cout << "[0] - Encerrar Programa" << endl;
        cout << "==================================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "\nO formato do nome do arquivo deve ser: 'exemplo.pgm'" << endl;
                cout << "Digite o nome do arquivo: ";
                cin >> nomeArquivo;
                
                // Libera a imagem anterior, se existir
                if (imagem != nullptr) {
                    liberarImagem(imagem, linhas);
                    imagem = nullptr;
                }

                // Carrega a nova imagem
                carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
                if (imagem != nullptr) {
                    cout << "\nImagem carregada com sucesso!" << endl;
                }
                break;

            case 2:
                if (imagem == nullptr) {
                    cout << "\nNenhuma imagem carregada. Por favor, carregue uma imagem primeiro." << endl;
                }else {
                    // Exibe o menu de alterações da imagem
                    cout << "\n====== Menu de Alteracoes da Imagem ======" << endl;
                    cout << "[1] - Escurecer ou Clarear Imagem" << endl;
                    cout << "[2] - Rotacionar ou Espelhar Imagem" << endl;
                    cout << "[3] - Negativar a Imagem" << endl;
                    cout << "[4] - Binarizar Imagem" << endl;
                    cout << "[5] - Iconizar Imagem" << endl;
                    cout << "[0] - Voltar ao Menu Principal" << endl;
                    cout << "===========================================" << endl;
                    cout << "Escolha uma opcao: ";
                    int opAlteracao;
                    cin >> opAlteracao;

                    switch (opAlteracao) {
                        case 1: {
                            int ajuste;
                            cout << "Digite o valor de ajuste de brilho (positivo para clarear, negativo para escurecer): ";
                            cin >> ajuste;

                            ajustarBrilho(imagem, linhas, colunas, ajuste);
                            cout << "\nBrilho ajustado com sucesso!" << endl;

                            // Salva a imagem ajustada
                            salvarImagem(imagem, linhas, colunas, maxValor, "saida", ".pgm", registro);

                            // Carrega novamente a imagem para refletir as alterações
                            carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
                            break;
                        }
                        case 2:
                            // Implementar rotacionar imagem
                            cout << "\n========= Rotacionar Imagem =========" << endl;
                            cout << "[1] - Rotacionar 90 graus a direita" << endl;
                            cout << "[2] - Rotacionar 90 graus a esquerda" << endl;
                            cout << "[3] - Espelhar horizontalmente" << endl;
                            cout << "[4] - Espelhar verticalmente" << endl;
                            cout << "[0] - Voltar ao Menu de Alteracoes" << endl;
                            cout << "=====================================" << endl;
                            cout << "Escolha uma opcao: ";
                            int opcaoRotacao;
                            cin >> opcaoRotacao;
                            switch (opcaoRotacao) {
                                case 1:
                                    // Implementar rotacionar 90 graus a direita
                                    rotacionarDireita(imagem, linhas, colunas);
                                    cout << "\nImagem rotacionada 90 graus a direita!" << endl;

                                    // Salva a imagem rotacionada
                                    salvarImagem(imagem, linhas, colunas, maxValor, "saida", ".pgm", registro);

                                    // Carrega novamente a imagem para refletir as alterações
                                    carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
                                    break;
                                case 2:
                                    // Implementar rotacionar 90 graus a esquerda
                                    rotacionarEsquerda(imagem, linhas, colunas);
                                    cout << "\nImagem rotacionada 90 graus a esquerda!" << endl;

                                    // Salva a imagem rotacionada
                                    salvarImagem(imagem, linhas, colunas, maxValor, "saida", ".pgm", registro);

                                    // Carrega novamente a imagem para refletir as alterações
                                    carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
                                    break;
                                case 3:
                                    // Implementar espelhar horizontalmente
                                    espelharHorizontal(imagem, linhas, colunas);
                                    cout << "\nImagem espelhada horizontalmente!" << endl;

                                    // Salva a imagem espelhada
                                    salvarImagem(imagem, linhas, colunas, maxValor, "saida", ".pgm", registro);

                                    // Carrega novamente a imagem para refletir as alterações
                                    carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
                                    break;
                                case 4:
                                    // Implementar espelhar verticalmente
                                    espelharVertical(imagem, linhas, colunas);
                                    cout << "\nImagem espelhada verticalmente!" << endl;

                                    // Salva a imagem espelhada
                                    salvarImagem(imagem, linhas, colunas, maxValor, "saida", ".pgm", registro);

                                    // Carrega novamente a imagem para refletir as alterações
                                    carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
                                    break;
                                case 0:
                                    cout << "\nVoltando ao menu principal..." << endl;
                                    break;
                                default:
                                    cout << "\nOpcao invalida. Tente novamente." << endl;
                            }
                            break;
                        case 3:
                            // Negativa a imagem
                            negativarImagem(imagem, linhas, colunas, maxValor);
                            cout << "\nImagem negativada com sucesso!" << endl;

                            // Salva a imagem negativada
                            salvarImagem(imagem, linhas, colunas, maxValor, "saida", ".pgm", registro);

                            // Carrega novamente a imagem para refletir as alterações
                            carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
                            break;
                        case 4:
                            // Binarizar a imagem por um limiar informado pelo usuário
                            cout << "\n========= Binarizar Imagem =========" << endl;
                            int limiar;
                            cout << "Digite o valor do limiar (0 a " << maxValor << "): ";
                            cin >> limiar;

                            if (limiar < 0 || limiar > maxValor) {
                                cout << "Limiar invalido. Deve estar entre 0 e " << maxValor << "." << endl;
                            } else {
                                binarizarImagem(imagem, linhas, colunas, limiar);
                                cout << "\nImagem binarizada com sucesso!" << endl;

                                // Salva a imagem binarizada
                                salvarImagem(imagem, linhas, colunas, maxValor, "saida", ".pgm", registro);

                                // Carrega novamente a imagem para refletir as alterações
                                carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
                            }

                            break;
                        case 5:
                            // Iconizar imagem
                            cout << "\nIconizar imagem em 64x64 pixels..." << endl;

                            iconizarImagem(imagem, linhas, colunas, 64);
                            cout << "\nImagem iconizada com sucesso!" << endl;

                            // Salva a imagem iconizada
                            salvarImagem(imagem, linhas, colunas, maxValor, "saida", ".pgm", registro);

                            // Carrega novamente a imagem para refletir as alterações
                            carregarImagem(nomeArquivo, imagem, linhas, colunas, maxValor);
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
        cout << "\nErro ao abrir o arquivo: " << nomeArquivo << endl;
        cout << "Certifique-se de que o arquivo existe e esta no formato correto." << endl;
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

// Função para rotacionar a imagem 90 graus para a direita
void rotacionarDireita(int**& imagem, int& linhas, int& colunas) {
    // Cria uma nova matriz com dimensões invertidas (colunas x linhas)
    int** novaImagem = new int*[colunas];
    for (int i = 0; i < colunas; ++i) {
        novaImagem[i] = new int[linhas];
    }

    // Copia os pixels da imagem original para a nova matriz, rotacionando 90 graus à direita
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            novaImagem[j][linhas - 1 - i] = imagem[i][j];
        }
    }

    // Libera a memória da imagem original
    for (int i = 0; i < linhas; ++i) {
        delete[] imagem[i];
    }
    delete[] imagem;

    // Atualiza o ponteiro da imagem para apontar para a nova matriz rotacionada
    imagem = novaImagem;

    // Troca os valores de linhas e colunas usando variável auxiliar
    int temp = linhas;
    linhas = colunas;
    colunas = temp;
}

// Função para rotacionar a imagem a 90 graus para a esquerda
void rotacionarEsquerda(int**& imagem, int& linhas, int& colunas) {
    // Cria uma nova matriz com dimensões invertidas (colunas x linhas)
    int** novaImagem = new int*[colunas];
    for (int i = 0; i < colunas; ++i) {
        novaImagem[i] = new int[linhas];
    }

    // Copia os pixels da imagem original para a nova matriz, rotacionando 90 graus à esquerda
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            novaImagem[colunas - 1 - j][i] = imagem[i][j];
        }
    }

    // Libera a memória da imagem original
    for (int i = 0; i < linhas; ++i) {
        delete[] imagem[i];
    }
    delete[] imagem;

    // Atualiza o ponteiro da imagem para apontar para a nova matriz rotacionada
    imagem = novaImagem;

    // Troca os valores de linhas e colunas usando variável auxiliar
    int temp = linhas;
    linhas = colunas;
    colunas = temp;
}

// Função para espelhar horizontalmente a imagem
void espelharHorizontal(int**& imagem, int linhas, int colunas) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas / 2; ++j) {
            int temp = imagem[i][j];
            imagem[i][j] = imagem[i][colunas - 1 - j];
            imagem[i][colunas - 1 - j] = temp;
        }
    }
}

// Função para espelhar verticalmente a imagem
void espelharVertical(int**& imagem, int linhas, int colunas) {
    for (int i = 0; i < linhas / 2; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int temp = imagem[i][j];
            imagem[i][j] = imagem[linhas - 1 - i][j];
            imagem[linhas - 1 - i][j] = temp;
        }
    }
}

// Função para negativar a imagem
void negativarImagem(int** imagem, int linhas, int colunas, int maxValor) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            imagem[i][j] = maxValor - imagem[i][j];
        }
    }
}

// Função para binarizar a imagem
void binarizarImagem(int**& imagem, int linhas, int colunas, int limiar) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (imagem[i][j] > limiar) {
                imagem[i][j] = 255;
            } else {
                imagem[i][j] = 0;
            }
        }
    }
}

// Função para iconizar a imagem
void iconizarImagem(int**& imagem, int& linhas, int& colunas, int tamanhoIcone) {
    int blocoL = linhas / tamanhoIcone;
    int blocoC = colunas / tamanhoIcone;

    int** novaImagem = new int*[tamanhoIcone];
    for (int i = 0; i < tamanhoIcone; i++)
        novaImagem[i] = new int[tamanhoIcone];

    for (int i = 0; i < tamanhoIcone; i++) {
        for (int j = 0; j < tamanhoIcone; j++) {
            int soma = 0;
            int cont = 0;

            for (int x = 0; x < blocoL; x++) {
                for (int y = 0; y < blocoC; y++) {
                    int linhaOrig = i * blocoL + x;
                    int colunaOrig = j * blocoC + y;

                    // Verifica se está dentro da imagem original
                    if (linhaOrig < linhas && colunaOrig < colunas) {
                        soma += imagem[linhaOrig][colunaOrig];
                        cont++;
                    }
                }
            }

            novaImagem[i][j] = (cont > 0) ? (soma / cont) : 0;
        }
    }

    // Libera a memória da imagem original
    for (int i = 0; i < linhas; ++i) {
        delete[] imagem[i];
    }
    delete[] imagem;

    // Atualiza o ponteiro da imagem para apontar para a nova matriz do ícone
    imagem = novaImagem;

    // Atualiza as dimensões da imagem
    linhas = colunas = tamanhoIcone;
}