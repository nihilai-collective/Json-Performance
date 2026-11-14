
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1395.62 | 0.109129 | 1051.88ms | 4604 | 2560 | 30175.4 | 3146.06 | 0.231413 | 3.66174 | 9.31951 | 0.631408 | 0.000595016 | 5.45551e-05 | 2.57928e-05 | 1(Win) | true |
| Glaze | 827.061 | 0.0909481 | 1267.06ms | 4604 | 2560 | 59679.3 | 5308.82 | 0.0129592 | 6.16577 | 12.4472 | 0.970679 | 0.000826048 | 7.09302e-05 | 2.66412e-05 | 2(Loss) | true |
