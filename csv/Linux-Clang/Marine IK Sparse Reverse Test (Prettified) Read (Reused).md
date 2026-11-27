
----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7308.25 | 0.160152 | 6109.92ms | 7351818 | 160 | 3.77699e+08 | 959360 | 0.0314401 | 0.697136 | 2.8713 | 0.436856 | 0.00239287 | 0.0635397 | 3.49208e-05 | 1(Win) | true |
| simdjson (ondemand) | 6287.09 | 0.0952002 | 7073.34ms | 7351818 | 320 | 3.60675e+08 | 1.11518e+06 | 0.340746 | 0.807338 | 4.06918 | 0.606495 | 0.000793479 | 0.0847928 | 5.22056e-05 | 2(Loss) | true |
