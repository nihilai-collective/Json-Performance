
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2045.35 | 0.430147 | 783.434ms | 905 | 160 | 527.125 | 421.969 | 0.0133286 | 2.76147 | 13.5039 | 2.2895 | 0.00121547 | 0.000103591 | 0 | 1(Win) | true |
| Glaze | 1585.58 | 0.103655 | 770.087ms | 905 | 4890 | 1556.73 | 544.329 | 0.0238519 | 3.4918 | 17.5934 | 2.2895 | 0.00112282 | 0.000115468 | 1.58176e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 633.101 | 0.0987574 | 854.851ms | 905 | 4890 | 8863.37 | 1363.25 | 0.0111538 | 8.33069 | 42.2243 | 5.0663 | 0.00118519 | 0.000133998 | 1.288e-05 | 3(Loss) | true |
| simdjson (ondemand) | 287.495 | 0.092232 | 1024.82ms | 905 | 1280 | 9813.2 | 3002.06 | 0.184301 | 18.0634 | 88.9459 | 9.47735 | 0.0230741 | 0.000152797 | 5.17956e-06 | 4(Loss) | true |
