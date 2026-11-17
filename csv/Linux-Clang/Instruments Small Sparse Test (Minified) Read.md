
----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4507.77 | 0.0610897 | 816.196ms | 4669 | 4890 | 1780.62 | 987.785 | 0.0329806 | 1.18843 | 5.1722 | 0.762691 | 0.00128704 | 1.32712e-05 | 1.22638e-06 | 1(Win) | true |
| simdjson (ondemand) | 4190.89 | 0.138573 | 819.936ms | 4669 | 1280 | 2774.62 | 1062.47 | 0.0275083 | 1.27406 | 5.63911 | 0.70165 | 0.00139501 | 1.18802e-05 | 2.50991e-06 | 2(Loss) | true |
