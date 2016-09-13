#include <stdlib.h>
#include <stdio.h>
#include "minunit.h"

#include "../src/value.h"
#include "../src/index.h"
#include "../src/query.h"
#include "../src/query_plan.h"

MU_TEST(testQueryParser) {
  char *str =
      "$1 = \"hello world\" AND $2 > 3 AND $3 IN (1, 3.14, 'foo', 'bar')";

  SIQuery q = SI_NewQuery();

  mu_check(SI_ParseQuery(&q, str, strlen(str)));
  mu_check(q.root != NULL);

  mu_check(q.root->type == QN_LOGIC);
  mu_check(q.root->op.left != NULL);
  mu_check(q.root->op.left->type == QN_PRED);
  mu_check(q.root->op.left->pred.t == PRED_EQ);
  mu_check(q.root->op.left->pred.eq.v.type == T_STRING);
  mu_check(q.root->op.left->pred.propId == 0);
  mu_check(!strcmp(q.root->op.left->pred.eq.v.stringval.str, "hello world"));

  mu_check(q.root->op.right != NULL);
  mu_check(q.root->op.right->type == QN_PRED);
  mu_check(q.root->op.right->pred.t == PRED_RNG);
  mu_check(q.root->op.right->pred.rng.min.type == T_INT32);
  mu_check(q.root->op.right->pred.rng.min.intval == 3);
  mu_check(q.root->op.right->pred.rng.max.type == T_NULL);
  mu_check(q.root->op.right->pred.propId == 1);

  //   for (int i = 0; i < q.numPredicates; i++) {
  //     printf("pred %d\n", i);
  //   }

  SIQueryNode_Print(q.root, 0);

  SIQueryNode_Free(q.root);
}

MU_TEST(testQueryPlan) {
  SISpec spec = {.properties =
                     (SIIndexProperty[]){{T_INT32}, {T_INT32}, {T_INT32}},
                 .numProps = 3};

  char *str = "$1 = 2 AND $2 IN ('hello', 'world')  AND ($3 IN (1, 3.14, "
              "'foo', 'bar') OR $4 = 'zzz')";

  SIQuery q = SI_NewQuery();

  mu_check(SI_ParseQuery(&q, str, strlen(str)));

  SIQueryPlan *qp = SIBuildQueryPlan(&q, &spec);
}

int main(int argc, char **argv) {
  // return testIndex();
  // MU_RUN_TEST(testQueryParser);
  MU_RUN_TEST(testQueryPlan);
  // MU_REPORT();
  return minunit_status;
}