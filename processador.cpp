#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Usar o namespace std para facilitar a escrita
using namespace std;

int main() {
    // --- 1. Abrir os arquivos ---

    // ifstream (input file stream) para LER o arquivo de imagem original
    ifstream imagem_entrada("./entrada.ppm");

    // ofstream (output file stream) para ESCREVER o novo arquivo de imagem
    ofstream imagem_saida("./saida_modificada.ppm");

    // --- Verificação de Erro ---
    if (!imagem_entrada.is_open()) {
        cout << "Erro! Nao foi possivel abrir o arquivo de entrada." << endl;
        return 1; // Encerra o programa com um código de erro
    }
    if (!imagem_saida.is_open()) {
        cout << "Erro! Nao foi possivel criar o arquivo de saida." << endl;
        return 1; // Encerra o programa com um código de erro
    }

    // --- 2. Ler o Cabeçalho da Imagem de Entrada ---

    string tipo_imagem;
    int largura, altura, valor_max_cor;

    // Lê as informações do cabeçalho da imagem de entrada
    imagem_entrada >> tipo_imagem;
    imagem_entrada >> largura >> altura;
    imagem_entrada >> valor_max_cor;

    // Exibe no console as informações que foram lidas (bom para depuração)
    cout << "Imagem de entrada lida com sucesso:" << endl;
    cout << "Tipo: " << tipo_imagem << endl;
    cout << "Dimensoes: " << largura << "x" << altura << endl;
    cout << "Valor Max Cor: " << valor_max_cor << endl;

    // --- 3. Escrever o Cabeçalho na Imagem de Saída ---

    imagem_saida << tipo_imagem << endl;
    imagem_saida << largura << " " << altura << endl;
    imagem_saida << valor_max_cor << endl;


    // --- 4. Processar e Escrever os Pixels ---
    // Vamos criar uma imagem com a metade de cima VERMELHA e a metade de baixo AZUL.

    // Loop pelas linhas (altura)
    for (int y = 0; y < altura; y++) {
        // Loop pelas colunas (largura)
        for (int x = 0; x < largura; x++) {

            // Se a linha atual (y) estiver na primeira metade da imagem
            if (y < altura / 2) {
                // Escreve um pixel VERMELHO
                // R=255, G=0, B=0
                imagem_saida << "255 0 0 ";
            }
            // Senão, se a linha atual estiver na segunda metade
            else {
                // Escreve um pixel AZUL
                // R=0, G=0, B=255
                imagem_saida << "0 0 255 ";
            }
        }
        // Adiciona uma quebra de linha no arquivo de saída ao final de cada linha de pixels
        // Isso ajuda a manter o arquivo PPM organizado e legível
        imagem_saida << endl;
    }

    cout << "\nProcessamento concluido! A imagem 'saida_modificada.ppm' foi criada." << endl;

    // --- 5. Fechar os Arquivos ---
    imagem_entrada.close();
    imagem_saida.close();

    return 0; // Sucesso
}