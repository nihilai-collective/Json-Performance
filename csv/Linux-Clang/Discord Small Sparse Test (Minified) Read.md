
----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4000.57 | 0.0321886 | 830.697ms | 4857 | 1280 | 177.79 | 1157.83 | 0.11112 | 1.33283 | 5.5456 | 0.890056 | 0.000307707 | 2.20365e-05 | 2.09105e-06 | 1(Win) | true |
| simdjson (ondemand) | 3603.96 | 0.0557733 | 842.828ms | 4857 | 640 | 328.858 | 1285.25 | 0.0538272 | 1.47384 | 6.01462 | 0.829319 | 0.00035194 | 1.80152e-05 | 4.82551e-06 | 2(Loss) | true |
