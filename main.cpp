#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {

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

    // Variaveis auxiliares
    int opcao;
    int numeroBusca;
    int numeroDestino;
    int indice;
    int indiceOrigem;
    int indiceDestino;
    int tipoNovo;
    double valor;
    bool encontrada;

    do {
        cout << fixed << setprecision(2);

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

        cout << "\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {

            // 1 - Cadastrar conta
            case 1:

                if (quantidadeContas >= MAX_CONTAS) {
                    cout << "\nLimite de 100 contas atingido!" << endl;
                    break;
                }

                cout << "\n--- CADASTRO DE CONTA ---" << endl;

                // Validar numero positivo e evitar contas duplicadas
                do {
                    cout << "Numero da conta: ";
                    cin >> numeroConta[quantidadeContas];

                    encontrada = false;

                    for (int i = 0; i < quantidadeContas; i++) {
                        if (numeroConta[i] == numeroConta[quantidadeContas]) {
                            encontrada = true;
                            break;
                        }
                    }

                    if (numeroConta[quantidadeContas] <= 0) {
                        cout << "O numero deve ser maior que zero!" << endl;
                    } else if (encontrada) {
                        cout << "Essa conta ja esta cadastrada!" << endl;
                    }

                } while (numeroConta[quantidadeContas] <= 0 || encontrada);

                cin.ignore();

                cout << "Nome do titular: ";
                getline(cin, nomeCliente[quantidadeContas]);

                cout << "CPF: ";
                getline(cin, cpf[quantidadeContas]);

                // Validar tipo da conta
                do {
                    cout << "Tipo (1 - Corrente / 2 - Poupanca): ";
                    cin >> tipoConta[quantidadeContas];

                    if (tipoConta[quantidadeContas] != 1 &&
                        tipoConta[quantidadeContas] != 2) {
                        cout << "Tipo de conta invalido!" << endl;
                    }

                } while (tipoConta[quantidadeContas] != 1 &&
                         tipoConta[quantidadeContas] != 2);

                // Validar saldo inicial
                do {
                    cout << "Saldo inicial: R$ ";
                    cin >> saldo[quantidadeContas];

                    if (saldo[quantidadeContas] < 0) {
                        cout << "O saldo nao pode ser negativo!" << endl;
                    }

                } while (saldo[quantidadeContas] < 0);

                contaAtiva[quantidadeContas] = true;
                quantidadeContas++;

                cout << "\nConta cadastrada com sucesso!" << endl;
                break;


            // 2 - Listar contas
            case 2:

                if (quantidadeContas == 0) {
                    cout << "\nNenhuma conta cadastrada." << endl;
                    break;
                }

                cout << "\n--- CONTAS CADASTRADAS ---" << endl;

                for (int i = 0; i < quantidadeContas; i++) {
                    cout << "\nNumero: " << numeroConta[i] << endl;
                    cout << "Titular: " << nomeCliente[i] << endl;

                    if (tipoConta[i] == 1) {
                        cout << "Tipo: Conta Corrente" << endl;
                    } else {
                        cout << "Tipo: Conta Poupanca" << endl;
                    }

                    cout << "Saldo: R$ " << saldo[i] << endl;

                    if (contaAtiva[i]) {
                        cout << "Situacao: Ativa" << endl;
                    } else {
                        cout << "Situacao: Inativa" << endl;
                    }
                }

                break;


            // 3 - Consultar conta
            case 3:

                cout << "\nNumero da conta: ";
                cin >> numeroBusca;

                indice = -1;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                        break;
                    }
                }

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else {
                    cout << "\n--- DADOS DA CONTA ---" << endl;
                    cout << "Numero: " << numeroConta[indice] << endl;
                    cout << "Titular: " << nomeCliente[indice] << endl;
                    cout << "CPF: " << cpf[indice] << endl;

                    if (tipoConta[indice] == 1) {
                        cout << "Tipo: Conta Corrente" << endl;
                    } else {
                        cout << "Tipo: Conta Poupanca" << endl;
                    }

                    cout << "Saldo: R$ " << saldo[indice] << endl;

                    if (contaAtiva[indice]) {
                        cout << "Situacao: Ativa" << endl;
                    } else {
                        cout << "Situacao: Inativa" << endl;
                    }
                }

                break;


            // 4 - Realizar deposito
            case 4:

                if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    cout << "\nLimite de movimentacoes atingido!" << endl;
                    break;
                }

                cout << "\nNumero da conta: ";
                cin >> numeroBusca;

                indice = -1;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                        break;
                    }
                }

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "\nConta inativa! Deposito nao permitido." << endl;
                } else {
                    do {
                        cout << "Valor do deposito: R$ ";
                        cin >> valor;

                        if (valor <= 0) {
                            cout << "O valor deve ser positivo!" << endl;
                        }
                    } while (valor <= 0);

                    saldo[indice] = saldo[indice] + valor;

                    // Registrar deposito no historico
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    cout << "\nDeposito realizado com sucesso!" << endl;
                    cout << "Novo saldo: R$ " << saldo[indice] << endl;
                }

                break;


            // 5 - Realizar saque
            case 5:

                if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    cout << "\nLimite de movimentacoes atingido!" << endl;
                    break;
                }

                cout << "\nNumero da conta: ";
                cin >> numeroBusca;

                indice = -1;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                        break;
                    }
                }

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "\nConta inativa! Saque nao permitido." << endl;
                } else {
                    do {
                        cout << "Valor do saque: R$ ";
                        cin >> valor;

                        if (valor <= 0) {
                            cout << "O valor deve ser positivo!" << endl;
                        } else if (valor > saldo[indice]) {
                            cout << "Saldo insuficiente!" << endl;
                        }
                    } while (valor <= 0 || valor > saldo[indice]);

                    saldo[indice] = saldo[indice] - valor;

                    // Registrar saque no historico
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    cout << "\nSaque realizado com sucesso!" << endl;
                    cout << "Novo saldo: R$ " << saldo[indice] << endl;
                }

                break;


            // 6 - Realizar transferencia
            case 6:

                // A transferencia precisa de dois espacos no historico
                if (quantidadeMovimentacoes > MAX_MOVIMENTACOES - 2) {
                    cout << "\nNao ha espaco para registrar a transferencia!" << endl;
                    break;
                }

                cout << "\nConta de origem: ";
                cin >> numeroBusca;

                cout << "Conta de destino: ";
                cin >> numeroDestino;

                indiceOrigem = -1;
                indiceDestino = -1;

                // Localizar as duas contas
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indiceOrigem = i;
                    }

                    if (numeroConta[i] == numeroDestino) {
                        indiceDestino = i;
                    }
                }

                if (indiceOrigem == -1 || indiceDestino == -1) {
                    cout << "\nUma ou ambas as contas nao foram encontradas!" << endl;
                } else if (indiceOrigem == indiceDestino) {
                    cout << "\nNao e permitido transferir para a mesma conta!" << endl;
                } else if (!contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) {
                    cout << "\nAs duas contas devem estar ativas!" << endl;
                } else {
                    do {
                        cout << "Valor da transferencia: R$ ";
                        cin >> valor;

                        if (valor <= 0) {
                            cout << "O valor deve ser positivo!" << endl;
                        } else if (valor > saldo[indiceOrigem]) {
                            cout << "Saldo insuficiente!" << endl;
                        }
                    } while (valor <= 0 || valor > saldo[indiceOrigem]);

                    // Atualizar os saldos
                    saldo[indiceOrigem] = saldo[indiceOrigem] - valor;
                    saldo[indiceDestino] = saldo[indiceDestino] + valor;

                    // Registrar saida da conta de origem
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    // Registrar entrada na conta de destino
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    cout << "\nTransferencia realizada com sucesso!" << endl;
                    cout << "Saldo da origem: R$ " << saldo[indiceOrigem] << endl;
                    cout << "Saldo do destino: R$ " << saldo[indiceDestino] << endl;
                }

                break;


            // 7 - Exibir extrato
            case 7:

                cout << "\nNumero da conta: ";
                cin >> numeroBusca;

                indice = -1;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                        break;
                    }
                }

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
                                cout << "Deposito/Entrada: R$ "
                                     << valorMovimentacao[i] << endl;
                            } else if (tipoMovimentacao[i] == 'S') {
                                cout << "Saque/Saida: R$ "
                                     << valorMovimentacao[i] << endl;
                            }
                        }
                    }

                    if (!encontrada) {
                        cout << "Nenhuma movimentacao registrada." << endl;
                    }

                    cout << "Saldo atual: R$ " << saldo[indice] << endl;
                }

                break;


            // 8 - Alterar tipo da conta (mantido da Etapa 1)
            case 8:

                cout << "\nNumero da conta: ";
                cin >> numeroBusca;

                indice = -1;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                        break;
                    }
                }

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "\nConta inativa!" << endl;
                } else {
                    do {
                        cout << "Novo tipo (1-Corrente / 2-Poupanca): ";
                        cin >> tipoNovo;

                        if (tipoNovo != 1 && tipoNovo != 2) {
                            cout << "Tipo invalido!" << endl;
                        }
                    } while (tipoNovo != 1 && tipoNovo != 2);

                    tipoConta[indice] = tipoNovo;
                    cout << "\nTipo de conta alterado com sucesso!" << endl;
                }

                break;


            // 9 - Ativar/Desativar conta (mantido da Etapa 1)
            case 9:

                cout << "\nNumero da conta: ";
                cin >> numeroBusca;

                indice = -1;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                        break;
                    }
                }

                if (indice == -1) {
                    cout << "\nConta nao encontrada!" << endl;
                } else {
                    contaAtiva[indice] = !contaAtiva[indice];

                    if (contaAtiva[indice]) {
                        cout << "\nConta ativada com sucesso!" << endl;
                    } else {
                        cout << "\nConta desativada com sucesso!" << endl;
                    }
                }

                break;


            // 10 - Sair
            case 10:

                cout << "\nEncerrando o BANCO INF101..." << endl;
                cout << "Obrigado por utilizar nosso sistema!" << endl;
                break;


            default:
                cout << "\nOpcao invalida! Tente novamente." << endl;
        }

    } while (opcao != 10);

    return 0;
}
