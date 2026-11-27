
----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2938.59 | 0.0673782 | 807.553ms | 2632 | 640 | 211.989 | 854.177 | 0.147403 | 1.80591 | 7.87082 | 1.41299 | 0.00117544 | 5.93655e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2341.8 | 0.0450998 | 854.761ms | 2632 | 2560 | 598.221 | 1071.86 | 0.0776015 | 2.28 | 8.85828 | 1.51938 | 0.0017118 | 6.456e-05 | 2.56756e-05 | 2(Loss) | true |
