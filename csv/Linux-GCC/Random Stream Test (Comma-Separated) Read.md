
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1451.7 | 0.238149 | 5244.02ms | 4506446 | 30 | 1.4912e+09 | 2.96045e+06 | 0.00436063 | 3.50584 | 16.8994 | 3.26091 | 0.0111585 | 0.0813177 | 0.00192214 | 1(Win) | true |
| simdjson (ondemand) | 942.365 | 0.107436 | 7596.85ms | 4506446 | 80 | 1.92052e+09 | 4.56053e+06 | 0.653637 | 5.41361 | 21.2197 | 4.41481 | 0.0136754 | 0.088716 | 0.00236273 | 2(Loss) | true |
