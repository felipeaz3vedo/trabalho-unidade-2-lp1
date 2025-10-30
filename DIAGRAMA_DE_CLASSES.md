classDiagram
    %% Classe Base Funcionario
    class Funcionario {
        #string nome
        #string id
        #string cargo
        +Funcionario(string, string, string)
        +string getNome()
        +string getId()
        +string getCargo()
        +virtual void mostrarInfo()
    }

    %% Classes Derivadas de Funcionario
    class Gerente {
        +Gerente(string, string)
    }

    class Cozinheiro {
        +Cozinheiro(string, string)
    }

    class Garcom {
        +Garcom(string, string)
    }

    class Recepcionista {
        +Recepcionista(string, string)
    }

    %% Relações de Herança
    Funcionario <|-- Gerente
    Funcionario <|-- Cozinheiro
    Funcionario <|-- Garcom
    Funcionario <|-- Recepcionista

    %% Classe Mesa
    class Mesa {
        -int numero
        -bool disponivel
        -int capacidade
        +Mesa(int, int)
        +void criarMesa(int, int)
        +void lerInfo()
        +void atualizarStatus(bool)
        +void liberarMesa()
        +int getNumero()
        +bool isDisponivel()
        +int getCapacidade()
    }

    %% Classe Prato
    class Prato {
        -string nome
        -string descricao
        -double preco
        -string categoria
        +Prato(string, string, double, string)
        +void criarPrato(string, string, double, string)
        +void lerInfo()
        +void atualizarPreco(double)
        +void atualizarDescricao(string)
        +string getNome()
        +double getPreco()
        +string getCategoria()
    }

    %% Classe ItemPedido
    class ItemPedido {
        -Prato* prato
        -int quantidade
        -string observacoes
        +ItemPedido(Prato*, int, string)
        +double calcularSubtotal()
        +void lerInfo()
        +Prato* getPrato()
        +int getQuantidade()
        +void setQuantidade(int)
    }

    %% Classe Pedido
    class Pedido {
        -int numeroMesa
        -vector~ItemPedido~ itens
        -bool fechado
        +Pedido(int)
        +void adicionarItem(Prato*, int, string)
        +void removerItem(int)
        +void lerPedido()
        +void atualizarQuantidadeItem(int, int)
        +double calcularTotal()
        +void fecharPedido()
        +int getNumeroMesa()
        +bool isFechado()
        +vector~ItemPedido~ getItens()
    }

    %% Classe Reserva
    class Reserva {
        -string nomeCliente
        -int numeroMesa
        -string data
        -string hora
        -int numPessoas
        +Reserva(string, int, string, string, int)
        +void criarReserva(string, int, string, string, int)
        +void lerInfo()
        +void atualizarReserva(string, string, int)
        +string getNomeCliente()
        +int getNumeroMesa()
    }

    %% Classe NotaFiscal
    class NotaFiscal {
        -int numero
        -double valorTotal
        -int numeroMesa
        -vector~ItemPedido~ itens
        +NotaFiscal(int, Pedido)
        +void emitirNota()
    }

    %% Classe SistemaRestaurante
    class SistemaRestaurante {
        -vector~Funcionario*~ funcionarios
        -vector~Mesa~ mesas
        -vector~Prato*~ cardapio
        -vector~Pedido~ pedidos
        -vector~Reserva~ reservas
        -vector~NotaFiscal~ notasFiscais
        -int proximoNumeroNota
        +SistemaRestaurante()
        +~SistemaRestaurante()
        +void menuPrincipal()
        -void inicializarDados()
        -void menuGerente()
        -void menuCozinheiro()
        -void menuGarcom()
        -void menuRecepcionista()
        -void gerenciarFuncionarios()
        -void gerenciarMesas()
        -void gerenciarCardapio()
        -void finalizarComanda()
        -void verRelatorios()
        -void mostrarCardapio()
        -void adicionarPrato()
        -void removerPrato()
        -void atualizarPrecoPrato()
        -void fazerPedido()
        -void verPedidosAbertos()
        -void fecharContaGarcom()
        -void mostrarMesas()
        -void fazerReserva()
        -void cancelarReserva()
        -void mostrarReservas()
        -int contarPedidosAbertos()
    }

    %% Relações de Associação
    ItemPedido --> Prato : usa
    Pedido --> ItemPedido : contém
    NotaFiscal --> Pedido : gera de
    SistemaRestaurante --> Funcionario : gerencia
    SistemaRestaurante --> Mesa : gerencia
    SistemaRestaurante --> Prato : gerencia
    SistemaRestaurante --> Pedido : gerencia
    SistemaRestaurante --> Reserva : gerencia
    SistemaRestaurante --> NotaFiscal : gerencia
    Reserva --> Mesa : referencia
