
----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5201.26 | 0.0352347 | 5838.24ms | 277673 | 320 | 102977 | 50912.6 | 0.000945257 | 0.990583 | 4.30864 | 0.678261 | 0.00311565 | 1.71065e-06 | 3.37627e-08 | 1(Win) | true |
| simdjson (ondemand) | 4111.55 | 0.244642 | 7221.68ms | 277673 | 80 | 1.98614e+06 | 64406.3 | 0.159224 | 1.25263 | 4.69362 | 0.771527 | 0.00496231 | 2.79105e-06 | 9.0034e-08 | 2(Loss) | true |
