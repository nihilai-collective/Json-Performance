
----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3515.1 | 0.0177113 | 3677.53ms | 108313 | 2560 | 69347 | 29386.2 | 0.0445496 | 1.46586 | 7.88731 | 1.41192 | 0.00123569 | 2.58222e-06 | 7.21289e-07 | 1(Win) | true |
| simdjson (ondemand) | 2658.64 | 0.0845885 | 4636ms | 108313 | 1280 | 1.38253e+06 | 38852.7 | 0.0344753 | 1.93637 | 9.76064 | 1.58674 | 0.00354958 | 2.18551e-06 | 1.15406e-07 | 2(Loss) | true |
