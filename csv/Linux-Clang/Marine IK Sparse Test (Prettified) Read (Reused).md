
----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9661.19 | 0.308622 | 9257.95ms | 7351818 | 640 | 3.21043e+09 | 725712 | 0.187584 | 0.527868 | 2.49475 | 0.256642 | 0.000782074 | 0.0424168 | 0.000117924 | 1(Win) | true |
| Jsonifier (generic) | 9331.67 | 0.317746 | 9671.32ms | 7351818 | 80 | 4.55954e+08 | 751338 | 0.0279905 | 0.544484 | 2.25888 | 0.261901 | 0.00243062 | 0.0423636 | 0.00019637 | 2(Loss) | true |
