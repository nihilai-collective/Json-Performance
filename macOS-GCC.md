# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Sep 23, 2026)
#### Using the following commits:
----
| Jsonifier: [38630d2](https://github.com/nihilai-collective/jsonifier/commit/38630d2)  
| Glaze: [59af451](https://github.com/stephenberry/glaze/commit/59af451)  
| Simdjson: [6913ee1](https://github.com/simdjson/simdjson/commit/6913ee1)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |
| Glaze (structural-skip) | `NEON64` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 10.000000% AND mean shift < 5.000000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [6160583](https://github.com/nihilai-collective/benchmarksuite/commit/6160583).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 880.457 | 2.65661 | 3.26707ms | 1811 | 80 | 217254 | 1961.6 | 1(Tie) |
| jsonifier STATISTICAL TIE | 879.978 | 4.73535 | 23.371ms | 1811 | 30 | 259131 | 1962.67 | 1(Tie) |
| simdjson (ondemand) | 167.13 | 1.30915 | 3.24813ms | 1811 | 30 | 549071 | 10333.9 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 741.374 | 3.84841 | 0.784896ms | 1811 | 30 | 241127 | 2329.6 | 1(Tie) |
| glaze STATISTICAL TIE | 705.06 | 3.55982 | 0.868096ms | 1798 | 30 | 224856 | 2432 | 1(Tie) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4616.98 | 8.11709 | 0.578048ms | 3873 | 40 | 168671 | 800 | 1(Win) |
| glaze | 2739.5 | 6.62345 | 0.5632ms | 3873 | 30 | 239244 | 1348.27 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1453.24 | 3.79339 | 0.8ms | 3862 | 30 | 277285 | 2534.4 | 1(Win) |
| jsonifier | 1273.9 | 4.64781 | 20.524ms | 3862 | 320 | 5.77834e+06 | 2891.2 | 2(Loss) |
| simdjson (ondemand) | 438.463 | 0.737587 | 13.8949ms | 3862 | 80 | 307096 | 8400 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3742.22 | 3.10642 | 26.4742ms | 3862 | 1280 | 1.19646e+06 | 984.2 | 1(Win) |
| glaze | 1702.38 | 2.15456 | 109.482ms | 3862 | 2560 | 5.56249e+06 | 2163.5 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1231.56 | 7.43041 | 0.995072ms | 905 | 80 | 216922 | 700.8 | 1(Win) |
| glaze | 770.603 | 4.607 | 0.848128ms | 905 | 40 | 106496 | 1120 | 2(Loss) |
| simdjson (ondemand) | 146.027 | 5.7206 | 8.95693ms | 905 | 80 | 9.1455e+06 | 5910.4 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2854.08 | 6.04171 | 4.27187ms | 905 | 640 | 213630 | 302.4 | 1(Win) |
| glaze | 991.585 | 7.40851 | 0.349184ms | 905 | 30 | 124744 | 870.4 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2536.55 | 3.14126 | 1.29203ms | 9578 | 30 | 383875 | 3601.07 | 1(Win) |
| glaze | 1899.05 | 0.802045 | 481.203ms | 9578 | 4890 | 7.2775e+06 | 4809.92 | 2(Loss) |
| simdjson (ondemand) | 537.514 | 4.14484 | 46.783ms | 9578 | 160 | 7.93792e+07 | 16993.6 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze STATISTICAL TIE | 5724.2 | 5.73981 | 0.702976ms | 9578 | 30 | 251673 | 1595.73 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5379.02 | 4.92802 | 0.64896ms | 9578 | 30 | 210092 | 1698.13 | 1(Tie) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 350.357 | 4.47236 | 1618.13ms | 2090234 | 30 | 1.94251e+12 | 5.68963e+06 | 1(Win) |
| glaze STATISTICAL TIE | 293.266 | 3.54911 | 4705.3ms | 2090234 | 40 | 2.3279e+12 | 6.79724e+06 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 286.363 | 4.36609 | 2351.8ms | 2090234 | 30 | 2.77117e+12 | 6.9611e+06 | 2(Tie) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2116.3 | 7.30836 | 955.676ms | 6661897 | 30 | 1.44412e+12 | 3.00207e+06 | 1(Tie) |
| glaze STATISTICAL TIE | 1937.1 | 6.59029 | 2434.85ms | 6661897 | 40 | 1.86879e+12 | 3.27979e+06 | 1(Tie) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2508.09 | 5.06774 | 97.163ms | 500299 | 40 | 3.7176e+09 | 190234 | 1(Win) |
| glaze | 1302.38 | 0.963637 | 5274.22ms | 500299 | 640 | 7.97607e+09 | 366346 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1012.37 | 5.75335 | 39.4089ms | 56369 | 40 | 3.7334e+08 | 53100.8 | 1(Win) |
| jsonifier STATISTICAL TIE | 822.566 | 5.29678 | 222.472ms | 56369 | 160 | 1.91727e+09 | 65353.6 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 756.485 | 2.14523 | 110.964ms | 56369 | 80 | 1.85916e+08 | 71062.4 | 2(Tie) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1568.74 | 2.0438 | 18.4791ms | 94370 | 30 | 4.12441e+07 | 57369.6 | 1(Win) |
| jsonifier | 1181.5 | 4.17447 | 59.9119ms | 94370 | 40 | 4.04448e+08 | 76172.8 | 2(Loss) |
| simdjson (ondemand) | 585.073 | 6.68074 | 82.6621ms | 94370 | 40 | 4.22433e+09 | 153824 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2704.69 | 0.972312 | 1834.91ms | 94370 | 2560 | 2.67969e+08 | 33274.9 | 1(Win) |
| glaze | 1675.37 | 2.90446 | 673.524ms | 94370 | 640 | 1.55796e+09 | 53718.4 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 731.405 | 4.38218 | 28.138ms | 11812 | 80 | 3.64421e+07 | 15401.6 | 1(Win) |
| glaze | 622.812 | 1.15471 | 485.506ms | 11812 | 1280 | 5.58326e+07 | 18087 | 2(Loss) |
| simdjson (ondemand) | 497.914 | 1.686 | 17.91ms | 11812 | 40 | 5.81989e+06 | 22624 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2688.62 | 4.40055 | 393.369ms | 11812 | 4890 | 1.66231e+08 | 4189.81 | 1(Win) |
| glaze | 1468.4 | 4.23766 | 3.49005ms | 11812 | 30 | 3.17051e+06 | 7671.47 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1472.14 | 1.02313 | 1880.59ms | 108313 | 1280 | 6.59687e+08 | 70167 | 1(Win) |
| glaze | 1191.43 | 1.37723 | 27.3838ms | 108313 | 30 | 4.27717e+07 | 86698.7 | 2(Loss) |
| simdjson (ondemand) | 911.164 | 1.97875 | 178.753ms | 108313 | 80 | 4.02569e+08 | 113366 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1956.19 | 1.81696 | 16.5491ms | 108313 | 30 | 2.76152e+07 | 52804.3 | 1(Win) |
| glaze | 1552.96 | 1.59857 | 101.38ms | 108313 | 80 | 9.04476e+07 | 66515.2 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2050.22 | 3.09025 | 155.692ms | 213963 | 80 | 7.56753e+08 | 99526.4 | 1(Win) |
| glaze | 1654.47 | 1.24012 | 1512.93ms | 213963 | 640 | 1.49716e+09 | 123333 | 2(Loss) |
| simdjson (ondemand) | 1426.66 | 1.79233 | 229.778ms | 213963 | 80 | 5.25732e+08 | 143027 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2485.94 | 3.64039 | 24.321ms | 213963 | 30 | 2.67864e+08 | 82082.1 | 1(Win) |
| glaze | 1848.07 | 1.39026 | 32.2509ms | 213963 | 30 | 7.06892e+07 | 110413 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 439.532 | 0.958251 | 3090.65ms | 1834197 | 40 | 5.8174e+10 | 3.97974e+06 | 1(Win) |
| jsonifier | 397.969 | 3.1786 | 1321.37ms | 1834197 | 30 | 5.85581e+11 | 4.39538e+06 | 2(Loss) |
| simdjson (ondemand) | 96.6819 | 2.01953 | 5526.92ms | 1834197 | 30 | 4.0052e+12 | 1.80926e+07 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 730.235 | 0.278837 | 7617.84ms | 1833577 | 160 | 7.13333e+09 | 2.39462e+06 | 1(Win) |
| jsonifier | 592.444 | 1.57485 | 955.128ms | 1834197 | 30 | 6.48628e+10 | 2.95256e+06 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1741.12 | 0.924226 | 8838.79ms | 9930848 | 80 | 2.02192e+11 | 5.43949e+06 | 1(Tie) |
| glaze STATISTICAL TIE | 1671.19 | 1.93383 | 1867.06ms | 9930848 | 30 | 3.60311e+11 | 5.66709e+06 | 1(Tie) |
| simdjson (ondemand) | 480.306 | 1.01669 | 6010.21ms | 9930848 | 30 | 1.2057e+12 | 1.97183e+07 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2786.65 | 0.909637 | 11601.6ms | 9930848 | 160 | 1.5292e+11 | 3.39863e+06 | 1(Win) |
| glaze | 2437.94 | 1.12064 | 2883.88ms | 9930228 | 40 | 7.57996e+10 | 3.88451e+06 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 441.925 | 0.978236 | 1211.04ms | 1834197 | 30 | 4.49783e+10 | 3.9582e+06 | 1(Win) |
| jsonifier | 413.317 | 2.33008 | 6540.62ms | 1834197 | 80 | 7.77959e+11 | 4.23216e+06 | 2(Loss) |
| simdjson (ondemand) | 344.561 | 0.472287 | 8053.3ms | 1834197 | 80 | 4.59896e+10 | 5.07668e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 572.107 | 0.96777 | 4650.82ms | 1834197 | 80 | 7.00442e+10 | 3.05752e+06 | 1(Win) |
| glaze | 538.381 | 2.47936 | 18572.2ms | 1833577 | 320 | 2.07513e+12 | 3.24795e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1628.51 | 1.09001 | 1804.13ms | 9930848 | 30 | 1.20551e+11 | 5.81561e+06 | 1(Win) |
| simdjson (ondemand) | 1426.25 | 1.12882 | 1996.18ms | 9930848 | 30 | 1.68559e+11 | 6.64032e+06 | 2(Loss) |
| glaze | 1124.01 | 3.82792 | 2503.95ms | 9930848 | 30 | 3.12088e+12 | 8.42587e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2919.45 | 0.489408 | 11179ms | 9930848 | 160 | 4.03303e+10 | 3.24403e+06 | 1(Win) |
| glaze | 2086 | 1.82498 | 7445.42ms | 9930228 | 80 | 5.49156e+11 | 4.53989e+06 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 856.398 | 0.430049 | 246.012ms | 642697 | 30 | 2.84196e+08 | 715699 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 633.227 | 7.99802 | 703.775ms | 642697 | 40 | 2.39728e+11 | 967936 | 2(Tie) |
| jsonifier STATISTICAL TIE | 589.762 | 1.37118 | 6628.05ms | 642697 | 320 | 6.49826e+10 | 1.03927e+06 | 2(Tie) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2201.05 | 1.45967 | 848.413ms | 1225964 | 80 | 4.80942e+09 | 531187 | 1(Win) |
| glaze | 1165.57 | 2.15363 | 698.638ms | 1225970 | 40 | 1.86676e+10 | 1.0031e+06 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 513.31 | 2.43642 | 231.304ms | 409725 | 30 | 1.03193e+10 | 761225 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 435.567 | 2.7363 | 301.616ms | 409725 | 30 | 1.80769e+10 | 897092 | 2(Tie) |
| glaze STATISTICAL TIE | 427.406 | 1.10979 | 12294.1ms | 409725 | 640 | 6.58818e+10 | 914223 | 2(Tie) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1825.5 | 3.96642 | 636.769ms | 409725 | 160 | 1.15329e+10 | 214048 | 1(Win) |
| glaze | 1232.17 | 2.7695 | 464.743ms | 409725 | 80 | 6.17078e+09 | 317120 | 2(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2952.04 | 0.620021 | 80.2911ms | 785750 | 30 | 7.43119e+07 | 253841 | 1(Win) |
| glaze | 1869.35 | 3.48511 | 132.77ms | 785750 | 30 | 5.85522e+09 | 400862 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3116.38 | 1.03572 | 266.816ms | 264040 | 160 | 1.12058e+08 | 80801.6 | 1(Win) |
| simdjson (ondemand) | 2691.18 | 1.17422 | 154.454ms | 264040 | 80 | 9.65702e+07 | 93568 | 2(Loss) |
| glaze | 1809.91 | 3.2461 | 40.553ms | 264040 | 30 | 6.11888e+08 | 139127 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3147.11 | 1.0397 | 90.571ms | 399947 | 40 | 6.35124e+07 | 121197 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3127.23 | 9.15361 | 43.4842ms | 399947 | 30 | 3.7393e+09 | 121967 | 1(Tie) |
| glaze | 1916.02 | 2.00413 | 2273.14ms | 399947 | 640 | 1.01867e+10 | 199068 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1271.45 | 3.33265 | 141.962ms | 264040 | 40 | 1.74253e+09 | 198048 | 1(Win) |
| glaze | 1000.61 | 2.21608 | 1649.87ms | 264040 | 320 | 9.95249e+09 | 251655 | 2(Loss) |
| simdjson (ondemand) | 827.437 | 4.85922 | 449.81ms | 264040 | 80 | 1.74941e+10 | 304323 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1641.72 | 3.53808 | 71.028ms | 399947 | 30 | 2.02703e+09 | 232329 | 1(Win) |
| simdjson (ondemand) | 1448.83 | 1.69694 | 419.823ms | 399947 | 80 | 1.5966e+09 | 263261 | 2(Loss) |
| glaze | 1242.35 | 3.91694 | 216.82ms | 399947 | 40 | 5.78456e+09 | 307014 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4028.99 | 0.902741 | 5135.29ms | 399947 | 2560 | 1.86973e+09 | 94668.6 | 1(Win) |
| glaze | 3114.61 | 3.82138 | 85.0931ms | 399830 | 40 | 8.75479e+08 | 122426 | 2(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2297.81 | 1.24181 | 93.836ms | 699405 | 30 | 3.89819e+08 | 290278 | 1(Win) |
| glaze | 1911.99 | 0.487655 | 1228.54ms | 699405 | 160 | 4.63055e+08 | 348854 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2211.25 | 2.18388 | 1823.23ms | 631514 | 320 | 1.13214e+10 | 272361 | 1(Win) |
| glaze | 1656.35 | 1.00588 | 122.912ms | 631514 | 30 | 4.01303e+08 | 363605 | 2(Loss) |
