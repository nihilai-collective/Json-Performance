# Json-Performance: Node.js package.json Corpus vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

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

<p align="left"><a href="./graphs/macOS-GCC/Package.json%20Corpus%200-512%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Package.json%20Corpus%200-512%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2195.03 | 4.14025 | 84.702ms | 1497 | 320 | 232041 | 650.4 | 1.1194 | 1(Win) | true |
| simdjson (ondemand) | 1831.73 | 1.10965 | 87.3372ms | 1497 | 2560 | 191484 | 779.4 | 0.205708 | 2(Loss) | true |

----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2872.5 | 0.299125 | 880.206ms | 26071 | 2560 | 1.71609e+06 | 8655.6 | 0.0808071 | 1(Win) | true |
| simdjson (ondemand) | 2572.08 | 0.419506 | 938.377ms | 26071 | 1280 | 2.10491e+06 | 9666.6 | 0.815569 | 2(Loss) | true |

----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3800.79 | 0.293397 | 3882.71ms | 152326 | 320 | 4.02403e+06 | 38220.8 | 0.568349 | 1(Win) | true |
| simdjson (ondemand) | 3221.28 | 0.393823 | 4560.56ms | 152326 | 320 | 1.00935e+07 | 45096.8 | 0.636325 | 2(Loss) | true |

----
### Package.json Corpus 2048-65536 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%202048-65536%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4787.41 | 0.352912 | 1156.24ms | 59099 | 640 | 1.10477e+06 | 11772.8 | 0.334083 | 1(Win) | true |
| simdjson (ondemand) | 4098.27 | 0.133545 | 1403.4ms | 59099 | 4890 | 1.64939e+06 | 13752.4 | 0.511129 | 2(Loss) | true |

----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3592.89 | 0.486575 | 6038.37ms | 238993 | 30 | 2.85827e+06 | 63436.8 | 0.0537779 | 1(Win) | true |
| simdjson (ondemand) | 3184.68 | 0.218948 | 7055.2ms | 238993 | 160 | 3.9286e+06 | 71568 | 0.129499 | 2(Loss) | true |
