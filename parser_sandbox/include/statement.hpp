/* The MIT License (MIT)
 *
 * Copyright (c) 2014-2018 David Medina and Tim Warburton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 */
#ifndef OCCA_LANG_STATEMENT_HEADER
#define OCCA_LANG_STATEMENT_HEADER

#include <vector>

#include "baseStatement.hpp"
#include "scope.hpp"
#include "token.hpp"
#include "trie.hpp"
#include "type.hpp"

namespace occa {
  namespace lang {
    class ifStatement;
    class elifStatement;
    class elseStatement;
    class variableDeclaration;

    typedef std::vector<elifStatement*>      elifStatementVector;
    typedef std::vector<variableDeclaration> variableDeclarationVector;

    //---[ Pragma ]---------------------
    class pragmaStatement : public statement_t {
    public:
      pragmaToken &token;

      pragmaStatement(statement_t *up_,
                      pragmaToken &token_);
      ~pragmaStatement();

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ Type ]-----------------------
    // TODO: Type declaration
    class functionStatement : public statement_t {
    public:
      function_t function;

      functionStatement(statement_t *up_,
                        const function_t &function_);

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };

    class functionDeclStatement : public blockStatement {
    public:
      function_t function;

      functionDeclStatement(statement_t *up_,
                            const function_t &function_);
      functionDeclStatement(const functionDeclStatement &other);

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };

    class classAccessStatement : public statement_t {
    public:
      int access;

      classAccessStatement(statement_t *up_,
                           const int access_);

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ Expression ]-----------------
    class expressionStatement : public statement_t {
    public:
      exprNode *root;

      expressionStatement(statement_t *up_,
                          exprNode &root_);
      ~expressionStatement();

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };

    class declarationStatement : public statement_t {
    public:
      variableDeclarationVector declarations;

      declarationStatement(statement_t *up_);
      declarationStatement(const declarationStatement &other);

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ Goto ]-----------------------
    class gotoStatement : public statement_t {
    public:
      identifierToken &labelToken;

      gotoStatement(statement_t *up_,
                    identifierToken &labelToken_);
      gotoStatement(const gotoStatement &other);
      ~gotoStatement();

      std::string& label();
      const std::string& label() const;

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };

    class gotoLabelStatement : public statement_t {
    public:
      identifierToken &labelToken;

      gotoLabelStatement(statement_t *up_,
                         identifierToken &labelToken_);
      gotoLabelStatement(const gotoLabelStatement &other);
      ~gotoLabelStatement();

      std::string& label();
      const std::string& label() const;

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ Namespace ]------------------
    class namespaceStatement : public blockStatement {
    public:
      identifierToken &nameToken;

      namespaceStatement(statement_t *up_,
                         identifierToken &nameToken_);
      namespaceStatement(const namespaceStatement &other);
      ~namespaceStatement();

      std::string& name();
      const std::string& name() const;

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ If ]-------------------------
    class ifStatement : public blockStatement {
    public:
      statement_t *condition;

      elifStatementVector elifSmnts;
      elseStatement *elseSmnt;

      ifStatement(statement_t *up_,
                  statement_t *condition_);
      ifStatement(const ifStatement &other);
      ~ifStatement();

      void addElif(elifStatement &elifSmnt);

      void addElse(elseStatement &elseSmnt_);

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };

    class elifStatement : public blockStatement {
    public:
      statement_t *condition;

      elifStatement(statement_t *up_,
                    statement_t *condition_);
      elifStatement(const elifStatement &other);
      ~elifStatement();

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };

    class elseStatement : public blockStatement {
    public:
      elseStatement(statement_t *up_);
      elseStatement(const elseStatement &other);

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ For ]------------------------
    class forStatement : public blockStatement {
    public:
      statement_t *init, *check, *update;

      forStatement(statement_t *up_,
                   statement_t *init_,
                   statement_t *check_,
                   statement_t *update_);
      forStatement(const forStatement &other);
      ~forStatement();

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ While ]----------------------
    class whileStatement : public blockStatement {
    public:
      statement_t *condition;
      bool isDoWhile;

      whileStatement(statement_t *up_,
                     statement_t *condition_,
                     const bool isDoWhile_ = false);
      whileStatement(const whileStatement &other);
      ~whileStatement();

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ Switch ]---------------------
    class switchStatement : public blockStatement {
    public:
      statement_t *condition;

      switchStatement(statement_t *up_,
                      statement_t *condition_);
      switchStatement(const switchStatement& other);
      ~switchStatement();

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ Case ]-----------------------
    class caseStatement : public statement_t {
    public:
      exprNode *value;

      caseStatement(statement_t *up_,
                    exprNode &value_);
      ~caseStatement();

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };

    class defaultStatement : public statement_t {
    public:
      defaultStatement(statement_t *up_);

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================

    //---[ Exit ]-----------------------
    class continueStatement : public statement_t {
    public:
      continueStatement(statement_t *up_);

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };

    class breakStatement : public statement_t {
    public:
      breakStatement(statement_t *up_);

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };

    class returnStatement : public statement_t {
    public:
      exprNode *value;

      returnStatement(statement_t *up_,
                      exprNode *value_);
      returnStatement(const returnStatement &other);
      ~returnStatement();

      virtual statement_t& clone_() const;
      virtual int type() const;

      virtual void print(printer &pout) const;
    };
    //==================================
  }
}

#endif
