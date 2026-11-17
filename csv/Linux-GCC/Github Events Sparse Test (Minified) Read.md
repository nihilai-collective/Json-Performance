
----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8074.96 | 0.100344 | 1360.03ms | 53331 | 1280 | 51129.4 | 6298.53 | 0.181995 | 0.632951 | 3.02601 | 0.401286 | 0.000667778 | 4.07244e-06 | 1.30377e-06 | 1(Win) | true |
| simdjson (ondemand) | 6783.49 | 0.0276325 | 1471.37ms | 53331 | 320 | 1373.55 | 7497.67 | 0.149946 | 0.763616 | 3.40252 | 0.420318 | 0.000983715 | 2.22666e-06 | 0 | 2(Loss) | true |
