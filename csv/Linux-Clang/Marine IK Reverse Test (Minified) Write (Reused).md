
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1342.47 | 0.0806783 | 8659.93ms | 1922245 | 160 | 1.94197e+08 | 1.36554e+06 | 0.106545 | 3.79819 | 12.3634 | 0.737426 | 0.000717768 | 0.0570136 | 0.000878563 | 1(Win) | true |
| Glaze | 656.462 | 0.185396 | 8371.95ms | 1833577 | 80 | 1.95105e+09 | 2.66373e+06 | 0.0442081 | 7.83347 | 16.0113 | 0.996381 | 0.00111002 | 0.049134 | 0.000113958 | 2(Loss) | true |
