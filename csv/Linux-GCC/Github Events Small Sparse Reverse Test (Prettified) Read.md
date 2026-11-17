
----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3774.38 | 0.180259 | 774.481ms | 2158 | 80 | 77.2847 | 545.263 | 0.0114637 | 1.46258 | 5.80816 | 0.979611 | 0.000474977 | 2.8962e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3274.25 | 0.0600771 | 774.554ms | 2158 | 1280 | 182.518 | 628.549 | 0.307327 | 1.67524 | 6.90686 | 1.14319 | 0.000600962 | 1.66532e-05 | 2.8962e-06 | 2(Loss) | true |
