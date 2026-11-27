
----
### Random Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3748.76 | 0.0298093 | 9186.35ms | 676745 | 2560 | 6.74246e+06 | 172162 | 0.278564 | 1.35491 | 6.17032 | 1.05057 | 0.00508156 | 0.000971751 | 1.43368e-05 | 1(Win) | true |
| simdjson (ondemand) | 3063.17 | 0.030004 | 5550.99ms | 676745 | 640 | 2.55768e+06 | 210695 | 0.0552244 | 1.65416 | 6.95239 | 1.10638 | 0.00590911 | 0.000837894 | 2.73437e-05 | 2(Loss) | true |
