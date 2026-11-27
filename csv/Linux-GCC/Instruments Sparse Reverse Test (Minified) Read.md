
----
### Instruments Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3404.74 | 0.0771395 | 3778.34ms | 108313 | 1280 | 701063 | 30338.7 | 0.197257 | 1.50138 | 7.79926 | 1.4324 | 0.000914068 | 4.0825e-06 | 1.55077e-06 | 1(Win) | true |
| simdjson (ondemand) | 2688.75 | 0.0428196 | 4603.86ms | 108313 | 30 | 8118.37 | 38417.7 | 0.029665 | 1.91821 | 9.89856 | 1.62164 | 0.00367638 | 1.8465e-06 | 9.2325e-07 | 2(Loss) | true |
