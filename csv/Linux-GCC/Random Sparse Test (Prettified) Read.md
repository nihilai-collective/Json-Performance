
----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3416.38 | 0.223981 | 5003.9ms | 676745 | 160 | 2.86458e+07 | 188912 | 0.0106443 | 1.4721 | 6.779 | 1.11354 | 0.00378678 | 0.000440519 | 7.15742e-06 | 1(Win) | true |
| simdjson (ondemand) | 3004.55 | 0.111111 | 5692.9ms | 676745 | 80 | 4.55718e+06 | 214806 | 0.00218215 | 1.69621 | 7.01317 | 1.11441 | 0.00565963 | 0.00509906 | 7.53607e-06 | 2(Loss) | true |
