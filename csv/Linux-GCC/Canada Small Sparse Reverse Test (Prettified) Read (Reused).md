
----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10096.4 | 0.0603655 | 824.026ms | 11579 | 2560 | 1115.91 | 1093.72 | 0.0649725 | 0.529756 | 2.72381 | 0.340962 | 0.000259326 | 1.45738e-05 | 7.05075e-06 | 1(Win) | true |
| simdjson (ondemand) | 8002.65 | 0.133212 | 851.92ms | 11579 | 1280 | 4324.84 | 1379.87 | 0.216264 | 0.662312 | 3.02479 | 0.35953 | 0.000266377 | 3.56923e-05 | 1.47762e-05 | 2(Loss) | true |
