
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 686.028 | 0.044275 | 129.384ms | 905 | 160 | 49.6421 | 1258.08 | 0.0853751 | 3.53299 | 1(Win) | true |
| simdjson (stage-1) | 307.232 | 0.064483 | 286.554ms | 905 | 30 | 98.4414 | 2809.2 | 0.0249119 | 7.98471 | 2(Loss) | true |
