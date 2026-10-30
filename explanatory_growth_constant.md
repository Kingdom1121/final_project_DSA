# Technical Explanatory Note: Pruning Constant (c ≈ 2.54) vs Measured Step Growth (~5.5x)
Project: Backtracking Search for the N-Queens Problem
Module: Data Structures and Algorithms (DASA230179_Dot1)

====================================================================================================
1. THE CORE DISTINCTION
====================================================================================================
* Empirical Factor (~5.5x): The measured runtime and node expansion ratio between consecutive 
  steps, T(N + 1) / T(N).
* Theoretical Constant (c ≈ 2.54): The combinatorial pruning factor per row from Donald Knuth's 
  TAOCP model and asymptotic chess theory (Rivin et al., 1994).

====================================================================================================
2. MATHEMATICAL DERIVATION
====================================================================================================
1. Pruned State Space:
   Unlike unpruned permutation O(N!), diagonal pruning bounds the valid search space to:
       S(N) ≈ N! / (c^N)  (with c ≈ 2.54)

2. Step-by-Step Growth Ratio:
   Evaluating the ratio between consecutive problem sizes N and N + 1:
       Ratio(N -> N + 1) = S(N + 1) / S(N)
                         ≈ [ (N + 1)! / c^(N + 1) ] / [ N! / c^N ]
                         = (N + 1) / c

====================================================================================================
3. EMPIRICAL VERIFICATION (BENCHMARK DATA)
====================================================================================================
* Step N = 12 -> 13:
  - Theoretical expectation: 13 / 2.54 ≈ 5.12x
  - Measured solutions: 73,712 / 14,200 ≈ 5.19x
  - Measured nodes: 4,674,890 / 856,189 ≈ 5.46x
  - Measured Plain time: 0.201991s / 0.038165s ≈ 5.29x

* Step N = 13 -> 14:
  - Theoretical expectation: 14 / 2.54 ≈ 5.51x
  - Measured nodes: 27,358,553 / 4,674,890 ≈ 5.85x
  - Measured Plain time: 1.209164s / 0.201991s ≈ 5.99x
  - Measured Bitmask time: 0.104610s / 0.017775s ≈ 5.89x

=> Conclusion: The measured growth factor of ~5.5x directly aligns with (N + 1) / c governed 
   by c ≈ 2.54, verifying the O(c^N) exponential model.

====================================================================================================
4. WEEK 4 ORAL DEFENSE SCRIPT (CONCISE)
====================================================================================================
Question: "Why does the table cite c ≈ 2.54 while the measured growth factor is ~5.5x?"

Answer:
"The factor of ~5.5x is the empirical ratio between consecutive steps, T(N + 1) / T(N). In contrast, 
c ≈ 2.54 is Knuth's combinatorial pruning constant in the model S(N) ≈ N! / (c^N).

Mathematically, the ratio between consecutive steps simplifies to:
    S(N + 1) / S(N) ≈ (N + 1) / c

At N = 13 -> 14, this yields 14 / 2.54 ≈ 5.51x, which closely matches our measured node expansion 
ratio of ~5.85x and time growth of ~5.9x. Therefore, c ≈ 2.54 is the foundational constant that 
proves why our measured growth factor converges to approximately 5.5x."