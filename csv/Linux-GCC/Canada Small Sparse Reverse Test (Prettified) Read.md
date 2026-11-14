
----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10009.4 | 0.100962 | 823.883ms | 11579 | 1280 | 1588.01 | 1103.22 | 0.0853305 | 0.533049 | 2.7372 | 0.344158 | 0.000259562 | 7.42184e-06 | 6.07242e-07 | 1(Win) | true |
| simdjson (ondemand) | 7916.87 | 0.0827041 | 851.084ms | 11579 | 160 | 212.917 | 1394.82 | 0.157032 | 0.669204 | 3.03869 | 0.362812 | 0.00025963 | 1.07954e-06 | 0 | 2(Loss) | true |
