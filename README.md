# W_M_Multirules
Software used at work "A new multi-rules approach to improve the performance of the Chi fuzzy rule classification algorithm"

## How to compile?

cd code

make

## How to run?

Sintax:

`W_M_Multirules -e <path/seed problem> [-LearningModel <num>] [-InferenceModel <num>] [Parameters]`

Parameters Basic: 
* `-e  <path/seed problem>` directory path of the problem and seed of the files 
* `-nlabel <num>` number of labels used by discretize continuous variable. By default nlabel = 2  
* `-sd <num>` seed for the random number generator. By default sd = 0 
* `-h` or `-help` how to use this program.
* `-O <path/filename>` output file with results (by default [./patrBasicos.csv]).  


Learning Parameters: 
* `-LearningModel <num>` or `-LM <num>` to select the learning model:
* * `1`	Classic Chi Algorithm. Selected by default
* * `2`	Amount version. More rules than the central are considered. In this case, a number fixes of rules for each example, following a heuristic, is included. 
* * `3`	Threshold version. More rules than the central are considered. A threshold on the adaptation of the central rule is fixed expressed by a pertantage. All the rule with with adaptation igual or greather than that threshold are include in the rule set.
* * `4`	Normalized Threshold version. More rules than the central are considered. Similar to the previous model but using the normalized adaptation of the central rule.
* * `5`	Hamming Distance version. More rules than the central are considered. All the rules with hamming distance with the central rule less than a certain base distance are included
* * `6`	Normalized Threshold and Hamming Mixed version. The considered rules in this case are those that satisfy Normalized Threshold version and Distance Hamming Version.
* `-times <num>` or `-tm <num>` being `<num>` the number of rules included by each training example. By default, times = 1
* `-threshold <percentage>` or `-th <percent>` being `<percent>` a value in [0,1]. By default, threshold = 1.0
* `-ld <num>` being `<num>` the value of the maximum hamming distance permitted. By default, ld = 0
* `-size <num>` or `-sz <num>` establishes the maximum number of rules in the final rule set. 0 meaning not limited. By default, size = 0
* `-NotInferenceTraining` or `-Nit` does not apply real inference on training set (it is an estimation obtained from the learning process). By default not included
* `-NormalizedMu` uses the normalized adaptation degrees (by default the normalization is not used).
* `-weightCalculateProcess <num>` or `-wCP <num>` activate exhaustive traditional computation for obtaining the weight of the rule.
* `-weightRuleModel <num>` or `-w <num>` define how rule's weight is calculated by the Chi algorithm:
* * `1`	PCF (by default)
* * `2`	NSLV model 
* * `3`	Original Chi Strategy 2

Rule Filtering Parameters: 
*	 `-RuleFilteringMethod <num>` or `-RF <num>` to select the filtering rule process:
* *	`0`	No Filtering Method Applied (Value by default)
* *	`1`	Only are considered rules that classified at least one training example


Inference Parameters: 
* `-InferenceModel <num>` or `-IM <num>` to select the inference model:
  * `1`	Standard Inference
  * `2`	Standard Inference Prunned
  * `3`	Neighborhood Inference
  * `4`	Heuristic Neighborhood Inference
  * `5`	Heuristic Nearby Neighborhood Inference
  * `6`	Hybrid Inference
* `-d <num>` when model +5 or 6 is selected, this parameter establishes the maximum distance with the center rule. By default d = 0 
* `-maxrules <num>` when model `3`, `4`, `5` or `6` is selected, this parameter fixes the limit in the number of rule for explored. By default `maxrules 1024`
* `-PerCentOnTest <real_num>` establishes de percentage of the examples from the test set on which the inference is applied. By default `PerCentOnTest 1.0`


## Some examples

##### ./RedundancyStudyChi -e ../data/texture/texture -nlabel 5
Result of 10 cross-validation on the *texture* database, learning with *Classic CHI algorithm* and infering with *Heuristic Neighborhood Inference* taking 5 uniformly distributed labels cutoff at 0.5 over the universe of discourse of continuous variables.

##### ./RedundancyStudyChi -e ../data/census/census -IM 4 -nlabel 5 -maxrules 1024
Result of 10 cross-validation on the *census* database learning with *Classic CHI algorithm* and infering with *Heuristic Neighborhood Inference* taking 5 uniformly distributed labels and setting the inference parameter on the maximum number of rule to search in the example neighbor to 2^10 = 1024.


##### ./RedundancyStudyChi -e ../data/satimage/satimage -LM 2 -times 5 -nlabel 3 -maxrules 1024 -size 1000000 
Result of 10 cross-validation on the *satimage* database learning with *Amount Version of CHI algorithm*, considering 5 antecedents for each example, infering with *Heuristic Neighborhood Inference* taking 5 uniformly distributed labels and setting the inference parameter on the maximum number of rule to search in the example neighbor to 2^10 = 1024, and it is not permitted more than 1000000 rules in the final rule set.

# W_M_Multirules
# W_M_Multirules
