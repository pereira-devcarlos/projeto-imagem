# 📷 Projeto Imagem


### 🎯 Objetivo

Desenvolver habilidades em manipulação de matrizes (imagens) utilizando ponteiros em C/C++, implementando funcionalidades para processar imagens em tons de cinza a partir de arquivos-texto no formato PGM (Portable GrayMap).

---

### 🖼️ Sobre o Projeto

O programa apresenta um **menu interativo** que permite ao usuário:

1. **Carregar uma imagem** no formato PGM.
2. **Executar operações** sobre a imagem carregada, salvando o resultado de cada operação em um novo arquivo PGM, com nome distinto.

> **Observação:**  
> Toda interação com o usuário é feita apenas na função `main` usando `cin` e `cout`.  
> Cada operação é implementada em uma função separada.

---

### 📑 Formato do Arquivo PGM

O programa trabalha com imagens em tons de cinza no formato PGM (ASCII):

- **1ª linha:** `P2`
- **2ª linha:** `<colunas> <linhas>`
- **3ª linha:** `<valor máximo de tons de cinza>`
- **4ª linha em diante:** valores inteiros dos pixels, separados por espaço, entre 0 e o valor máximo.
- **Linhas iniciadas por `#`** são ignoradas (comentários).

---

### 🛠️ Funcionalidades Implementadas

- **Escurecer ou clarear** a imagem por um fator informado pelo usuário.
- **Rotacionar** a imagem:
  - 90º à esquerda
  - 90º à direita
  - Espelhar horizontalmente (em torno da linha vertical)
  - Espelhar verticalmente (em torno da linha horizontal)
- **Gerar imagem negativa** (inversão dos tons).
- **Binarização** por limiar informado pelo usuário (pixels abaixo do limiar tornam-se 0, acima tornam-se o valor máximo).
- **Iconização**: redução para 64x64 pixels.

Cada operação gera um novo arquivo PGM de saída, respeitando o formato e limites do arquivo original.

---

### 📋 Requisitos

- Ler imagens PGM criadas pelos autores.
- Menu interativo para seleção de operações.
- Cada operação implementada em função separada (`C/C++`).
- Somente a função `main` pode usar `cin` e `cout`.
- Salvar o resultado de cada operação em um novo arquivo PGM.
- Os valores de tons de cinza devem sempre estar entre 0 e o valor máximo do arquivo.
- **Código-fonte comentado**, com descrição do projeto e nomes dos autores.

---

### ▶️ Como Compilar e Executar

1. **Compile o projeto** com um compilador C++. Exemplo usando g++:
   ```sh
   g++ -o projeto-imagem projeto-imagem.cpp
   ```

2. **Coloque a imagem PGM** (ASCII, formato P2) na mesma pasta do executável.

3. **Execute o programa**:
   ```sh
   ./projeto-imagem
   ```

4. **Siga o menu interativo:**

   - **[1] Carregar Imagem:**  
     Informe o nome do arquivo com a extensão `.pgm` (exemplo: `imagem.pgm`).
   - **[2] Menu de Alterações da Imagem:**  
     Após carregar a imagem, acesse este menu para escolher operações:
     - Escurecer ou Clarear (ajuste de brilho)
     - Rotacionar (direita/esquerda) ou Espelhar (horizontal/vertical)
     - Negativar (imagem negativa)
     - Binarizar (por limiar informado)
     - Iconizar (reduz para 64x64 pixels)
     - Voltar ao menu principal

     > **Importante:**  
     > Após cada alteração escolhida, uma nova imagem PGM é gerada automaticamente com nome único e salva no diretório do executável.
     >  
     > O nome do novo arquivo é registrado em `nomes.txt`. Você pode consultar esse arquivo para ver todos os nomes gerados.

   - **[0] Encerrar Programa:**  
     Sai do programa e libera a memória utilizada.

---

### 📝 Observações de Uso

- Só é possível aplicar operações **depois de carregar uma imagem válida**.
- Os arquivos gerados são salvos no formato PGM (ASCII/P2) e têm nomes automáticos, como `saida_1.pgm`, `saida_2.pgm` etc.
- O histórico dos arquivos gerados fica em `nomes.txt`, criado no mesmo diretório.
- Sempre que uma operação é realizada, a imagem original é recarregada, ou seja, as operações **não são cumulativas** a partir do resultado anterior.
- O programa foi desenvolvido para ser utilizado via terminal/console, utilizando apenas `cin` e `cout` para interação com o usuário.

---

### 💡 Dicas

- Utilize um visualizador de arquivos PGM para conferir os resultados.
- Sinta-se à vontade para contribuir ou sugerir melhorias!

---

### 👨‍💻 Autor

- Carlos Eduardo Pereira dos Santos

---
