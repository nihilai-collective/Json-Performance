
----
### Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5857.27 | 0.124306 | 5285.27ms | 277673 | 640 | 2.02135e+06 | 45210.4 | 0.106311 | 0.873904 | 3.87618 | 0.653348 | 0.00433848 | 2.77417e-06 | 1.64875e-06 | 1(Win) | true |
| simdjson (ondemand) | 4625.56 | 0.0467298 | 6465.95ms | 277673 | 1280 | 916086 | 57249.2 | 0.152242 | 1.10927 | 4.46623 | 0.711352 | 0.00327831 | 4.21471e-06 | 2.75729e-06 | 2(Loss) | true |
