/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
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
*     11      vas   15/dez/2016 ajustes na funcao de verificacao
*     10      iars  12/dez/2016 criacao da funcao de verificacao
*     9       iars  15/nov/2016 copia lista
*     8       vas   13/nov/2016 adi��o da implementa��o da fun��o de comparar listas
*     7       vas   11/nov/2016 adi��o da fun��o de lista vazia
*     6       vas   03/out/2016 ajuste das fun��es para todas terem condi��es de retorno
*                               e retirada de fun��es n�o utilizadas
*     5       iars  14/set/2016 inser��o ordenada, procurar valor, imprimir
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#ifdef _DEBUG
    #include "GENERICO.H"
    #include "CESPDIN.H"
    #include "CONTA.H"
    #include "TIPOS_ESPACO.H"
    //#include   "..\\tabelas\\IdTiposEspaco.def"
#endif

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
   #define MAGIC_NUMBER 0xDEADBEEF
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         #ifdef _DEBUG
            int magic_number;
         #endif

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         #ifdef _DEBUG
            int magic_number;
         #endif

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

         char * idLista ;
               /* Identifica��o da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */
         
         int ( * CompararValores ) ( void * pValor_1, void * pValor_2 ) ;
               /* Ponteiro para a fun��o de compara��o de valores */
         
         int ( * Igual ) ( void * pValor_1, void * pValor_2 ) ;
               /* Ponteiro para a fun��o de checagem de igualdade de valores */

         #ifdef _DEBUG

            int tipoArmazenado;

         #endif

   } LIS_tpLista ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LIS_EsvaziarLista( LIS_tppLista pLista ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * pLista ,
             char * idLista ,
             void   ( * ExcluirValor ) ( void * pDado ),
             int   ( * CompararValores ) ( void * pDado_1, void * pDado_2 ),
             int   ( * Igual ) ( void * pDado_1, void * pDado_2 ) )
   {

      LIS_tppLista pNewLista = NULL ;

      pNewLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pNewLista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      LimparCabeca( pNewLista ) ;

      pNewLista->idLista = ( char * ) malloc ( strlen ( idLista ) + 1 ) ;
      strcpy( pNewLista->idLista , idLista ) ;
      pNewLista->ExcluirValor = ExcluirValor ;
      pNewLista->CompararValores = CompararValores ;
      pNewLista->Igual = Igual ;

      #ifdef _DEBUG
         pNewLista->magic_number = MAGIC_NUMBER;
         CED_MarcarEspacoAtivo( pNewLista ) ;
         pNewLista->tipoArmazenado = CED_ID_TIPO_VALOR_NULO;
      #endif

      *pLista = pNewLista ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Criar lista */


/***************************************************************************
*
*  Fun��o: LIS  &Copiar lista
*  ****/


   LIS_tpCondRet LIS_CopiarLista( LIS_tppLista* pLista , LIS_tppLista listaOriginal, void ( * CopiarElemento ) ( void ** pValor, void* pValorOriginal ) )
   {

      LIS_tppLista pNewLista = NULL ;
      tpElemLista * pElem ;
      LIS_tpCondRet listaCondRet;
      void * pValorNovo;

      pNewLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pNewLista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      LimparCabeca( pNewLista ) ;

      pNewLista->idLista = ( char * ) malloc ( strlen ( listaOriginal->idLista ) + 1 ) ;
      strcpy( pNewLista->idLista , listaOriginal->idLista ) ;

      pNewLista->ExcluirValor = listaOriginal->ExcluirValor ;
      pNewLista->CompararValores = listaOriginal->CompararValores ;
      pNewLista->Igual = listaOriginal->Igual ;

      #ifdef _DEBUG
         pNewLista->magic_number = MAGIC_NUMBER;
      #endif

      if ( listaOriginal->pElemCorr == NULL )
      {
         *pLista = pNewLista ;
         return LIS_CondRetOK ;
      } /* if */

      for ( pElem  = listaOriginal->pOrigemLista ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         CopiarElemento(&pValorNovo, pElem->pValor);
         listaCondRet = LIS_InserirElementoApos( pNewLista, pValorNovo );
         if(listaCondRet == LIS_CondRetFaltouMemoria)
         {
            LIS_DestruirLista(pNewLista);
            return LIS_CondRetFaltouMemoria;
         }
      } /* for */

      *pLista = pNewLista ;
      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Copiar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista )
   {

      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      LIS_EsvaziarLista( pLista ) ;

      #ifdef _DEBUG
         CED_MarcarEspacoNaoAtivo( pLista ) ;
      #endif

      free( pLista ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Move Inicio
*  ****/

   LIS_tpCondRet LIS_MoveInicio( LIS_tppLista pLista )
   {
      pLista->pElemCorr = pLista->pOrigemLista;
      return LIS_CondRetOK;
   }

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir ap�s */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista , void ** elementoCorrente )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */
      
      *elementoCorrente = pLista->pElemCorr->pValor ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para a identifica��o contida na cabe�a da lista
*  ****/

   LIS_tpCondRet LIS_ObterId( LIS_tppLista pLista , char ** idLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
      
      *idLista = pLista->idLista ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Obter refer�ncia para a identifica��o contida na cabe�a da lista */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {
            return LIS_CondRetListaVazia ;
         } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetNoCorrenteUlt ;

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetNoCorrentePrim ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Altera conteudo do n� corrente
*  ****/

   LIS_tpCondRet LIS_AlteraValor( LIS_tppLista pLista ,
                                    void * pValor )
   {

      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      }/* if */

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pLista->pElemCorr->pValor = pValor;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Altera conteudo do n� corrente */

/***************************************************************************
*
*  Fun��o: LIS  &Verifica se a lista est� vazia
*  ****/

   LIS_tpCondRet LIS_VerificaVazia( LIS_tppLista pLista ,
                                    int * vazia )
   {

      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      if ( pLista->numElem == 0 )
      {
         *vazia = 1 ;
      }
      else
      {
         *vazia = 0 ;
      } /* if */

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Verifica se a lista est� vazia */


/***************************************************************************
*
*  Fun��o: LIS  &Compara duas listas
*  ****/

   LIS_tpCondRet LIS_VerificaIgualdade( LIS_tppLista pLista1 ,
                                        LIS_tppLista pLista2 ,
                                        int * igualdade )
   {

      int i ;

      if ( pLista1 == NULL || pLista2 == NULL )
      {
         *igualdade = 0 ;
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      if ( pLista1->numElem != pLista2->numElem )
      {
         *igualdade = 0 ;
         return LIS_CondRetOK ;
      } /* if */

      for ( i = 0 ; i < pLista1->numElem ; i++ )
      {
         if ( !pLista1->CompararValores( pLista1->pElemCorr , pLista2->pElemCorr ) )
         {
            *igualdade = 0;
            return LIS_CondRetOK ;
         } /* if */

         LIS_AvancarElementoCorrente( pLista1 , 1 ) ;
         LIS_AvancarElementoCorrente( pLista2 , 1 ) ;

      } /* for */

      *igualdade = 1 ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Verifica se a lista est� vazia */

/***************************************************************************
*
*  Fun��o: LIS  &Esvazia lista
*  ****/

   LIS_tpCondRet LIS_Esvazia( LIS_tppLista pLista )
   {

      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      free( pLista ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Esvazia lista */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista ) ) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      #ifdef _DEBUG
         pElem->magic_number = MAGIC_NUMBER;
      #endif

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Esvaziar a lista
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim fun��o: LIS  -Esvaziar a lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->idLista = NULL;
      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor )
   {

      tpElemLista * pElem ;

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pLista->Igual( pElem->pValor, pValor ) )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim fun��o: LIS  &Procurar elemento contendo valor */


#ifdef _DEBUG

/* --------------------------------------------------------------
*   DEBUG
* -------------------------------------------------------------- */

   LIS_tpCondRet LIS_SetTipo( LIS_tppLista pLista ,
                              int identificadorDoTipo )
   {

      pLista->tipoArmazenado = identificadorDoTipo;

      return LIS_CondRetOK ;
   }

   LIS_tpCondRet LIS_GetTipo( LIS_tppLista pLista ,
                              int* identificadorDoTipo )
   {

      *identificadorDoTipo = pLista->tipoArmazenado;

      return LIS_CondRetOK ;
   }

   LIS_tpCondRet LIS_Tamanho( LIS_tppLista pLista ,
                              int * tamanhoDaLista )
   {
      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      *tamanhoDaLista = pLista->numElem;

      return LIS_CondRetOK ;
   }

   LIS_tpCondRet LIS_VerificaAssertivasEstruturais( LIS_tppLista pLista, LIS_tpErroEstrutura* erroOcorrido, int* numErrosEncontrados )
   {
      tpElemLista * pElem;
      int numElemContados;
      LIS_tpCondRet ret = LIS_CondRetOK;

      *numErrosEncontrados = 0;

      if(( pLista->pElemCorr == NULL && pLista->numElem != 0 )
      || ( pLista->pOrigemLista == NULL && pLista->numElem != 0 )
      || ( pLista->pFimLista == NULL && pLista->numElem != 0 )
      || ( pLista->numElem == 0 && pLista->pElemCorr != NULL )
      || ( pLista->numElem == 0 && pLista->pOrigemLista != NULL )
      || ( pLista->numElem == 0 && pLista->pFimLista != NULL ) )
      {
         *erroOcorrido = LIS_tpErroEstruturaListaVaziaInconsistente;
         CNT_CONTAR( "erro-lista-vazia-inconsistente");
         (*numErrosEncontrados)++;
         ret = LIS_CondRetFalhaNaEstrutura;
         return ret;
      }

      if( pLista->numElem != 0 && (pLista->pOrigemLista->pAnt != NULL || pLista->pFimLista->pProx != NULL ))
      {
         *erroOcorrido = LIS_tpErroEstruturaListaCircular;
         CNT_CONTAR( "erro-lista-circular" );
         (*numErrosEncontrados)++;
         ret = LIS_CondRetFalhaNaEstrutura;
         return ret;
      }

      numElemContados = 0;
      for(pElem = pLista->pOrigemLista; pElem != NULL; pElem = pElem->pProx)
      {
         if( (pElem->magic_number != MAGIC_NUMBER)
         ||  (pElem->pProx != NULL && pElem->pProx->magic_number != MAGIC_NUMBER)
         ||  (pElem->pAnt != NULL && pElem->pAnt->magic_number != MAGIC_NUMBER) )
         {
            *erroOcorrido = LIS_tpErroEstruturaElementoDaListaCorrompido;
            CNT_CONTAR( "erro-lista-magic-number-errado" );
            (*numErrosEncontrados)++;
            ret = LIS_CondRetFalhaNaEstrutura;
            return ret;
         }

         if( ( pElem->pProx != NULL && (pElem->pProx->pAnt != pElem) )
         ||  ( pElem->pAnt != NULL  && (pElem->pAnt->pProx != pElem) ) )
         {
            *erroOcorrido = LIS_tpErroEstruturaElementoDaListaCorrompido;
            CNT_CONTAR( "erro-lista-encadeamento" ) ;
            (*numErrosEncontrados)++;
            ret = LIS_CondRetFalhaNaEstrutura;
            return ret;
         }

         if(pElem->pValor == NULL)
         {
            *erroOcorrido = LIS_tpErroEstruturaValorArmazenadoNulo;
            CNT_CONTAR( "erro-lista-valor-corrente-nulo" );
            (*numErrosEncontrados)++;
            ret = LIS_CondRetFalhaNaEstrutura;
         }

         if(CED_ObterTipoEspaco( pElem->pValor ) != pLista->tipoArmazenado)
         {
            *erroOcorrido = LIS_tpErroEstruturaTipoDoValorIncoerente;
            CNT_CONTAR( "erro-lista-tipo-valor-incoerente" );
            (*numErrosEncontrados)++;
            ret = LIS_CondRetFalhaNaEstrutura;
         }

         numElemContados++;
      }

      if(numElemContados != pLista->numElem)
      {
         *erroOcorrido = LIS_tpErroEstruturaNumeroDeElementosIncorreto;
         CNT_CONTAR( "erro-lista-numero-elementos-incorreto");
         (*numErrosEncontrados)++;
         ret = LIS_CondRetFalhaNaEstrutura;
      }

      *erroOcorrido = LIS_tpErroEstruturaNenhum;
      return ret;
   }

LIS_tpCondRet LIS_ObterPonteiroProximo( LIS_tppLista pLista ,
                                       void *** ponteiroProxElem )
{
    tpElemLista* noCorrente ;
    
    noCorrente = pLista->pElemCorr ;
    
    *ponteiroProxElem = &noCorrente->pProx ;

    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_ObterPonteiroAnterior( LIS_tppLista pLista ,
                                       void *** ponteiroAntElem )
{
    tpElemLista* noCorrente ;
    
    noCorrente = pLista->pElemCorr ;
    
    *ponteiroAntElem = &noCorrente->pAnt ;

    return LIS_CondRetOK;
}



LIS_tpCondRet LIS_ObterPonteiroValor( LIS_tppLista pLista ,
                                       void *** ponteiroValor )
{
    tpElemLista* noCorrente ;
    
    noCorrente = pLista->pElemCorr ;
    
    *ponteiroValor = &noCorrente->pValor ;

    return LIS_CondRetOK;
}


LIS_tpCondRet LIS_ObterPonteiroCorrente( LIS_tppLista pLista ,
                                       void *** ponteiroCorrente )
{
  
    *ponteiroCorrente = &pLista->pElemCorr ;

    return LIS_CondRetOK;   
}

LIS_tpCondRet LIS_MoveFim( LIS_tppLista pLista )
{
   pLista->pElemCorr = pLista->pFimLista;
   return LIS_CondRetOK;
}


#endif

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/

