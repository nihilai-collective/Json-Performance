
----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 849.385 | 0.038842 | 8378.52ms | 4506447 | 80 | 3.08997e+08 | 5.05976e+06 | 0.210605 | 5.96715 | 26.8775 | 5.42152 | 0.0131544 | 0.0814058 | 0.00639333 | 1(Win) | true |
| simdjson (ondemand) | 508.134 | 0.101152 | 6290.44ms | 4506447 | 30 | 2.19574e+09 | 8.45777e+06 | 0.203295 | 9.99718 | 43.6994 | 7.78398 | 0.0323102 | 0.0791902 | 0.00530606 | 2(Loss) | true |
