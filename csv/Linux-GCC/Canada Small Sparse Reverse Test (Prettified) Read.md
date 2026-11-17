
----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9927.07 | 0.0749827 | 827.851ms | 11579 | 4890 | 3401.97 | 1112.37 | 0.0470711 | 0.536425 | 2.7372 | 0.344158 | 0.000259726 | 8.88358e-06 | 1.94273e-06 | 1(Win) | true |
| simdjson (ondemand) | 7888.36 | 0.122202 | 854.739ms | 11579 | 1280 | 3745.71 | 1399.86 | 0.270888 | 0.671745 | 3.03878 | 0.362639 | 0.000259495 | 1.49112e-05 | 3.44104e-06 | 2(Loss) | true |
