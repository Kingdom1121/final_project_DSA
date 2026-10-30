# Technical Explanatory Note: Pruning Constant (c ≈ 2.54) vs Measured Step Growth (~5.5x)

* **Project:** Backtracking Search for the N-Queens Problem
* **Module:** Data Structures and Algorithms (DASA230179_Dot1)
* **Target:** Week 4 Oral Defense & Theoretical Justification

---

## 1. The Core Distinction

* **Empirical Factor (~5.5x):** The measured runtime and node expansion ratio between consecutive steps:
  $$\frac{T(N + 1)}{T(N)}$$
* **Theoretical Constant ($c \approx 2.54$):** The combinatorial pruning factor per row derived from Donald Knuth's TAOCP model (Vol. 4B) and asymptotic chess theory (Rivin et al., 1994).

---

## 2. Mathematical Derivation

### 2.1. Pruned State Space
Without diagonal constraints, placing $N$ queens on an $N \times N$ board has an unpruned permutation complexity of $O(N!)$. 

When diagonal pruning is enforced in Backtracking, the effective valid search space is asymptotically bounded by:
$$S(N) \approx \frac{N!}{c^N} \quad (\text{with } c \approx 2.54)$$

### 2.2. Step-by-Step Growth Ratio
Evaluating the theoretical growth quotient between consecutive problem sizes $N$ and $N + 1$:
$$\text{Ratio}(N \to N + 1) = \frac{S(N + 1)}{S(N)} \approx \frac{\frac{(N + 1)!}{c^{N + 1}}}{\frac{N!}{c^N}} = \frac{(N + 1)!}{N!} \cdot \frac{c^N}{c^{N + 1}} = \frac{N + 1}{c}$$

---

## 3. Empirical Verification (Benchmark Data)

Substituting empirical benchmark data from `benchmark_result.txt` into the theoretical formula $\frac{N + 1}{c}$ with $c = 2.54$:

### Step $N = 12 \to 13$:
* **Theoretical expectation:** $\frac{13}{2.54} \approx \mathbf{5.12\times}$
* **Measured solutions:** $\frac{73,712}{14,200} \approx \mathbf{5.19\times}$
* **Measured nodes:** $\frac{4,674,890}{856,189} \approx \mathbf{5.46\times}$
* **Measured Plain time:** $\frac{0.20876020\text{s}}{0.03608850\text{s}} \approx \mathbf{5.78\text{x}}$
* **Measured Bitmask time:** $\frac{0.01838320\text{s}}{0.00339050\text{s}} \approx \mathbf{5.42\text{x}}$

### Step $N = 13 \to 14$:
* **Theoretical expectation:** $\frac{14}{2.54} \approx \mathbf{5.51\times}$
* **Measured solutions:** $\frac{365,596}{73,712} \approx \mathbf{4.96\times}$
* **Measured nodes:** $\frac{27,358,553}{4,674,890} \approx \mathbf{5.85\text{x}}$
* **Measured Plain time:** $\frac{1.22953670\text{s}}{0.20876020\text{s}} \approx \mathbf{5.89\text{x}}$
* **Measured Bitmask time:** $\frac{0.10407990\text{s}}{0.01838320\text{s}} \approx \mathbf{5.66\text{x}}$

> **Conclusion:** The empirically measured jump of $\approx 5.5\times$ is mathematically consistent with the constant $c \approx 2.54$ via the ratio $\frac{N + 1}{c}$.

---

## 4. Week 4 Oral Defense Script

**Question:** *"Why does your table cite $c \approx 2.54$ while your benchmark measures a growth factor of around $5.5\times$?"*

**Structured Answer:**
1. **State the distinction immediately:**  
   The factor of $\approx 5.5\times$ is the empirical step-growth ratio between consecutive sizes, $\frac{T(N + 1)}{T(N)}$. In contrast, $c \approx 2.54$ is Knuth's combinatorial pruning constant in the model $S(N) \approx \frac{N!}{c^N}$.
2. **Present the mathematical formula:**  
   According to combinatorial chess theory, computing the ratio between consecutive problem sizes yields:
   $$\frac{S(N + 1)}{S(N)} \approx \frac{N + 1}{c}$$
3. **Prove with benchmark numbers:**  
   At $N = 13 \to 14$, evaluating $\frac{14}{2.54} \approx \mathbf{5.51\times}$. This theoretical value aligns closely with our measured node expansion ratio of $\mathbf{5.85\times}$ and runtime growth of $\mathbf{5.89\times}$. Therefore, $c \approx 2.54$ is the mathematical root that proves why our measured step growth factor converges to approximately $5.5\times$.
