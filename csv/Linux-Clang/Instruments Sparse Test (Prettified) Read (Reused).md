
----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6775.08 | 0.0301817 | 3326.31ms | 183677 | 640 | 38971.7 | 25854.8 | 0.000290083 | 0.761094 | 3.768 | 0.506046 | 0.000400295 | 1.11439e-06 | 7.6561e-08 | 1(Win) | true |
| simdjson (ondemand) | 6529.14 | 0.168942 | 3435.02ms | 183677 | 40 | 82173.9 | 26828.7 | 0.0388417 | 0.789868 | 4.00195 | 0.447476 | 0.00104912 | 1.08887e-06 | 0 | 2(Loss) | true |
