#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

// Limites do sistema
const int MAX_CONTAS = 100;
const int MAX_MOVIMENTACOES = 500;

// Dados das contas
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];
int quantidadeContas = 0;

// Historico de movimentacoes
int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];
double valorMovimentacao[MAX_MOVIMENTACOES];
int quantidadeMovimentacoes = 0;

// Leitura segura de numeros inteiros
int lerInteiro(string mensagem) {
    int valor;

    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            return valor;
        }

        cout << "Entrada invalida! Digite um numero inteiro." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Leitura segura de valores reais
double lerReal(string mensagem) {
    double valor;

    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            return valor;
        }

        cout << "Entrada invalida! Digite um valor numerico." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Localiza uma conta pelo numero
int buscarConta(int numero) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }

    return -1;
}

// Carrega as contas salvas no arquivo
void carregarContas() {
    ifstream arquivo("contas.txt");
    string linha;

    quantidadeContas = 0;

    if (!arquivo.is_open()) {
        return;
    }

    while (getline(arquivo, linha) && quantidadeContas < MAX_CONTAS) {
        stringstream dados(linha);
        string campo;
        int numero, tipo, ativa;
        string nome, documento;
        double valorSaldo;

        if (!getline(dados, campo, ';')) continue;
        stringstream(campo) >> numero;

        if (!getline(dados, nome, ';')) continue;
        if (!getline(dados, documento, ';')) continue;
        if (!getline(dados, campo, ';')) continue;
        stringstream(campo) >> tipo;

        if (!getline(dados, campo, ';')) continue;
        stringstream(campo) >> valorSaldo;

        if (!getline(dados, campo)) continue;
        stringstream(campo) >> ativa;

        // Ignora registros invalidos ou duplicados
        if (numero <= 0 || (tipo != 1 && tipo != 2) ||
            valorSaldo < 0 || (ativa != 0 && ativa != 1) ||
            buscarConta(numero) != -1) {
            continue;
        }

        numeroConta[quantidadeContas] = numero;
        nomeCliente[quantidadeContas] = nome;
        cpf[quantidadeContas] = documento;
        tipoConta[quantidadeContas] = tipo;
        saldo[quantidadeContas] = valorSaldo;
        contaAtiva[quantidadeContas] = (ativa == 1);
        quantidadeContas++;
    }

    arquivo.close();
}

// Salva todas as contas no arquivo
bool salvarContas() {
    ofstream arquivo("contas.txt");

    if (!arquivo.is_open()) {
        cout << "Erro: nao foi possivel salvar contas.txt!" << endl;
        return false;
    }

    arquivo << fixed << setprecision(2);

    for (int i = 0; i < quantidadeContas; i++) {
        arquivo << numeroConta[i] << ";"
                << nomeCliente[i] << ";"
                << cpf[i] << ";"
                << tipoConta[i] << ";"
                << saldo[i] << ";"
                << (contaAtiva[i] ? 1 : 0) << endl;
    }

    arquivo.close();

    if (arquivo.fail()) {
        cout << "Erro durante a gravacao de contas.txt!" << endl;
        return false;
    }

    return true;
}

// Carrega o historico de movimentacoes
void carregarMovimentacoes() {
    ifstream arquivo("movimentacoes.txt");
    string linha;

    quantidadeMovimentacoes = 0;

    if (!arquivo.is_open()) {
        return;
    }

    while (getline(arquivo, linha) &&
           quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
        stringstream dados(linha);
        string campo;
        int numero;
        char tipo;
        double valor;

        if (!getline(dados, campo, ';')) continue;
        stringstream(campo) >> numero;

        if (!getline(dados, campo, ';') || campo.empty()) continue;
        tipo = campo[0];

        if (!getline(dados, campo)) continue;
        stringstream(campo) >> valor;

        if (numero <= 0 || (tipo != 'D' && tipo != 'S') || valor <= 0) {
            continue;
        }

        contaMovimentacao[quantidadeMovimentacoes] = numero;
        tipoMovimentacao[quantidadeMovimentacoes] = tipo;
        valorMovimentacao[quantidadeMovimentacoes] = valor;
        quantidadeMovimentacoes++;
    }

    arquivo.close();
}

// Salva o historico de movimentacoes
bool salvarMovimentacoes() {
    ofstream arquivo("movimentacoes.txt");

    if (!arquivo.is_open()) {
        cout << "Erro: nao foi possivel salvar movimentacoes.txt!" << endl;
        return false;
    }

    arquivo << fixed << setprecision(2);

    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        arquivo << contaMovimentacao[i] << ";"
                << tipoMovimentacao[i] << ";"
                << valorMovimentacao[i] << endl;
    }

    arquivo.close();

    if (arquivo.fail()) {
        cout << "Erro durante a gravacao de movimentacoes.txt!" << endl;
        return false;
    }

    return true;
}

int main() {
    int opcao;
    int numeroBusca;
    int numeroDestino;
    int indice;
    int indiceOrigem;
    int indiceDestino;
    int tipoNovo;
    double valor;
    bool encontrada;

    // Recupera os dados salvos anteriormente
    carregarContas();
    carregarMovimentacoes();

    cout << fixed << setprecision(2);

    cout << "\nDados carregados: " << quantidadeContas
         << " conta(s) e " << quantidadeMovimentacoes
         << " movimentacao(oes)." << endl;

    do {
        cout << "\n************************************" << endl;
        cout << "           BANCO INF101" << endl;
        cout << "************************************" << endl;
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Listar contas" << endl;
        cout << "3 - Consultar conta" << endl;
        cout << "4 - Realizar deposito" << endl;
        cout << "5 - Realizar saque" << endl;
        cout << "6 - Realizar transferencia" << endl;
        cout << "7 - Exibir extrato" << endl;
        cout << "8 - Alterar tipo da conta" << endl;
        cout << "9 - Ativar/Desativar conta" << endl;
        cout << "10 - Sair" << endl;

        opcao = lerInteiro("\nEscolha uma opcao: ");

        switch (opcao) {
            case 1:
                if (quantidadeContas >= MAX_CONTAS) {
                    cout << "\nLimite de 100 contas atingido!" << endl;
                    break;
                }

                cout << "\n--- CADASTRO DE CONTA ---" << endl;

                do {
                    numeroBusca = lerInteiro("Numero da conta: ");

                    if (numeroBusca <= 0) {
                        cout << "O numero deve ser maior que zero!" << endl;
                    } else if (buscarConta(numeroBusca) != -1) {
                        cout << "Essa conta ja esta cadastrada!" << endl;
                    }
                } while (numeroBusca <= 0 || buscarConta(numeroBusca) != -1);

                numeroConta[quantidadeContas] = numeroBusca;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nome do titular: ";
                getline(cin, nomeCliente[quantidadeContas]);

                cout << "CPF: ";
                getline(cin, cpf[quantidadeContas]);

                do {
                    tipoNovo = lerInteiro("Tipo (1 - Corrente / 2 - Poupanca): ");
                    if (tipoNovo != 1 && tipoNovo != 2) {
                        cout << "Tipo de conta invalido!" << endl;
                    }
                } while (tipoNovo != 1 && tipoNovo != 2);

                tipoConta[quantidadeContas] = tipoNovo;

                do {
                    saldo[quantidadeContas] = lerReal("Saldo inicial: R$ ");
                    if (saldo[quantidadeContas] < 0) {
                        cout << "O saldo nao pode ser negativo!" << endl;
                    }
                } while (saldo[quantidadeContas] < 0);

                contaAtiva[quantidadeContas] = true;
                quantidadeContas++;

                if (salvarContas()) {
                    cout << "\nConta cadastrada e salva com sucesso!" << endl;
                }
                break;

            case 2:
                if (quantidadeContas == 0) {
                    cout << "\nNenhuma conta cadastrada." << endl;
                    break;
                }

                cout << "\n--- CONTAS CADASTRADAS ---" << endl;
                for (int i = 0; i < quantidadeContas; i++) {
                    cout << "\nNumero: " << numeroConta[i] << endl;
                    cout << "Titular: " << nomeCliente[i] << endl;
                    cout << "CPF: " << cpf[i] << endl;
                    cout << "Tipo: "
                         << (tipoConta[i] == 1 ? "Conta Corrente" : "Conta Poupanca")
                         << endl;
                    cout << "Saldo: R$ " << saldo[i] << endl;
                    cout << "Situacao: "
                         << (contaAtiva[i] ? "Ativa" : "Inativa") << endl;
                }
                break;

            case 3:
                numeroBusca = lerInteiro("\nNumero da conta: ");
                indice = buscarConta(numeroBusca);

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else {
                    cout << "\n--- DADOS DA CONTA ---" << endl;
                    cout << "Numero: " << numeroConta[indice] << endl;
                    cout << "Titular: " << nomeCliente[indice] << endl;
                    cout << "CPF: " << cpf[indice] << endl;
                    cout << "Tipo: "
                         << (tipoConta[indice] == 1 ? "Conta Corrente" : "Conta Poupanca")
                         << endl;
                    cout << "Saldo: R$ " << saldo[indice] << endl;
                    cout << "Situacao: "
                         << (contaAtiva[indice] ? "Ativa" : "Inativa") << endl;
                }
                break;

            case 4:
                if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    cout << "\nLimite de movimentacoes atingido!" << endl;
                    break;
                }

                numeroBusca = lerInteiro("\nNumero da conta: ");
                indice = buscarConta(numeroBusca);

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "\nConta inativa! Deposito nao permitido." << endl;
                } else {
                    do {
                        valor = lerReal("Valor do deposito: R$ ");
                        if (valor <= 0) {
                            cout << "O valor deve ser positivo!" << endl;
                        }
                    } while (valor <= 0);

                    saldo[indice] += valor;
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    salvarContas();
                    salvarMovimentacoes();

                    cout << "\nDeposito realizado!" << endl;
                    cout << "Novo saldo: R$ " << saldo[indice] << endl;
                }
                break;

            case 5:
                if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    cout << "\nLimite de movimentacoes atingido!" << endl;
                    break;
                }

                numeroBusca = lerInteiro("\nNumero da conta: ");
                indice = buscarConta(numeroBusca);

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "\nConta inativa! Saque nao permitido." << endl;
                } else {
                    do {
                        valor = lerReal("Valor do saque: R$ ");

                        if (valor <= 0) {
                            cout << "O valor deve ser positivo!" << endl;
                        } else if (valor > saldo[indice]) {
                            cout << "Saldo insuficiente!" << endl;
                        }
                    } while (valor <= 0 || valor > saldo[indice]);

                    saldo[indice] -= valor;
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    salvarContas();
                    salvarMovimentacoes();

                    cout << "\nSaque realizado!" << endl;
                    cout << "Novo saldo: R$ " << saldo[indice] << endl;
                }
                break;

            case 6:
                if (quantidadeMovimentacoes > MAX_MOVIMENTACOES - 2) {
                    cout << "\nNao ha espaco para registrar a transferencia!" << endl;
                    break;
                }

                numeroBusca = lerInteiro("\nConta de origem: ");
                numeroDestino = lerInteiro("Conta de destino: ");

                indiceOrigem = buscarConta(numeroBusca);
                indiceDestino = buscarConta(numeroDestino);

                if (indiceOrigem == -1 || indiceDestino == -1) {
                    cout << "\nUma ou ambas as contas nao foram encontradas!" << endl;
                } else if (indiceOrigem == indiceDestino) {
                    cout << "\nNao e permitido transferir para a mesma conta!" << endl;
                } else if (!contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) {
                    cout << "\nAs duas contas devem estar ativas!" << endl;
                } else {
                    do {
                        valor = lerReal("Valor da transferencia: R$ ");

                        if (valor <= 0) {
                            cout << "O valor deve ser positivo!" << endl;
                        } else if (valor > saldo[indiceOrigem]) {
                            cout << "Saldo insuficiente!" << endl;
                        }
                    } while (valor <= 0 || valor > saldo[indiceOrigem]);

                    saldo[indiceOrigem] -= valor;
                    saldo[indiceDestino] += valor;

                    // Registra a saida da conta de origem
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    // Registra a entrada na conta de destino
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    salvarContas();
                    salvarMovimentacoes();

                    cout << "\nTransferencia realizada!" << endl;
                    cout << "Saldo da origem: R$ " << saldo[indiceOrigem] << endl;
                    cout << "Saldo do destino: R$ " << saldo[indiceDestino] << endl;
                }
                break;

            case 7:
                numeroBusca = lerInteiro("\nNumero da conta: ");
                indice = buscarConta(numeroBusca);

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else {
                    cout << "\n--- EXTRATO BANCARIO ---" << endl;
                    cout << "Conta: " << numeroConta[indice] << endl;
                    cout << "Titular: " << nomeCliente[indice] << endl;

                    encontrada = false;

                    for (int i = 0; i < quantidadeMovimentacoes; i++) {
                        if (contaMovimentacao[i] == numeroBusca) {
                            encontrada = true;

                            if (tipoMovimentacao[i] == 'D') {
                                cout << "Deposito/Entrada: R$ ";
                            } else {
                                cout << "Saque/Saida: R$ ";
                            }

                            cout << valorMovimentacao[i] << endl;
                        }
                    }

                    if (!encontrada) {
                        cout << "Nenhuma movimentacao registrada." << endl;
                    }

                    cout << "Saldo atual: R$ " << saldo[indice] << endl;
                }
                break;

            case 8:
                numeroBusca = lerInteiro("\nNumero da conta: ");
                indice = buscarConta(numeroBusca);

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "\nConta inativa!" << endl;
                } else {
                    do {
                        tipoNovo = lerInteiro("Novo tipo (1-Corrente / 2-Poupanca): ");
                        if (tipoNovo != 1 && tipoNovo != 2) {
                            cout << "Tipo invalido!" << endl;
                        }
                    } while (tipoNovo != 1 && tipoNovo != 2);

                    tipoConta[indice] = tipoNovo;
                    salvarContas();
                    cout << "\nTipo de conta alterado!" << endl;
                }
                break;

            case 9:
                numeroBusca = lerInteiro("\nNumero da conta: ");
                indice = buscarConta(numeroBusca);

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else {
                    contaAtiva[indice] = !contaAtiva[indice];
                    salvarContas();

                    if (contaAtiva[indice]) {
                        cout << "\nConta ativada com sucesso!" << endl;
                    } else {
                        cout << "\nConta desativada com sucesso!" << endl;
                    }
                }
                break;

            case 10:
                cout << "\nEncerrando o BANCO INF101..." << endl;
                salvarContas();
                salvarMovimentacoes();
                cout << "Dados salvos. Obrigado por utilizar nosso sistema!" << endl;
                break;

            default:
                cout << "\nOpcao invalida! Tente novamente." << endl;
        }

    } while (opcao != 10);

    return 0;
}
