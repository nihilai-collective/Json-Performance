
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 950.027 | 0.127701 | 7040.75ms | 2251027 | 80 | 6.66144e+08 | 2.25967e+06 | 0.121557 | 5.29738 | 29.7605 | 5.98432 | 0.00737916 | 0.0645824 | 0.000132106 | 1(Win) | true |
| Jsonifier (two-stage) | 865.639 | 0.0918624 | 7780.32ms | 2251027 | 30 | 1.55699e+08 | 2.47996e+06 | 0.190106 | 5.81706 | 32.2818 | 6.3719 | 0.0101852 | 0.10257 | 0.000117694 | 2(Loss) | true |
| Glaze | 830.778 | 0.0699154 | 8084.35ms | 2251027 | 160 | 5.22225e+08 | 2.58402e+06 | 0.219185 | 6.05397 | 31.7479 | 5.90113 | 0.0101364 | 0.0635369 | 0.000534395 | 3(Loss) | true |
| simdjson (ondemand) | 795.104 | 0.173373 | 8379.64ms | 2251027 | 40 | 8.76466e+08 | 2.69996e+06 | 0.228246 | 6.31254 | 31.2886 | 5.42074 | 0.0148189 | 0.108696 | 0.00201238 | 4(Loss) | true |
