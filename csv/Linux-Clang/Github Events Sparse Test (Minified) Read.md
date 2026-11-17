
----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7909.28 | 0.0327712 | 1369.47ms | 53331 | 2560 | 11368.7 | 6430.47 | 0.0503412 | 0.654809 | 3.0039 | 0.422006 | 0.000819074 | 3.69889e-06 | 6.07937e-07 | 1(Win) | true |
| simdjson (ondemand) | 6852.62 | 0.0310358 | 1466ms | 53331 | 2560 | 13583.5 | 7422.04 | 0.142016 | 0.750422 | 3.34655 | 0.4161 | 0.000879011 | 3.36196e-06 | 4.76095e-07 | 2(Loss) | true |
