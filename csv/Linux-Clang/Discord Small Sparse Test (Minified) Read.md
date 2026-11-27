
----
### Discord Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4122.41 | 0.064717 | 828.993ms | 4857 | 4890 | 2585.71 | 1123.61 | 0.0897272 | 1.29393 | 5.47272 | 0.868643 | 0.000248919 | 6.4377e-05 | 3.42305e-05 | 1(Win) | true |
| simdjson (ondemand) | 3678.2 | 0.0901068 | 845.467ms | 4857 | 2560 | 3296.26 | 1259.31 | 0.0595519 | 1.44386 | 6.01379 | 0.829731 | 0.000281568 | 5.57346e-05 | 3.20896e-05 | 2(Loss) | true |
