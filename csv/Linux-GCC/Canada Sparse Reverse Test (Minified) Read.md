
----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6341.91 | 0.0599873 | 8252.02ms | 2090234 | 1280 | 4.5507e+07 | 314322 | 0.0800295 | 0.79996 | 4.62947 | 0.716865 | 0.0024252 | 0.0760871 | 3.02149e-06 | 1(Win) | true |
| simdjson (ondemand) | 5608.27 | 0.0456905 | 9302.52ms | 2090234 | 640 | 1.68797e+07 | 355440 | 0.122573 | 0.910217 | 5.10596 | 0.738337 | 0.00233051 | 0.0753076 | 8.04336e-07 | 2(Loss) | true |
