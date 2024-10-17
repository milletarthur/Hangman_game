
/**
 * @return la longueur de la chaine de caractères, c'est à dire le nombre
 * de caractères qu'elle contient. 
 * Exemple: "" -> length = 0
 *          "abc" -> length = 3
 */
int string_length(char *s) {
  char* txt = s;
  int count = 0;
  while(*s++){
    count += 1;
  }
  return count;
}  


/**
 * Copie la second chaîne sur la première.
 * @param s1 est la première chaîne
 * @param s2 est la seconde chaîne
 */
void string_copy(char* s1, char* s2) {
  for (int i=0; i<string_length(s2)+1; i++){
    *(s1+i) = *(s2+i);
  }
}

/**
 * Concatène les deux chaînes de caractères, ajoutant la seconde à la fin 
 * de la première.
 * @param s1 est la première chaîne
 * @param s2 est la seconde chaîne
 */
void string_concat(char* s1, char* s2) {
  int len = string_length(s1);
  int i;
    for (i=0; i<string_length(s2); i++){
    *(s1+i+len) = *(s2 + i);
  }
  *(s1+i+len+1) = '\0';
}

/**
 * Compare les deux chaînes de caractères
 * @param s1
 * @param s2
 * @return 0 si les deux chaînes sont identiques.
 *         -1 si la chaîne s1 est lexicographiquement inférieur à la chaîne s2
 *         1 si  la chaîne s1 est lexicographiquement supérieur à la chaîne s2
 */
int string_cmp(char *s1, char* s2) {
  int i=0;
  while(*(s1+i) == *(s2+i) && *(s1+i) != '\0' && *(s2+i) != '\0'){
    i++;
  }
  if (*(s1+i) == '\0' && *(s2+i) == '\0'){
    return 0;
  }
  else if (*(s1+i) < *(s2+i)){
    return -1;
  }
  else{
    return 1;
  }
}


/**
 * Cherche le caractère donné en argument, dans la chaîne donné en argument,
 * à partir de la position donné (offset).
 */
int string_index_of(char *dst, int offset, char ch) {
  int res;
  int i = offset;
  while(i != string_length(dst)){
    if(*(dst+i) == ch){
      res = string_length(dst) - i;
      res = string_length(dst) - res;
      return res;
    }
    i++;
  }
}

/**
 * Copie une sous-chaîne de la chaîne source dans la chaîne destination.
 * La sous-chaîne est défini par l'index du premier caractères (offset) 
 * et sa longueur (length). 
 * Cette sous-chaîne sera copiée dans la chaîne destination à l'index
 * donné par l'argument "doff".
 * @param dst: la chaîne destination
 * @param doff: l'offset dnas la chaîne destination
 * @param src: la chaîne source
 * @param offset: l'offset de la sous-chaîne à copier.
 * @param length: la loongueur de la sous-chaîne à copier.
 */
void string_substring(char* dst, int doff, char *src, int offset, int length) {
  int A = 0;
  int i;

  dst += doff;
  src += offset;
  for (i=0; i < length; i++){
    *(dst+i) = *(src+i);
  }
  if(length == 0){
    *dst = '\0';
  }
  else{
    *(dst+i+1) = '\0';
  }
}
