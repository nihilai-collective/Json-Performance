
----
### Twitter Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7752.66 | 0.0863498 | 4030.91ms | 264040 | 40 | 31464.5 | 32480.2 | 0.0150627 | 0.652754 | 3.32174 | 0.43782 | 0.00125909 | 6.15437e-06 | 3.88199e-06 | 1(Win) | true |
| simdjson (ondemand) | 6374.12 | 0.0337079 | 4759.64ms | 264040 | 2560 | 453944 | 39504.8 | 0.0167126 | 0.794909 | 3.89331 | 0.417321 | 0.00124194 | 1.45885e-05 | 1.13456e-05 | 2(Loss) | true |
