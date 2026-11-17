
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1396.05 | 0.123762 | 5320.38ms | 4506446 | 40 | 5.8063e+08 | 3.07846e+06 | 0.455639 | 3.63011 | 16.9 | 3.26103 | 0.011305 | 0.0813363 | 0.00524464 | 1(Win) | true |
| simdjson (ondemand) | 924.238 | 0.329723 | 7733.38ms | 4506446 | 30 | 7.05215e+09 | 4.64997e+06 | 0.168479 | 5.4686 | 21.2216 | 4.4134 | 0.013439 | 0.0886097 | 0.00902644 | 2(Loss) | true |
