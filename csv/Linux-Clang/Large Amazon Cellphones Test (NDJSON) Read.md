
----
### Large Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3999.93 | 0.199076 | 7886.86ms | 10548466 | 30 | 7.52028e+08 | 2.515e+06 | 0.0205583 | 1.26935 | 4.20881 | 0.692842 | 0.011384 | 0.0171605 | 0.000661436 | 1(Win) | true |
| simdjson (ondemand) | 3695.61 | 0.221146 | 8508.2ms | 10548466 | 160 | 5.79811e+09 | 2.7221e+06 | 0.390748 | 1.38146 | 4.6488 | 0.75738 | 0.00887879 | 0.0179614 | 0.000509214 | 2(Loss) | true |
