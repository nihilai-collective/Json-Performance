
----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3407.01 | 0.207754 | 3790.78ms | 108313 | 320 | 1.26959e+06 | 30318.5 | 0.0553913 | 1.51315 | 8.00572 | 1.39499 | 0.00127302 | 1.8465e-06 | 1.73109e-07 | 1(Win) | true |
| simdjson (ondemand) | 2719.69 | 0.113232 | 4557.3ms | 108313 | 160 | 295927 | 37980.6 | 0.0399706 | 1.89502 | 10.1578 | 1.5475 | 0.00262261 | 3.17367e-06 | 5.19328e-07 | 2(Loss) | true |
