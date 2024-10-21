#include <iostream>
#include <string>
using namespace std;

// Classe Cliente que representa um cliente do banco
class Cliente {
private:
  string nome; // Nome do cliente
  string cpf;  // CPF do cliente

public:
  // Construtor que inicializa o nome e o CPF do cliente
  Cliente(string nome, string cpf) : nome(nome), cpf(cpf) {}

  // Método getter para acessar o nome do cliente
  string getNome() const { return nome; }
  // Método getter para acessar o CPF do cliente
  string getCpf() const { return cpf; }
};

// Classe ContaBancaria que representa uma conta bancária
class ContaBancaria {
private:
  int numero;       // Número da conta bancária
  double saldo;     // Saldo disponível na conta
  Cliente *titular; // Ponteiro para o objeto Cliente, que é o titular da conta

public:
  // Construtor que inicializa o número, titular e saldo da conta
  ContaBancaria(int numero, Cliente &titular, double saldo = 0.0)
      : numero(numero), saldo(saldo), titular(&titular) {}

  // Método para depositar um valor na conta
  void depositar(double valor) {
    saldo += valor; // Incrementa o saldo com o valor do depósito
    cout << "Depositado: R$ " << valor << " na conta " << numero << endl;
  }

  // Método para sacar um valor da conta
  void sacar(double valor) {
    if (saldo >= valor) { // Verifica se há saldo suficiente para o saque
      saldo -= valor;     // Subtrai o saldo com o valor do saque
      cout << "Sacado: R$ " << valor << " da conta " << numero << endl;
    } else {
      // Mensagem de erro se o saldo for insuficiente
      cout << "Saldo insuficiente para saque!" << endl;
    }
  }

  // Método para transferir um valor para outra conta
  void transferir(double valor, ContaBancaria &destino) {
    // Verifica se há saldo suficiente para a transferência
    if (saldo >= valor) {
      saldo -= valor;           // Subtrai o saldo com o valor da transferência
      destino.depositar(valor); // Deposita o valor na conta de destino
      cout << "Transferido: R$ " << valor << " da conta " << numero
           << " para a conta " << destino.getNumero() << endl;
    } else {
      // Mensagem de erro se o saldo for insuficiente
      cout << "Saldo insuficiente para transferência!" << endl;
    }
  }
  // Sobrecarga do método transferir para transferir um valor dividido entre
  // duas contas
  void transferir(double valor, ContaBancaria &destino1,
                  ContaBancaria &destino2) {
    // Verifica se há saldo suficiente para a transferência
    if (saldo >= valor) {
      saldo -= valor; // Subtrai o saldo com o valor total da transferência
      double valorDividido = valor / 2; // Divide o valor em duas partes iguais
      // Deposita metade na primeira conta de destino
      destino1.depositar(valorDividido);
      // Deposita metade na segunda conta de destino
      destino2.depositar(valorDividido);
      cout << "Transferido: R$ " << valorDividido << " para cada conta ("
           << destino1.getNumero() << " e " << destino2.getNumero()
           << ") da conta " << numero << endl;
    } else {
      // Mensagem de erro se o saldo for insuficiente
      cout << "Saldo insuficiente para transferência!" << endl;
    }
  }

  // Exibe o saldo atual da conta
  void exibirSaldo() const {
    cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
  }

  // Exibe as informações do titular e da conta
  void exibirInformacoes() const {
    cout << "Titular: " << titular->getNome() << ", CPF: " << titular->getCpf()
         << endl;
    cout << "Número da Conta: " << numero << ", Saldo: R$ " << saldo << endl;
  }

  // Método getter para acessar o número da conta
  int getNumero() const { return numero; }
};

int main() {
  // Clientes
  Cliente cliente1("Laura", "123.456.789-00");
  Cliente cliente2("Gabriel", "987.654.321-00");
  Cliente cliente3("Sofia", "012.345.678-00");

  // Contas bancárias com saldos iniciais
  ContaBancaria conta1(2001, cliente1, 5000.00);
  ContaBancaria conta2(2002, cliente2, 1200.00);
  ContaBancaria conta3(2003, cliente3, 800.00);

  // Exibe o saldo inicial da conta de Laura
  conta1.exibirSaldo();

  // Laura transfere R$1000 para Gabriel
  conta1.transferir(1000.00, conta2);

  // Laura transfere R$ 500 divididos entre Gabriel e Sofia
  conta1.transferir(500.00, conta2, conta3);

  // Exibe os saldos finais
  cout << endl;
  conta1.exibirInformacoes();
  conta2.exibirInformacoes();
  conta3.exibirInformacoes();

  return 0;
}