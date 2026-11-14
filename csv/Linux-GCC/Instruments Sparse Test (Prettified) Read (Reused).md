
----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7047.28 | 0.0468417 | 3227.4ms | 183677 | 640 | 86758.4 | 24856.1 | 0.0631657 | 0.731442 | 3.80574 | 0.482091 | 0.000521202 | 7.42642e-06 | 5.019e-06 | 1(Win) | true |
| simdjson (ondemand) | 6723.6 | 0.0353748 | 3356.65ms | 183677 | 640 | 54359.3 | 26052.7 | 0.037072 | 0.766935 | 3.98948 | 0.453405 | 0.000864714 | 3.19855e-06 | 2.07565e-06 | 2(Loss) | true |
