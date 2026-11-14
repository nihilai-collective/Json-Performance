
----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4677.71 | 0.0765507 | 819.442ms | 4857 | 2560 | 1470.99 | 990.228 | 0.0557483 | 1.14468 | 4.96026 | 0.725345 | 0.000432205 | 2.98377e-05 | 5.95146e-06 | 1(Win) | true |
| simdjson (ondemand) | 4109.66 | 0.0443468 | 830.114ms | 4857 | 2560 | 639.574 | 1127.1 | 0.236669 | 1.2975 | 5.43072 | 0.71258 | 0.00120429 | 1.50395e-05 | 2.2519e-06 | 2(Loss) | true |
