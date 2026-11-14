
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2830.69 | 0.0404774 | 826.873ms | 3370 | 4890 | 1032.78 | 1135.37 | 0.0406324 | 1.8831 | 7.87389 | 1.42018 | 0.001014 | 3.08872e-05 | 2.60933e-06 | 1(Win) | true |
| simdjson (ondemand) | 2598.7 | 0.0366962 | 836.153ms | 3370 | 2560 | 527.266 | 1236.73 | 0.0431011 | 2.04587 | 7.97507 | 1.31217 | 0.00288738 | 2.96736e-05 | 1.04321e-06 | 2(Loss) | true |
