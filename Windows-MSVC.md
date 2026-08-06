# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Aug 03, 2026)
#### Using the following commits:
----
| Jsonifier: [fa275f4](https://github.com/nihilai-collective/jsonifier/commit/fa275f4)  
| Simdjson (On Demand): [cbca9e9](https://github.com/simdjson/simdjson/commit/cbca9e9)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below.

> Both libraries are executing only 'stage-1' parsing, where they identify the structural indices, and neither of them are performing utf-8 validation in these tests. Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 80 and double each epoch (e.g. 80 → 160 → 320 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 2.5% AND mean shift < 1% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 10 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [97c14b0](https://github.com/realtimechris/benchmarksuite/commit/97c14b0).
  
----
### Abc Test (Minified) Results [(View the data used in the following test)](./json/Abc%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13231 | 0.350191 | 1.6531ms | 33713 | 30 | 2172.41 | 2430 | 0.228099 | 1(Win) |
| simdjson (ondemand) | 11907.9 | 0.166301 | 3.1189ms | 33713 | 32 | 645.161 | 2700 | 0.251805 | 2(Loss) |

----
### Abc Test (Prettified) Results [(View the data used in the following test)](./json/Abc%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Abc%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Abc%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13590.3 | 0.252511 | 1.9049ms | 48024 | 30 | 2172.41 | 3370 | 0.221795 | 1(Win) |
| simdjson (ondemand) | 12998.8 | 0.261169 | 1.8919ms | 48024 | 30 | 2540.23 | 3523.33 | 0.232437 | 2(Loss) |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13940.7 | 0.155062 | 5.2266ms | 94651 | 32 | 3225.81 | 6475 | 0.217287 | 1(Win) |
| simdjson (ondemand) | 12520.7 | 0.130039 | 5.712ms | 94651 | 32 | 2812.5 | 7209.38 | 0.242084 | 2(Loss) |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 13846.3 | 2.20992 | 13.3456ms | 136024 | 64 | 2.74345e+06 | 9368.75 | 0.218738 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 13364.9 | 1.0302 | 7.0635ms | 136024 | 32 | 319960 | 9706.25 | 0.226737 | 1(Tie) |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13410.6 | 1.0374 | 36.9127ms | 2090234 | 30 | 7.13356e+07 | 148643 | 0.226487 | 1(Win) |
| simdjson (ondemand) | 9240.98 | 1.09282 | 52.7642ms | 2090234 | 30 | 1.66714e+08 | 215713 | 0.328728 | 2(Loss) |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 19039.1 | 0.518975 | 82.0383ms | 6661897 | 30 | 8.99741e+07 | 333697 | 0.159505 | 1(Win) |
| simdjson (ondemand) | 13949.3 | 0.373664 | 110.535ms | 6661897 | 30 | 8.68915e+07 | 455457 | 0.217742 | 2(Loss) |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10294.6 | 1.12633 | 12.2569ms | 500299 | 30 | 8.17499e+06 | 46346.7 | 0.295053 | 1(Win) |
| simdjson (ondemand) | 9182.49 | 1.12488 | 13.6171ms | 500299 | 30 | 1.02487e+07 | 51960 | 0.33079 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13089.5 | 1.12129 | 26.2741ms | 1439562 | 30 | 4.14925e+07 | 104883 | 0.232052 | 1(Win) |
| simdjson (ondemand) | 12089.1 | 1.49035 | 28.1011ms | 1439562 | 30 | 8.59355e+07 | 113563 | 0.251299 | 2(Loss) |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11084.1 | 0.191438 | 2.297ms | 56369 | 30 | 2586.21 | 4850 | 0.272876 | 1(Win) |
| simdjson (ondemand) | 10149.3 | 0.0629327 | 2.3386ms | 56369 | 30 | 333.333 | 5296.67 | 0.297307 | 2(Loss) |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12402.1 | 0.126806 | 2.8229ms | 94370 | 30 | 2540.23 | 7256.67 | 0.244489 | 1(Win) |
| simdjson (ondemand) | 11890.8 | 1.64493 | 11.2321ms | 94370 | 64 | 992024 | 7568.75 | 0.254234 | 2(Loss) |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14893.7 | 0.266082 | 3.4967ms | 52708 | 32 | 2580.65 | 3375 | 0.203249 | 1(Win) |
| simdjson (ondemand) | 13249.8 | 0.114598 | 3.7581ms | 52708 | 32 | 604.839 | 3793.75 | 0.226884 | 2(Loss) |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14418.9 | 1.26851 | 2.1777ms | 70103 | 30 | 103782 | 4636.67 | 0.209419 | 1(Win) |
| simdjson (ondemand) | 13957.3 | 0.116302 | 2.2245ms | 70103 | 30 | 931.034 | 4790 | 0.216226 | 2(Loss) |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10179 | 0.418559 | 1.2864ms | 11812 | 30 | 643.678 | 1106.67 | 0.294712 | 1(Win) |
| simdjson (ondemand) | 9519.55 | 0.584827 | 1.3398ms | 11812 | 30 | 1436.78 | 1183.33 | 0.315103 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13278.5 | 0.410187 | 1.6575ms | 31235 | 30 | 2540.23 | 2243.33 | 0.226737 | 1(Win) |
| simdjson (ondemand) | 12766.3 | 0.375161 | 1.6184ms | 31235 | 30 | 2298.85 | 2333.33 | 0.235238 | 2(Loss) |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10835.2 | 1.04088 | 3.4066ms | 108313 | 30 | 295402 | 9533.33 | 0.279603 | 1(Win) |
| simdjson (ondemand) | 9951.38 | 0.0715589 | 3.6793ms | 108313 | 30 | 1655.17 | 10380 | 0.304472 | 2(Loss) |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 12606.1 | 2.40691 | 4.946ms | 213963 | 30 | 4.55361e+06 | 16186.7 | 0.240599 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 12301.5 | 0.37484 | 10.8646ms | 213963 | 32 | 123710 | 16587.5 | 0.246537 | 1(Tie) |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8702.76 | 1.10939 | 49.5845ms | 1834197 | 30 | 1.49166e+08 | 200997 | 0.349009 | 1(Win) |
| simdjson (ondemand) | 7000.55 | 0.6841 | 61.3524ms | 1834197 | 30 | 8.76573e+07 | 249870 | 0.433921 | 2(Loss) |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 15536.6 | 0.559354 | 146.723ms | 9930848 | 30 | 3.48784e+08 | 609580 | 0.19553 | 1(Win) |
| simdjson (ondemand) | 12657 | 0.323989 | 180.987ms | 9930848 | 30 | 1.76316e+08 | 748263 | 0.240045 | 2(Loss) |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11473.7 | 1.11115 | 13.8121ms | 642697 | 30 | 1.05699e+07 | 53420 | 0.264734 | 1(Win) |
| simdjson (ondemand) | 9515.97 | 1.12259 | 16.5681ms | 642697 | 30 | 1.56844e+07 | 64410 | 0.31919 | 2(Loss) |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13393.6 | 0.850866 | 22.1969ms | 1225964 | 30 | 1.65503e+07 | 87293.3 | 0.226776 | 1(Win) |
| simdjson (ondemand) | 12098.6 | 0.775512 | 24.2893ms | 1225964 | 30 | 1.68493e+07 | 96636.7 | 0.251073 | 2(Loss) |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11545.5 | 1.3334 | 20.74ms | 409725 | 32 | 6.51673e+06 | 33843.8 | 0.262989 | 1(Win) |
| simdjson (ondemand) | 10248.6 | 1.35617 | 10.193ms | 409725 | 30 | 8.02064e+06 | 38126.7 | 0.296263 | 2(Loss) |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 12916.1 | 1.27938 | 14.9723ms | 785750 | 30 | 1.65283e+07 | 58016.7 | 0.2351 | 1(Win) |
| simdjson (ondemand) | 12366.9 | 0.654037 | 16.1188ms | 785750 | 30 | 4.71168e+06 | 60593.3 | 0.245644 | 2(Loss) |

----
### Semanticscholar Corpus Test (Minified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11203.3 | 0.510683 | 178.14ms | 8587914 | 30 | 4.18125e+08 | 731040 | 0.271161 | 1(Win) |
| simdjson (ondemand) | 9320.92 | 0.401809 | 213.415ms | 8587914 | 30 | 3.73955e+08 | 878677 | 0.325956 | 2(Loss) |

----
### Semanticscholar Corpus Test (Prettified) Results [(View the data used in the following test)](./json/Semanticscholar%20Corpus%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Semanticscholar%20Corpus%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 11409.3 | 0.315179 | 198.368ms | 9804437 | 30 | 2.00152e+08 | 819527 | 0.266288 | 1(Win) |
| simdjson (ondemand) | 9947.98 | 0.466577 | 227.727ms | 9804437 | 30 | 5.76958e+08 | 939913 | 0.305409 | 2(Loss) |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 13826.1 | 0.112305 | 12.063ms | 264040 | 32 | 13387.1 | 18212.5 | 0.219474 | 1(Win) |
| simdjson (ondemand) | 12330.3 | 1.09719 | 26.915ms | 264040 | 64 | 3.21316e+06 | 20421.9 | 0.24609 | 2(Loss) |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 14214.4 | 1.41884 | 7.6433ms | 399947 | 30 | 4.34851e+06 | 26833.3 | 0.213631 | 1(Win) |
| simdjson (ondemand) | 13282.2 | 1.32229 | 8.0232ms | 399947 | 30 | 4.32557e+06 | 28716.7 | 0.228539 | 2(Loss) |
