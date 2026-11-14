
----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8429.31 | 0.0333599 | 1459.64ms | 65103 | 2560 | 15456.4 | 7365.62 | 0.0430765 | 0.613876 | 2.85097 | 0.339109 | 0.000621065 | 4.02007e-06 | 9.96018e-07 | 1(Win) | true |
| simdjson (ondemand) | 7704.51 | 0.0610759 | 1528.94ms | 65103 | 640 | 15503.6 | 8058.54 | 0.0245022 | 0.67139 | 3.04537 | 0.354101 | 0.000737893 | 2.90405e-06 | 6.24011e-07 | 2(Loss) | true |
