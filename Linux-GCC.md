# Json-Performance: Node.js package.json Corpus vs simdjson On Demand (AVX512)
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1020-azure using the GCC 16.0.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%200-512%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%200-512%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3497.4 | 0.0546383 | 43.6663ms | 1497 | 640 | 31.8366 | 408.203 | 0.101155 | 0.66329 | 1(Win) | true |
| simdjson (ondemand) | 3485.08 | 0.0574292 | 43.9051ms | 1497 | 640 | 35.4213 | 409.647 | 0.137886 | 0.666738 | 2(Loss) | true |

----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6582.1 | 0.0621417 | 394.378ms | 26071 | 40 | 220.4 | 3777.4 | 0.0989312 | 0.373574 | 1(Win) | true |
| Jsonifier (generic) | 6364.99 | 0.168971 | 423.413ms | 26071 | 2560 | 111528 | 3906.25 | 0.267212 | 0.386437 | 2(Loss) | true |

----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8422.52 | 0.0255065 | 1776.72ms | 152326 | 40 | 774.153 | 17247.7 | 0.203872 | 0.293507 | 1(Win) | true |
| simdjson (ondemand) | 7753.75 | 0.1278 | 1877.69ms | 152326 | 2560 | 1.46767e+06 | 18735.4 | 0.0865218 | 0.318877 | 2(Loss) | true |

----
### Package.json Corpus 2048-65536 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%202048-65536%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10587.3 | 0.0474982 | 556.878ms | 59099 | 40 | 255.741 | 5323.45 | 0.0910234 | 0.232683 | 1(Win) | true |
| simdjson (ondemand) | 8617.92 | 0.0442543 | 661.619ms | 59099 | 80 | 670.127 | 6540 | 0.256774 | 0.286173 | 2(Loss) | true |

----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8130.3 | 0.123218 | 2835.44ms | 238993 | 1280 | 1.52726e+06 | 28033.6 | 0.0725583 | 0.304237 | 1(Win) | true |
| simdjson (ondemand) | 7739.94 | 0.0399366 | 3004.01ms | 238993 | 30 | 4149.15 | 29447.5 | 0.0158499 | 0.319605 | 2(Loss) | true |
