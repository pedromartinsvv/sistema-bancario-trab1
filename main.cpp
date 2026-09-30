#include <iostream>
#include <string>

using namespace std;

int main() {

    // Nome do sistema
    const int MAX_CONTAS = 5;

    // Variaveis para armazenar ate 5 contas
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];

    int quantidadeContas = 0;
    int opcao;
    int numeroBusca;
    int posicao;
    bool encontrada;

    do {

        cout << "\n********************************" << endl;
        cout << "       BANCO INF101" << endl;
        cout << "********************************" << endl;

        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Consultar conta" << endl;
        cout << "3 - Verificar saldo" << endl;
        cout << "4 - Alterar tipo da conta" << endl;
        cout << "5 - Ativar/Desativar conta" << endl;
        cout << "6 - Sair" << endl;

        cout << "\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {

            // ==========================================
            // 1 - CADASTRAR CONTA
            // ==========================================
            case 1:

                if (quantidadeContas >= MAX_CONTAS) {
                    cout << "\nLimite de 5 contas atingido!" << endl;
                    break;
                }

                cout << "\n--- CADASTRO DE CONTA ---" << endl;

                // Validacao do numero da conta
                do {
                    cout << "Numero da conta: ";
                    cin >> numeroConta[quantidadeContas];

                    if (numeroConta[quantidadeContas] <= 0) {
                        cout << "O numero da conta deve ser maior que zero." << endl;
                    }

                } while (numeroConta[quantidadeContas] <= 0);

                cin.ignore();

                cout << "Nome do titular: ";
                getline(cin, nomeCliente[quantidadeContas]);

                cout << "CPF: ";
                getline(cin, cpf[quantidadeContas]);

                // Validacao do tipo da conta
                do {
                    cout << "Tipo da conta (1 - Corrente / 2 - Poupanca): ";
                    cin >> tipoConta[quantidadeContas];

                    if (tipoConta[quantidadeContas] != 1 &&
                        tipoConta[quantidadeContas] != 2) {

                        cout << "Tipo de conta invalido." << endl;
                    }

                } while (tipoConta[quantidadeContas] != 1 &&
                         tipoConta[quantidadeContas] != 2);

                // Validacao do saldo inicial
                do {
                    cout << "Saldo inicial: R$ ";
                    cin >> saldo[quantidadeContas];

                    if (saldo[quantidadeContas] < 0) {
                        cout << "O saldo nao pode ser negativo." << endl;
                    }

                } while (saldo[quantidadeContas] < 0);

                // Toda nova conta comeca ativa
                contaAtiva[quantidadeContas] = true;

                quantidadeContas++;

                cout << "\nConta cadastrada com sucesso!" << endl;

                break;


            // ==========================================
            // 2 - CONSULTAR CONTA
            // ==========================================
            case 2:

                cout << "\nDigite o numero da conta: ";
                cin >> numeroBusca;

                encontrada = false;

                for (int i = 0; i < quantidadeContas; i++) {

                    if (numeroConta[i] == numeroBusca) {

                        encontrada = true;

                        cout << "\n--- DADOS DA CONTA ---" << endl;
                        cout << "Numero: " << numeroConta[i] << endl;
                        cout << "Titular: " << nomeCliente[i] << endl;
                        cout << "CPF: " << cpf[i] << endl;

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

                        break;
                    }
                }

                if (!encontrada) {
                    cout << "\nConta nao encontrada." << endl;
                }

                break;


            // ==========================================
            // 3 - VERIFICAR SALDO
            // ==========================================
            case 3:

                cout << "\nDigite o numero da conta: ";
                cin >> numeroBusca;

                encontrada = false;

                for (int i = 0; i < quantidadeContas; i++) {

                    if (numeroConta[i] == numeroBusca) {

                        encontrada = true;

                        if (contaAtiva[i]) {

                            cout << "Titular: "
                                 << nomeCliente[i] << endl;

                            cout << "Saldo atual: R$ "
                                 << saldo[i] << endl;

                        } else {

                            cout << "A conta esta inativa." << endl;
                        }

                        break;
                    }
                }

                if (!encontrada) {
                    cout << "\nConta nao encontrada." << endl;
                }

                break;


            // ==========================================
            // 4 - ALTERAR TIPO DA CONTA
            // ==========================================
            case 4:

                cout << "\nDigite o numero da conta: ";
                cin >> numeroBusca;

                encontrada = false;
                posicao = -1;

                for (int i = 0; i < quantidadeContas; i++) {

                    if (numeroConta[i] == numeroBusca) {
                        encontrada = true;
                        posicao = i;
                        break;
                    }
                }

                if (!encontrada) {

                    cout << "\nConta nao encontrada." << endl;

                } else if (!contaAtiva[posicao]) {

                    cout << "\nA conta esta inativa." << endl;

                } else {

                    do {

                        cout << "Novo tipo (1 - Corrente / 2 - Poupanca): ";
                        cin >> tipoConta[posicao];

                        if (tipoConta[posicao] != 1 &&
                            tipoConta[posicao] != 2) {

                            cout << "Tipo invalido." << endl;
                        }

                    } while (tipoConta[posicao] != 1 &&
                             tipoConta[posicao] != 2);

                    cout << "\nTipo da conta alterado com sucesso!" << endl;
                }

                break;


            // ==========================================
            // 5 - ATIVAR / DESATIVAR CONTA
            // ==========================================
            case 5:

                cout << "\nDigite o numero da conta: ";
                cin >> numeroBusca;

                encontrada = false;

                for (int i = 0; i < quantidadeContas; i++) {

                    if (numeroConta[i] == numeroBusca) {

                        encontrada = true;

                        contaAtiva[i] = !contaAtiva[i];

                        if (contaAtiva[i]) {

                            cout << "\nConta ativada com sucesso!" << endl;

                        } else {

                            cout << "\nConta desativada com sucesso!" << endl;
                        }

                        break;
                    }
                }

                if (!encontrada) {
                    cout << "\nConta nao encontrada." << endl;
                }

                break;


            // ==========================================
            // 6 - SAIR
            // ==========================================
            case 6:

                cout << "\nEncerrando o BANCO INF101..." << endl;
                cout << "Obrigado por utilizar nosso sistema!" << endl;

                break;


            default:

                cout << "\nOpcao invalida!" << endl;
        }

    } while (opcao != 6);

    return 0;
}
