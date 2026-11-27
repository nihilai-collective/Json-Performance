
----
### Canada Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5767.99 | 0.673687 | 9103.62ms | 2090234 | 160 | 8.67318e+08 | 345598 | 0.456405 | 0.883476 | 4.62832 | 0.756385 | 0.00630445 | 0.0760168 | 4.12334e-06 | 1(Win) | true |
| simdjson (ondemand) | 5420.82 | 0.117777 | 9577.88ms | 2090234 | 640 | 1.20049e+08 | 367731 | 0.0560091 | 0.931422 | 5.10597 | 0.73834 | 0.00285008 | 0.0753796 | 5.24089e-06 | 2(Loss) | true |
