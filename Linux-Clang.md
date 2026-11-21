# Json-Performance: Node.js package.json Corpus vs simdjson On Demand (AVX512)
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1020-azure using the Clang 24.0.0 compiler).  

Latest Results: (Nov 21, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [c3f3d47](https://github.com/nihilai-collective/Jsonifier/commit/c3f3d47)  
| simdjson: [81c2d7212](https://github.com/simdjson/simdjson/commit/81c2d7212)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (generic)** | `AVX512` |
| **simdjson (ondemand)** | `icelake` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (AMD EPYC 9V45 96-Core Processor-AVX512):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 5s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 5% and mean shift ≤ 2.5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **Corpus:** Every unique package.json that is a JSON object under the deps/ folder of the Node.js add-jsonifier-main branch (the set Node's benchmark/module/package-json-corpus.js reads), split by size into the same buckets. `json/package_json/Sources.txt` maps each file to its source path.
* **Work per document:** Each library runs Node.js's own package.json field loop: name, main, type, private, and the raw JSON of exports, imports and scripts, skipping every other key. One benchmark iteration parses every document in the bucket once, with a parser reused across documents.
* **Padding:** Every document is stored with `SIMDJSON_PADDING` bytes of spare capacity, so simdjson parses in place with no copy.
* **Jsonifier:** Built from its `node` branch, the C++20 subset vendored into Node.js.

---
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Package.json Corpus 0-512 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%200-512%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3828.38 | 0.0776499 | 40.0824ms | 1497 | 1280 | 107.326 | 372.913 | 0.181516 | 0.60183 | 1(Win) | true |
| Jsonifier (generic) | 3557.73 | 0.0942672 | 42.8837ms | 1497 | 640 | 91.5796 | 401.281 | 0.000778749 | 0.647093 | 2(Loss) | true |

----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6721.09 | 0.0700607 | 358.999ms | 26071 | 80 | 537.372 | 3699.29 | 0.49928 | 0.365611 | 1(Win) | true |
| simdjson (ondemand) | 6507.51 | 0.0733145 | 381.727ms | 26071 | 30 | 235.39 | 3820.7 | 0.106325 | 0.377863 | 2(Loss) | true |

----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9164.15 | 0.0255404 | 1654.52ms | 152326 | 40 | 655.661 | 15851.9 | 0.235221 | 0.269714 | 1(Win) | true |
| simdjson (ondemand) | 7918.19 | 0.354587 | 1881.51ms | 152326 | 80 | 338557 | 18346.3 | 0.339173 | 0.312236 | 2(Loss) | true |

----
### Package.json Corpus 2048-65536 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%202048-65536%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10099.7 | 0.58517 | 565.104ms | 59099 | 160 | 170619 | 5580.48 | 0.169054 | 0.243972 | 1(Win) | true |
| simdjson (ondemand) | 8762.12 | 0.053025 | 654.57ms | 59099 | 30 | 348.999 | 6432.37 | 0.0570359 | 0.28147 | 2(Loss) | true |

----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8911.41 | 0.0751599 | 2592.08ms | 238993 | 4890 | 1.80701e+06 | 25576.4 | 0.385071 | 0.277541 | 1(Win) | true |
| simdjson (ondemand) | 7779.57 | 0.168657 | 2949.4ms | 238993 | 1280 | 3.12522e+06 | 29297.5 | 0.62745 | 0.317969 | 2(Loss) | true |
