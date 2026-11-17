
----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6353.79 | 0.100026 | 8275.77ms | 2090234 | 640 | 6.3028e+07 | 313735 | 0.0545257 | 0.800722 | 4.62939 | 0.716848 | 0.00240175 | 0.0751273 | 4.14128e-06 | 1(Win) | true |
| simdjson (ondemand) | 5434.49 | 0.956253 | 9537.3ms | 2090234 | 640 | 7.87406e+09 | 366806 | 0.140474 | 0.935264 | 5.10588 | 0.738318 | 0.00234006 | 0.074207 | 2.7008e-06 | 2(Loss) | true |
