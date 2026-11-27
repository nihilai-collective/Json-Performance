
----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4439.75 | 0.111974 | 772.977ms | 2632 | 320 | 128.244 | 565.362 | 0.162243 | 1.24687 | 5.3617 | 0.847264 | 0.000387063 | 1.06858e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2837.2 | 0.119389 | 806.117ms | 2632 | 80 | 89.2506 | 884.7 | 0.195362 | 1.90118 | 7.06497 | 1.1421 | 0.000764628 | 1.8997e-05 | 0 | 2(Loss) | true |
