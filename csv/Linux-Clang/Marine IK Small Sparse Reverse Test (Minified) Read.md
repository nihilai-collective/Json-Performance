
----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2899.58 | 0.0440526 | 867.14ms | 4604 | 4890 | 2175.97 | 1514.26 | 0.0417492 | 1.82537 | 9.43571 | 1.67572 | 0.00108215 | 2.24309e-05 | 4.04201e-06 | 1(Win) | true |
| simdjson (ondemand) | 2050.07 | 0.0896826 | 929.515ms | 4604 | 320 | 1180.59 | 2141.74 | 0.0530829 | 2.56258 | 13.2628 | 2.351 | 0.00112063 | 9.50261e-06 | 0 | 2(Loss) | true |
