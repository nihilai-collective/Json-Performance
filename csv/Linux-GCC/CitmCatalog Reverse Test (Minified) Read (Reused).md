
----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 784.745 | 0.0844423 | 8264.5ms | 500299 | 160 | 4.21738e+07 | 607997 | 0.0733549 | 6.49727 | 33.6561 | 6.96693 | 0.0155532 | 0.0149535 | 5.89522e-05 | 1(Win) | true |
| simdjson (ondemand) | 439.128 | 0.0606411 | 7159.19ms | 500299 | 320 | 1.38918e+08 | 1.08652e+06 | 0.228696 | 11.559 | 62.368 | 12.8379 | 0.0294825 | 0.021542 | 6.86027e-05 | 2(Loss) | true |
