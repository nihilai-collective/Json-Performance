
----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4843.29 | 0.180798 | 806.849ms | 4669 | 1280 | 3536.43 | 919.356 | 0.0695603 | 1.10629 | 4.93639 | 0.682588 | 0.00124608 | 1.12109e-05 | 1.00396e-06 | 1(Win) | true |
| simdjson (ondemand) | 4662.07 | 0.090961 | 810.935ms | 4669 | 1280 | 966.074 | 955.092 | 0.0545074 | 1.14981 | 5.3112 | 0.644035 | 0.00113799 | 1.42228e-05 | 2.84456e-06 | 2(Loss) | true |
