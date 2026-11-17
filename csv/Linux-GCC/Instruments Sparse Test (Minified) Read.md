
----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4987.91 | 0.0537365 | 2802.04ms | 108313 | 640 | 79257.8 | 20709.1 | 0.0176748 | 1.02902 | 5.56725 | 0.815969 | 0.00109714 | 1.42815e-06 | 1.15406e-07 | 1(Win) | true |
| simdjson (ondemand) | 4526.29 | 0.031395 | 3024.56ms | 108313 | 2560 | 131413 | 22821.2 | 0.0426457 | 1.13623 | 5.95205 | 0.776971 | 0.00123237 | 2.08813e-06 | 3.93103e-07 | 2(Loss) | true |
