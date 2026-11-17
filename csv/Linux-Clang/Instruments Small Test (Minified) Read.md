
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1435.38 | 0.0503935 | 1032.74ms | 4669 | 2560 | 6256.11 | 3102.11 | 0.0387564 | 3.63561 | 14.7323 | 2.98672 | 0.00264879 | 8.46675e-05 | 3.84016e-05 | 1(Win) | true |
| simdjson (ondemand) | 1401.02 | 0.0516331 | 1042.02ms | 4669 | 2560 | 6893.73 | 3178.19 | 0.0653199 | 3.71834 | 16.4699 | 2.48704 | 0.00101609 | 4.50946e-05 | 1.28005e-05 | 2(Loss) | true |
