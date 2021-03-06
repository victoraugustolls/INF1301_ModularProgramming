#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, iars, vas
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     6       vas   03/out/2016 ajuste das fun��es para todas terem condi��es de retorno
*                               e retirada de fun��es n�o utilizadas
*     5       iars  14/set/2016 inser��o ordenada, procurar valor, imprimir
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
*     Tamb�m devem ser fornecidas uma fun��o de compara��o de elementos, uma
*        fun��o que diz quando dois elementos s�o iguais e uma fun��o que
*        imprime o conte�do de um elemento.
*
*     A fun��o de compara��o deve receber dois elementos e retornar -1, 0 ou 1
*        caso o primeiro elemento deva ser ordenado antes, igualmente ou ap�s
*        o segundo elemento, respectivamente.
*
*     A fun��o de igualdade deve receber dois valores e retornar 0 caso sejam diferentes
*        ou um inteiro diferente de zero caso sejam iguais.
*
***************************************************************************/

#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK = 0 ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia = 2 ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetListaNaoExiste = 3 ,
               /* A lista n�o existe */

         LIS_CondRetNoCorrenteUlt = 4 ,
               /* N� corrente � o �ltimo */

         LIS_CondRetNoCorrentePrim = 5 ,
               /* N� corrente � o primeiro */

         LIS_CondRetFaltouMemoria = 6 ,
               /* Faltou mem�ria ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*
*     pLista          - ponteiro para a lista sendo criada
*     idLista         - id da lista sendo criada, m�ximo de 4 caracteres
*     ExcluirValor    - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*     CompararValores - ponteiro para a fun��o que compara o valor
*                     de dois elementos. Deve retornar -1, 0 ou 1.
*                     Ver descri��o do m�dulo.
*     Igual           - ponteiro para a fun��o que compara se o valor
*                     de dois elementos � igual.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     LIS_CondRetOK            - lista foi criada corretamente
*     LIS_CondRetFaltouMemoria - ocorreu um erro na cria��o da lista
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista* pLista ,
             char * idLista ,

             void   ( * ExcluirValor ) ( void * pDado ) ,

             int   ( * CompararValores ) ( void * pDado_1, void * pDado_2 ) ,

             int   ( * Igual ) ( void * pDado_1, void * pDado_2 ) ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     LIS_CondRetOK             - destruiu sem problemas
*     LIS_CondRetListaNaoExiste - lista n�o existe
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     O elemento corrente passar� a ser o novo elemento inserido.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK              - inseriu elemento ap�s corretamente
*        LIS_CondRetFaltouMemoria   - ocorreu um erro na inser��o do elemento
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK           - excluiu elemento da lista corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista           - ponteiro para a lista de onde se quer o valor
*     elementoCorrente - ponteiro para o ponteiro referente ao valor do n� corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve valor do n� corrente corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista ,
                                 void ** elementoCorrente ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter identificador na cabe�a da lista
*
*  $ED Descri��o da fun��o
*     Obtem a identifica��o na cabe�a da lista
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista de onde se quer o valor
*     idLista - ponteiro para o ponteiro referente ao valor do id da lista
*
*  $FV Valor retornado
*     LIS_CondRetOK   - obteve o id da lista corretamente
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterId( LIS_tppLista pLista ,
                              char ** idLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     LIS_CondRetOK             - se numElem elementos tiverem sido andados
*     LIS_CondRetNoCorrenteUlt  - chegou ao final da lista antes de avan�ar
*                               para o pr�ximo elemento
*     LIS_CondRetNoCorrentePrim - chegou no come�o da lista antes de retornar
*                               para o elemento anterior
*     LIS_CondRetListaVazia     - se a lista est� vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Altera conteudo do n� corrente
*
*  $ED Descri��o da fun��o
*     Altera o valor do n� corrente da lista para novo valor.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     pValor  - ponteiro para o novo valor do n� corrente
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK             - altera��o bem sucedida
*     LIS_CondRetListaVazia     - se a lista estiver vazia
*     LIS_CondRetListaNaoExiste - se a lista n�o existir
*
***********************************************************************/

   LIS_tpCondRet LIS_AlteraValor( LIS_tppLista pLista ,
                                  void * pValor ) ;

#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif
