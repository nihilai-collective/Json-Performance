# Json-Performance: Node.js package.json Corpus vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.5 compiler).  

Latest Results: (Nov 21, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [96a9aaf](https://github.com/nihilai-collective/Jsonifier/commit/96a9aaf)  
| simdjson: [81c2d7212](https://github.com/simdjson/simdjson/commit/81c2d7212)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (generic)** | `NEON` |
| **simdjson (ondemand)** | `arm64` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (Apple M2 Pro (Virtual)-NEON):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 5s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 10% and mean shift ≤ 5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
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

<p align="left"><a href="./graphs/macOS-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1769.88 | 0.602847 | 81.642ms | 1497 | 640 | 15133.9 | 806.638 | 1.65281 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1702.52 | 1.89304 | 75.1673ms | 1497 | 40 | 10079.4 | 838.55 | 0.457232 | 1(Tie) | true |

----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2931.74 | 0.833717 | 848.11ms | 26071 | 1280 | 6.39898e+06 | 8480.7 | 0.0548051 | 1(Win) | true |
| Jsonifier (generic) | 2854.53 | 0.611173 | 903.977ms | 26071 | 1280 | 3.6273e+06 | 8710.09 | 0.934747 | 2(Loss) | true |

----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3441.87 | 0.783108 | 4392.74ms | 152326 | 320 | 3.49584e+07 | 42206.5 | 0.506525 | 1(Win) | true |
| simdjson (ondemand) | 3154.82 | 0.287512 | 4520.77ms | 152326 | 4890 | 8.5708e+07 | 46046.9 | 1.98375 | 2(Loss) | true |

----
### Package.json Corpus 2048-65536 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%202048-65536%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5057.66 | 0.0325227 | 1198.7ms | 59099 | 80 | 1050.81 | 11143.7 | 2.25703 | 1(Win) | true |
| simdjson (ondemand) | 4313.57 | 0.37861 | 1332.27ms | 59099 | 640 | 1.56621e+06 | 13066 | 0.395604 | 2(Loss) | true |

----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3349.58 | 1.37568 | 6906.13ms | 238993 | 40 | 3.50499e+07 | 68044.8 | 0.507213 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 3270.67 | 0.500216 | 7382.45ms | 238993 | 1280 | 1.55533e+08 | 69686.5 | 2.01277 | 1(Tie) | true |
