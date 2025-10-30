#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Classe de base
class Funcionario {
protected:
    string nome, id, cargo;
public:
    Funcionario(string n, string i, string c) : nome(n), id(i), cargo(c) {}
    virtual void info() { cout << nome << " (" << cargo << ")" << endl; }
};

// Classes derivadas
class Gerente : public Funcionario {
public:
    Gerente(string n, string i) : Funcionario(n, i, "Gerente") {}
};

class Cozinheiro : public Funcionario {
public:
    Cozinheiro(string n, string i) : Funcionario(n, i, "Cozinheiro") {}
};

class Garcom : public Funcionario {
public:
    Garcom(string n, string i) : Funcionario(n, i, "Garcom") {}
};

class Recepcionista : public Funcionario {
public:
    Recepcionista(string n, string i) : Funcionario(n, i, "Recepcionista") {}
};

// Classes de domínio
class Mesa { 
public: 
    int numero; 
    bool disponivel;
    Mesa(int n) : numero(n), disponivel(true) {}
    void info() { cout << "Mesa " << numero << " - " << (disponivel ? "Livre" : "Ocupada") << endl; }
};

class Prato {
public:
    string nome;
    double preco;
    Prato(string n, double p) : nome(n), preco(p) {}
    void info() { cout << nome << " - R$ " << preco << endl; }
};

class Pedido {
public:
    int mesa;
    vector<Prato*> itens;
    Pedido(int m) : mesa(m) {}
    double total() {
        double t = 0;
        for (auto p : itens) t += p->preco;
        return t;
    }
};

class Reserva {
public:
    string cliente;
    int mesa;
    string data;
    Reserva(string c, int m, string d) : cliente(c), mesa(m), data(d) {}
    void info() { cout << cliente << " - Mesa " << mesa << " - " << data << endl; }
};

// Sistema principal compacto
class Restaurante {
    vector<Funcionario*> funcs;
    vector<Mesa> mesas;
    vector<Prato*> cardapio;
    vector<Pedido> pedidos;
    vector<Reserva> reservas;

public:
    Restaurante() {
        for (int i = 1; i <= 8; i++) mesas.push_back(Mesa(i));
        
        cardapio.push_back(new Prato("Feijoada", 35.90));
        cardapio.push_back(new Prato("Strogonoff", 28.50));
        cardapio.push_back(new Prato("Salada", 22.00));
        cardapio.push_back(new Prato("Battom", 999.99));

        funcs.push_back(new Gerente("Tio Patinhas", "G001"));
        funcs.push_back(new Cozinheiro("Creuza", "C001"));
        funcs.push_back(new Garcom("Tiringa", "W001"));
        funcs.push_back(new Garcom("Rossi", "W002"));
        funcs.push_back(new Recepcionista("Dora", "R001"));
    }

    void menuPrincipal() {
        int opcao;
        do {
            cout << endl << "=== RESTAURANTE ===" << endl << endl;
            cout << "[1] Gerente" << endl << "[2] Cozinheiro" << endl << "[3] Garcom" << endl << "[4] Recepcionista" << endl << "[0] Sair" << endl << endl << "Opcao: ";
            cin >> opcao;
            cout << endl;

            if (opcao == 1) menuGerente();
            else if (opcao == 2) menuCozinheiro();
            else if (opcao == 3) menuGarcom();
            else if (opcao == 4) menuRecepcionista();
        } while (opcao != 0);
    }

private:
    void menuGerente() {
        int opcao;
        do {
            cout << endl << "--- GERENTE ---" << endl;
            cout << "[1] Ver Funcionarios" << endl << "[2] Ver Mesas" << endl << "[3] Cardapio" << endl << "[4] Fechar Conta" << endl << "[0] Voltar" << endl << endl << "Opcao: ";
            cin >> opcao;
            cout << endl;

            if (opcao == 1) {
                cout << endl << "--- FUNCIONARIOS ---" << endl;
                for (auto f : funcs) f->info();
            }
            else if (opcao == 2) {
                cout << endl << "--- MESAS ---" << endl;
                for (auto m : mesas) m.info();
            }
            else if (opcao == 3) menuCardapio();
            else if (opcao == 4) fecharConta();
        } while (opcao != 0);
    }

    void menuCozinheiro() {
        int opcao;
        do {
            cout << endl << "--- COZINHEIRO ---" << endl;
            cout << "[1] Ver Cardapio" << endl << "[2] Add Prato" << endl << "[3] Remover Prato" << endl << "[0] Voltar" << endl << "Opcao: ";
            cin >> opcao;
            if (opcao == 1) menuCardapio();
            else if (opcao == 2) {
                string nome; double preco;
                cout << "Nome: "; 
                cin.ignore();
                getline(cin, nome);
                cout << "Preco: "; cin >> preco;
                cardapio.push_back(new Prato(nome, preco));
                cout << "Prato adicionado!" << endl;
            }
            else if (opcao == 3) {
                menuCardapio();
                int idx; cout << "Numero para remover: "; cin >> idx;
                if (idx > 0 && idx <= cardapio.size()) {
                    delete cardapio[idx-1];
                    cardapio.erase(cardapio.begin() + idx-1);
                    cout << "Removido!" << endl;
                }
            }
        } while (opcao != 0);
    }

    void menuGarcom() {
        int opcao;
        do {
            cout << endl << "--- GARCOM ---" << endl;
            cout << "[1] Fazer Pedido" << endl << "[2] Fechar Conta" << endl << "[0] Voltar" << endl << endl << "Opcao: ";
            cin >> opcao;
            if (opcao == 1) fazerPedido();
            else if (opcao == 2) fecharConta();
        } while (opcao != 0);
    }

    void menuRecepcionista() {
        int opcao;
        do {
            cout << endl << "--- RECEPCIONISTA ---" << endl;
            cout << "[1] Ver Mesas" << endl << "[2] Fazer Reserva" << endl << "[3] Ver Reservas" << endl << "[0] Voltar" << endl << endl << "Opcao: ";
            cin >> opcao;
            if (opcao == 1) { for (auto m : mesas) m.info(); }
            else if (opcao == 2) {
                string nome, data; 
                int mesa;
                
                cout << "Cliente: "; 
                cin.ignore();
                getline(cin, nome);
                cout << "Mesa: ";
                cin >> mesa;
                cin.ignore();
                cout << "Data (DD/MM/AAAA): ";
                getline(cin, data);

                if (mesa > 0 && mesa <= mesas.size()) {
                    if (mesas[mesa-1].disponivel) {
                        reservas.push_back(Reserva(nome, mesa, data));
                        mesas[mesa-1].disponivel = false;
                        cout << "Mesa reservada com sucesso!" << endl;
                    } else {
                        cout << "Mesa já está ocupada ou reservada!" << endl;
                    }
                } else {
                    cout << "Número de mesa inválido!" << endl;
                }
            }
            else if (opcao == 3) {
                for (int i = 0; i < reservas.size(); i++) {
                    cout << i+1 << ". "; reservas[i].info();
                }
            }
        } while (opcao != 0);
    }

    void menuCardapio() {
        cout << endl << "--- CARDAPIO ---" << endl << endl;
        for (int i = 0; i < cardapio.size(); i++) {
            cout << i+1 << ". "; cardapio[i]->info();
        }
    }

    void fazerPedido() {
        int mesa;
        cout << "Mesa: "; cin >> mesa;
        
        if (mesa <= 0 || mesa > mesas.size()) {
            cout << "Número de mesa inválido!" << endl;
            return;
        }

        if (!mesas[mesa-1].disponivel) {
            Pedido pedido(mesa);
            
            int opcao;
            do {
                menuCardapio();
                cout << "[0] Finalizar" << endl << endl << "Prato: ";
                cin >> opcao;

                if (opcao > 0 && opcao <= cardapio.size()) {
                    pedido.itens.push_back(cardapio[opcao-1]);
                    cout << "Adicionado!" << endl;
                }
            } while (opcao != 0);
            
            pedidos.push_back(pedido);
        } else {
            cout << "Mesa não está ocupada ou reservada!" << endl;
        }
    }

    void fecharConta() {
        int mesa;
        cout << "Mesa para fechar: ";
        cin >> mesa;
        
        if (mesa <= 0 || mesa > mesas.size()) {
            cout << "Número de mesa inválido!" << endl;
            return;
        }

        for (auto& pedido : pedidos) {
            if (pedido.mesa == mesa) {
                cout << endl << "====== CONTA DA MESA " << mesa << " ======" << endl << endl;
                for (auto item : pedido.itens) item->info();
                cout <<"---------------------" << endl << "TOTAL: R$ " << pedido.total() << endl << endl;
                
                // Libera a mesa
                mesas[mesa-1].disponivel = true;
                
                // Remove a reserva se existir
                for (int i = 0; i < reservas.size(); i++) {
                    if (reservas[i].mesa == mesa) {
                        reservas.erase(reservas.begin() + i);
                        break;
                    }
                }
                
                cout << "Mesa liberada!" << endl;
                return;
            }
        }
        cout << "Mesa sem pedidos!" << endl;
    }
};

// Main
int main() {
    Restaurante r;
    r.menuPrincipal();
    return 0;
}