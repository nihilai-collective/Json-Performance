
----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4968.74 | 0.0236415 | 2803.06ms | 108313 | 4890 | 118121 | 20789.1 | 0.0658282 | 1.03388 | 5.56753 | 0.81608 | 0.00110043 | 8.37722e-06 | 5.666e-06 | 1(Win) | true |
| simdjson (ondemand) | 4455.59 | 0.0259558 | 3042.51ms | 108313 | 2560 | 92695.5 | 23183.3 | 0.0379238 | 1.15321 | 5.94996 | 0.775964 | 0.00149105 | 2.39107e-06 | 6.56373e-07 | 2(Loss) | true |
