
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2024.06 | 0.113126 | 8345.1ms | 676745 | 320 | 4.16369e+07 | 318862 | 0.132288 | 2.48967 | 11.49 | 2.13972 | 0.00602367 | 0.0278802 | 6.40474e-06 | 1(Win) | true |
| simdjson (ondemand) | 1546.07 | 0.0871952 | 5385.31ms | 676745 | 80 | 1.05991e+07 | 417442 | 0.322534 | 3.27171 | 12.6587 | 2.32 | 0.0105905 | 0.0363365 | 1.60326e-05 | 2(Loss) | true |
