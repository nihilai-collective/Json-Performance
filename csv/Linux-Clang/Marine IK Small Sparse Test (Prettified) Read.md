
----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9740.3 | 0.0738362 | 909.725ms | 18245 | 4890 | 8507.27 | 1786.37 | 0.0634689 | 0.531726 | 2.66002 | 0.283091 | 0.00015721 | 1.2901e-05 | 6.01896e-06 | 1(Win) | true |
| Jsonifier (generic) | 9503.73 | 0.233173 | 908.366ms | 18245 | 160 | 2915.92 | 1830.84 | 0.186053 | 0.544156 | 2.54185 | 0.274431 | 0.000190121 | 5.48095e-06 | 2.39792e-06 | 2(Loss) | true |
