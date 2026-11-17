
----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6308.57 | 0.269671 | 8312.82ms | 2090234 | 160 | 1.16176e+08 | 315983 | 0.0168253 | 0.802983 | 4.62947 | 0.716865 | 0.00247044 | 0.0751966 | 5.37918e-06 | 1(Win) | true |
| simdjson (ondemand) | 5590.19 | 0.135797 | 9490.8ms | 2090234 | 160 | 3.7518e+07 | 356590 | 0.200676 | 0.91461 | 5.10596 | 0.738336 | 0.00249183 | 0.0742858 | 3.26817e-06 | 2(Loss) | true |
