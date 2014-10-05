#include "common.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256,EQ,NE,LE,GE,AND,OR,NOT,SAL,SAR,NUM,HEX,REG,NEG,DEREF

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{"[0-9]+", NUM},
	{"\\+", '+'},					// plus
	{"-", '-'},
	{"\\*", '*'},
	{"\\/", '/'},
	{"\\(", '('},
	{"\\)", ')'},
	{" +",	NOTYPE},				// white space
	{"==", EQ},						// equal

};
int level(int type) {
		int result = 100;
		switch (type) {
			case NEG: case '~': case NOT: case DEREF:								
				result = 16; break;
			case '*': case '/': case '%':
				result = 14; break;
			case '+': case '-':
				result = 13; break;
			case SAL: case SAR:
				result = 12; break;
			case '<': case LE: case '>': case GE:
				result = 11; break;
			case EQ: case NE:
				result = 10; break;
			case '&':
				result = 9; break;
			case '^':
				result = 8; break;
			case '|':
				result = 7; break;
			case AND:
				result = 6; break;
			case OR:
				result = 5; break;
		}
		return result;
}
#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			test(0, "regex compilation failed: %s\n%s\n", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);

				position += substr_len;


				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch(rules[i].token_type) {
					case NUM:
						tokens[nr_token].type=0;
						strncpy(tokens[nr_token].str,substr_start,substr_len);
						nr_token++;
						break;
					case 256:
						break;
					default:
						tokens[nr_token].type=rules[i].token_type;
						nr_token++;
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}
bool check_parentheses(int p,int q,bool* success) {
	int i,count=0;
	bool flag=(tokens[p].type == '(') && (tokens[q].type == ')');
	for (i=p+1;i<q;i++) {
		if (tokens[i].type=='(') 
			count++;
		if (tokens[i].type==')') 
			count--;
		if (count<0)
			flag = false;
	}
	*success=flag;
	return flag;
}
int dominant(int p,int q) {
	int i,count=0,loc=-1;
	for (i=p;i<=q;i++) {
		switch (tokens[i].type) {
			case '(':
				count++;
				break;
			case ')':
				count--;
				break;
			case NUM:
				break;
			default :
				if (count==0) {
					if (loc<0) 
						loc=i;
					if (level(tokens[i].type) < level(tokens[loc].type))
						loc=i;
				}
		}
	}
	return loc;
}
uint32_t eval(int p,int q,bool *success) {
	    if(p > q) {
		/* Bad expression */
			*success=false;
			return 0;
		}
		else if(p == q) { 
		/* Single token.
		* For now this token should be a number. 
		* Return the value of the number.
		*/ 
			uint32_t value=0;
			sscanf(tokens[p].str,"%d",&value);
			return value;
		}
		else if(check_parentheses(p,q,success)==true) {
		/* The expression is surrounded by a matched pair of parentheses. 
		 * If that is the case, just throw away the parentheses.	 
		 */
			return eval(p+1,q-1,success); 
		}
		else if (*success==true) {
		/* We should do more things here. */
			int op=dominant(p,q);
			int val1;
			if (op==p) val1=0;
			else val1=eval(p,op-1,success);
			int val2=eval(op+1,q,success);
			switch (tokens[op].type) {
				case '+': return val1+val2; 
				case '-': return val1-val2;
				case '*': return val1*val2;
				case '/': return val1/val2;
				default: *success=false; return 0;
			}
		}
		else 
			return 0;
}
uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}

	/* TODO: Implement code to evaluate the expression. */
	int tmp=0;
	for (;tmp<nr_token;tmp++) {
		if (tokens[tmp].type==0)
			printf("%s",tokens[tmp].str);
		else
			printf("%c",tokens[tmp].type);
	}
	printf("\n");
	int result=eval(0,nr_token-1,success);
	if (*success==false) {
		printf("Calaulate failed!\n");
		return -1;
	}
	else {
		printf("%d\n",result);
		return result;
	}
}

