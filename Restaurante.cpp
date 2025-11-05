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
    virtual void info() {
        cout << nome << " (" << cargo << " - " << id  << ")" << endl;
    }
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
    void info() {
        cout << "Mesa " << numero << " - " << (disponivel ? "Livre" : "Ocupada") << endl;
    }
};

class Prato {
public:
    string nome;
    double preco;
    Prato(string n, double p) : nome(n), preco(p) {}
    void info() {
        cout << nome << " - R$ " << preco << endl;
    }
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
    void info() {
        cout << cliente << " - Mesa " << mesa << " - " << data << endl;
    }
};

// Sistema principal
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

    ~Restaurante() {
        for (auto f : funcs) delete f;
        for (auto p : cardapio) delete p;
    }

    void menuPrincipal() {
        int opcao;
        do {
            cout << endl << "=== RESTAURANTE ===" << endl << endl;
            cout << "[1] Gerente" << endl
                 << "[2] Cozinheiro" << endl
                 << "[3] Garcom" << endl
                 << "[4] Recepcionista" << endl
                 << "[0] Sair" << endl << endl
                 << "Opcao: ";
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
            cout << "[1] Ver Funcionarios" << endl 
                 << "[2] Add Funcionario" << endl 
                 << "[3] Ver Mesas" << endl 
                 << "[4] Cardapio" << endl 
                 << "[5] Fechar Conta" << endl 
                 << "[0] Voltar" << endl << endl 
                 << "Opcao: ";
            cin >> opcao;
            cout << endl;

            if (opcao == 1) {
                cout << endl << "--- FUNCIONARIOS ---" << endl;
                for (auto f : funcs) f->info();
            }
            else if (opcao == 2) adicionarFuncionario();
            else if (opcao == 3) {
                cout << endl << "--- MESAS ---" << endl;
                for (auto m : mesas) m.info();
            }
            else if (opcao == 4) menuCardapio();
            else if (opcao == 5) fecharConta();
        } while (opcao != 0);
    }

    void adicionarFuncionario() {
        string nome, id;
        int tipo;
        
        cout << "Nome: "; 
        cin.ignore();
        getline(cin, nome);
        cout << "ID: "; 
        cin >> id;
        cout << "Tipo (1-Gerente, 2-Cozinheiro, 3-Garcom, 4-Recepcionista): "; 
        cin >> tipo;
        
        if (tipo == 1) funcs.push_back(new Gerente(nome, id));
        else if (tipo == 2) funcs.push_back(new Cozinheiro(nome, id));
        else if (tipo == 3) funcs.push_back(new Garcom(nome, id));
        else if (tipo == 4) funcs.push_back(new Recepcionista(nome, id));
        else {
            cout << "Tipo invalido!" << endl;
            return;
        }
        
        cout << "Funcionario adicionado com sucesso!" << endl;
    }

    void menuCozinheiro() {
        int opcao;
        do {
            cout << endl << "--- COZINHEIRO ---" << endl;
            cout << "[1] Ver Cardapio" << endl 
                 << "[2] Add Prato" << endl 
                 << "[3] Remover Prato" << endl 
                 << "[0] Voltar" << endl << endl 
                 << "Opcao: "; 
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
            cout << "[1] Fazer Pedido" << endl 
                 << "[2] Fechar Conta" << endl 
                 << "[0] Voltar" << endl << endl 
                 << "Opcao: ";
            cin >> opcao;
            if (opcao == 1) fazerPedido();
            else if (opcao == 2) fecharConta();
        } while (opcao != 0);
    }

    void menuRecepcionista() {
        int opcao;
        do {
            cout << endl << "--- RECEPCIONISTA ---" << endl;
            cout << "[1] Ver Mesas" << endl 
                 << "[2] Fazer Reserva" << endl 
                 << "[3] Ver Reservas" << endl 
                 << "[4] Cancelar Reserva" << endl 
                 << "[0] Voltar" << endl << endl
                 << "Opcao: ";
            cin >> opcao;
            if (opcao == 1) { 
                cout << endl << "--- MESAS ---" << endl;
                for (auto m : mesas) m.info(); 
            }
            else if (opcao == 2) fazerReserva();
            else if (opcao == 3) verReservas();
            else if (opcao == 4) cancelarReserva();
        } while (opcao != 0);
    }

    void fazerReserva() {
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
            cout << "Numero de mesa invalido!" << endl;
        }
    }

    void verReservas() {
        if (reservas.empty()) {
            cout << "Nenhuma reserva cadastrada!" << endl;
            return;
        }
        cout << endl << "--- RESERVAS ---" << endl;
        for (int i = 0; i < reservas.size(); i++) {
            cout << i+1 << ". "; reservas[i].info();
        }
    }

    void cancelarReserva() {
        if (reservas.empty()) {
            cout << "Nenhuma reserva cadastrada!" << endl;
            return;
        }
        
        verReservas();
        int idx;
        cout << endl << "Numero da reserva para cancelar: "; 
        cin >> idx;
        
        if (idx > 0 && idx <= reservas.size()) {
            int mesa = reservas[idx-1].mesa;
            mesas[mesa-1].disponivel = true;
            reservas.erase(reservas.begin() + idx-1);
            cout << "Reserva cancelada! Mesa " << mesa << " liberada." << endl;
        } else {
            cout << "Numero invalido!" << endl;
        }
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
            cout << "Numero de mesa invalido!" << endl;
            return;
        }

        if (!mesas[mesa-1].disponivel) {
            Pedido pedido(mesa);
            
            int opcao;
            do {
                menuCardapio();
                cout << "[0] Finalizar" << endl << endl
                     << "Prato: ";
                cin >> opcao;

                if (opcao > 0 && opcao <= cardapio.size()) {
                    pedido.itens.push_back(cardapio[opcao-1]);
                    cout << "Adicionado!" << endl;
                }
            } while (opcao != 0);
            
            pedidos.push_back(pedido);
            cout << "Pedido registrado para a mesa " << mesa << "!" << endl;
        } else {
            cout << "Mesa nao esta ocupada! Faca reserva primeiro." << endl;
        }
    }

    void fecharConta() {
        int mesa;
        cout << "Mesa para fechar: ";
        cin >> mesa;
        
        if (mesa <= 0 || mesa > mesas.size()) {
            cout << "Numero de mesa invalido!" << endl;
            return;
        }

        bool encontrou = false;
        for (int i = 0; i < pedidos.size(); i++) {
            if (pedidos[i].mesa == mesa) {
                cout << endl << "====== CONTA DA MESA " << mesa << " ======" << endl << endl;
                for (auto item : pedidos[i].itens) item->info();
                cout << "---------------------" << endl << "TOTAL: R$ " << pedidos[i].total() << endl << endl;
                
                // Liberar a mesa
                mesas[mesa-1].disponivel = true;
                
                // Remover a reserva se existir
                for (int j = 0; j < reservas.size(); j++) {
                    if (reservas[j].mesa == mesa) {
                        reservas.erase(reservas.begin() + j);
                        break;
                    }
                }
                
                // Remove o pedido
                pedidos.erase(pedidos.begin() + i);
                encontrou = true;
                cout << "Conta fechada e mesa liberada!" << endl;
                break;
            }
        }
        
        if (!encontrou) {
            cout << "Mesa sem pedidos ativos!" << endl;
        }
    }
};

// Main
int main() {
    Restaurante r;
    r.menuPrincipal();
    return 0;
}