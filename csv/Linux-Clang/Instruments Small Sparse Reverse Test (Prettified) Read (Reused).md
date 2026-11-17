
----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4684.12 | 0.070902 | 884.308ms | 7932 | 4890 | 6411.15 | 1614.94 | 0.699458 | 1.12069 | 5.11299 | 0.784045 | 0.000832511 | 1.3329e-05 | 2.16565e-06 | 1(Win) | true |
| simdjson (ondemand) | 4110.88 | 0.103994 | 901.541ms | 7932 | 1280 | 4687.32 | 1840.13 | 0.0413778 | 1.27925 | 6.07968 | 0.880611 | 0.00134325 | 9.45537e-06 | 4.92467e-07 | 2(Loss) | true |
