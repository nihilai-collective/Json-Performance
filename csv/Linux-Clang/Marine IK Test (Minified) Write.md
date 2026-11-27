
----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1319.39 | 0.0689977 | 8775.18ms | 1922245 | 80 | 7.35241e+07 | 1.38943e+06 | 0.165275 | 3.82818 | 12.3442 | 0.737465 | 0.000619113 | 0.0584975 | 0.000440475 | 1(Win) | true |
| Glaze | 641.919 | 0.126972 | 8508.37ms | 1833577 | 80 | 9.57067e+08 | 2.72407e+06 | 0.0414877 | 7.89368 | 16.0115 | 0.996581 | 0.0011158 | 0.082493 | 0.000241468 | 2(Loss) | true |
