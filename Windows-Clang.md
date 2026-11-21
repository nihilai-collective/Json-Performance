# Json-Performance: Node.js package.json Corpus vs simdjson On Demand (AVX512)
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the Clang 22.1.3 compiler).  

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

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3116.82 | 0.30125 | 48.7391ms | 1497 | 1280 | 2437.15 | 458.047 | 0.153741 | 0.747094 | 1(Win) | true |
| Jsonifier (generic) | 2972.34 | 0.244829 | 51.9317ms | 1497 | 1280 | 1770.04 | 480.312 | 0.195567 | 0.78613 | 2(Loss) | true |

----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 4653.13 | 0.194187 | 546.923ms | 26071 | 30 | 3229.89 | 5343.33 | 0 | 0.52855 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 4637.58 | 0.112492 | 528.266ms | 26071 | 80 | 2909.81 | 5361.25 | 0.304022 | 0.531223 | 1(Tie) | true |

----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6046.27 | 0.199032 | 2388.05ms | 152326 | 2560 | 5.85408e+06 | 24026.3 | 0.255417 | 0.408982 | 1(Win) | true |
| simdjson (ondemand) | 5696.56 | 0.507059 | 2604.71ms | 152326 | 160 | 2.67522e+06 | 25501.2 | 0.093046 | 0.434149 | 2(Loss) | true |

----
### Package.json Corpus 2048-65536 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%202048-65536%20Test.json):

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7957.11 | 0.644614 | 695.124ms | 59099 | 320 | 667112 | 7083.12 | 0.386745 | 0.309951 | 1(Win) | true |
| simdjson (ondemand) | 7269.29 | 0.119486 | 812.125ms | 59099 | 30 | 2574.71 | 7753.33 | 0.300043 | 0.33919 | 2(Loss) | true |

----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6153.69 | 0.136385 | 3725.89ms | 238993 | 2560 | 6.53236e+06 | 37038.2 | 0.0212995 | 0.402018 | 1(Win) | true |
| simdjson (ondemand) | 5622.58 | 0.0912337 | 4060.22ms | 238993 | 4890 | 6.68835e+06 | 40536.8 | 0.0325168 | 0.440028 | 2(Loss) | true |
