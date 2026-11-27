
----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1330.26 | 0.0503994 | 8760.89ms | 1922245 | 320 | 1.54364e+08 | 1.37807e+06 | 0.0574562 | 3.82195 | 12.344 | 0.737427 | 0.000614589 | 0.0584023 | 0.000176857 | 1(Win) | true |
| Glaze | 664.4 | 0.160356 | 8234.58ms | 1833577 | 80 | 1.42496e+09 | 2.6319e+06 | 0.200893 | 7.68649 | 16.0106 | 0.996384 | 0.0010765 | 0.049105 | 0.000113883 | 2(Loss) | true |
