#if ! defined( TabStr_ )
#define TabStr_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: TBS  Tabela de strings
*
*  Arquivo gerado:              TabStr.H
*  Letras identificadoras:      TBS
*  N�mero identificador:        000
*
*  Nome da base de software:    Gerar e acessar tabelas de strings
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\TABELA.BSW
*
*  Projeto: INF 1301/1628 - Exemplos
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs Arndt von Staa
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1        avs  20/11/2004  Inicio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa fun��es de acesso uma tabela de strings.
*     A tabela de string agrega em um �nico arquivo todos os strings
*     utilizados em determinado programa.
*
*     O presente m�dulo opera com uma tabela residente em mem�ria.
*
*     O conte�do dessa tabela � gerado pelo programa GERATAB.EXE
*     a partir de um ou mais arquivos contendo as especifica��es de strings.
*
*     O conte�do das correspondentes tabelas de defini��o � gerado pelo
*     programa GERADEF.EXE a partir dos mesmos arquivos de especifica��es
*     utilizado por GERATAB.EXE.
*
*  $EIU Interface com o usu�rio pessoa
*     Os strings s�o terminados por zero, e s�o compat�veis com as fun��es
*     definidas na biblioteca C.
*
***************************************************************************/
 
#if defined( TabStr_OWN )
   #define TabStr_EXT
#else
   #define TabStr_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

#define     TBS_MAX_LENGTH            256
#define     TBS_MIN_LENGTH              5


/***********************************************************************
*
*  $TC Tipo de dados: TBS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno
*
***********************************************************************/

   typedef enum {

         TBS_CondRetErroTabela = -3 ,
               /* Tabela mal formada */

         TBS_CondRetTruncado   = -2 ,
               /* String truncado, tamanho maior do que o espa�o dispon�vel */

         TBS_CondRetNaoExiste  = -1 ,
               /* N�o encontrou o string */

         TBS_CondRetOK         =  0
               /* Operou corretamente */

   } TBS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: TBS Obter um string contido na tabela
*
*  $ED Descri��o da fun��o
*     Procura a identifica��o de um string na tabela de strings.
*     Caso encontrado, copia-o para o espa�o disponibilizado pelo cliente.
*     N�o sendo encontrado copia o string com idString == 1; default:
*
*        "Identificaao de string %d nao foi encontrada."
*
*     Contido no arquivo de especifica��o de string: DefinicaoDefault.defstr
*
*     Caso este tamb�m n�o seja encontrado, copia o string ERRO_STRING
*     definido neste m�dulo. Default:
*
*        "?!?!?"
*
*  $EP Par�metros
*     idString    - identifica o string a ser procurado na tabela
*     dimString   - � a dimens�o m�xima, incluindo o zero terminal,
*                   que o string obtido poder� ter
*     pString     - ponteiro para espa�o receptor do string com pelo
*                   menos dimString bytes
*
*  $FV Valor retornado
*     Condi��o de retorno
*
***********************************************************************/

   TBS_tpCondRet TBS_ObterString( long   idString  ,
                                  int    dimString ,
                                  char * pString ) ;


/***********************************************************************
*
*  $FC Fun��o: TBS Obter o tamanho de um string
*
*  $ED Descri��o da fun��o
*     Retorna o tamanho do string idString contido na tabela
*
*  $EP Par�metros
*     idStr - identifica��o do string
*
*  $FV Valor retornado
*     tamanho do string
*        == TBS_CondRetNaoExiste  caso n�o seja encontrado
*
***********************************************************************/

   int TBS_ObterTamanhoString( long idString ) ;


/***********************************************************************
*
*  $FC Fun��o: TBS Teste - deturpar idString
*
*  $ED Descri��o da fun��o
*     For�a um valor lido no idString de um determinado string.
*
***********************************************************************/

   void TBS_TesteDeturparIdString( int idString , int inxElemento ) ;

#undef TabStr_EXT

/********** Fim do m�dulo de defini��o: TBS  Tabela de strings **********/

#else
#endif
