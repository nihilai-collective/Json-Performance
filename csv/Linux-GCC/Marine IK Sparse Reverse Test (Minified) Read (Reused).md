
----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3092.98 | 0.373548 | 7259.7ms | 1834197 | 320 | 1.42817e+09 | 565547 | 0.0413604 | 1.65252 | 8.50381 | 1.52919 | 0.000761132 | 0.113217 | 3.75164e-06 | 1(Win) | true |
| simdjson (ondemand) | 2209.49 | 0.242136 | 5030.24ms | 1834197 | 80 | 2.93977e+08 | 791686 | 0.0271077 | 2.31193 | 12.8394 | 2.27673 | 0.00488526 | 0.150598 | 4.89315e-06 | 2(Loss) | true |
