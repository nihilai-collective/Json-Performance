
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2124 | 0.17248 | 773.148ms | 905 | 4890 | 2402.02 | 406.345 | 0.0203087 | 2.63889 | 12.842 | 2.17127 | 0.00111559 | 0.00012044 | 2.44043e-05 | 1(Win) | true |
| Glaze | 1670.88 | 0.283489 | 781.47ms | 905 | 2560 | 5489.3 | 516.538 | 0.284624 | 3.27995 | 16.9249 | 2.17127 | 0.00114209 | 0.000102728 | 2.3308e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 638.849 | 0.166271 | 870.167ms | 905 | 1280 | 6458.66 | 1350.99 | 0.0324311 | 8.1469 | 41.6032 | 4.94827 | 0.00127072 | 0.000146754 | 3.62569e-05 | 3(Loss) | true |
| simdjson (ondemand) | 289.074 | 0.131664 | 1033.73ms | 905 | 1280 | 19779.7 | 2985.65 | 0.154151 | 17.723 | 88.3271 | 9.35912 | 0.0183132 | 0.000132942 | 2.15815e-05 | 4(Loss) | true |
