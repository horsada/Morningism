%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "histogram.hpp"
float frac_to_dec(std::string a)
{
  std::string num, denom;
  unsigned int index = a.find("/");
  for(unsigned int i=0; i<a.length(); i++)
  {
    if(i < index)
    {
      num += a[i];
    }
    else if(i != index)
    {
      denom += a[i];
    }
  }
  float dec = atof(num.c_str()) / atof(denom.c_str());
  return dec;
}

std::string substring(std::string a)
{
  int len = a.length();
  std::string sub = a.substr(1,len - 2);
  return sub;
}

// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

/* End the embedded code section. */
%}

digit [0-9]
letter [a-zA-Z]
decimal -?{digit}+\.?{digit}*
fraction -?[0-9]+\/[0-9]+
word1 {letter}+
word2 \[{word1}?{decimal}?{fraction}?\]
word3 \[[^\]]*\]
%%

{decimal}        { fprintf(stderr, "Number : %s\n", yytext); /* TODO: get value out of yytext and into yylval.numberValue */ yylval.numberValue = atof(yytext); return Number;}

{word1}          { fprintf(stderr, "Word : %s\n", yytext); /* TODO: get value out of yytext and into yylval.wordValue */ yylval.wordValue = new std::string(yytext); return Word;}

\n              { fprintf(stderr, "Newline\n"); }

{fraction}        { fprintf(stderr, "Number : %s\n", yytext); /* TODO: get value out of yytext and into yylval.numberValue */ yylval.numberValue = frac_to_dec(yytext); return Number;}

{word3}           { fprintf(stderr, "Word : %s\n", yytext); /* TODO: get value out of yytext and into yylval.wordValue */ yylval.wordValue = new std::string(substring(yytext)); return Word;}

.            { fprintf(stderr, "Random Character\n"); }
%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}