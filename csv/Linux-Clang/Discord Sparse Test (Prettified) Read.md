
----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3277.36 | 0.0272349 | 3178.18ms | 83958 | 1280 | 56668.1 | 24430.8 | 0.0212123 | 1.57231 | 7.17244 | 1.21094 | 0.00273339 | 4.17806e-06 | 1.2376e-06 | 1(Win) | true |
| simdjson (ondemand) | 2730.58 | 0.122075 | 3666.46ms | 83958 | 160 | 205017 | 29322.9 | 0.0406631 | 1.88762 | 7.47084 | 1.17431 | 0.00755214 | 1.03474e-05 | 6.32757e-06 | 2(Loss) | true |
