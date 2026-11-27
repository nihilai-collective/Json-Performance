
----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5510.63 | 0.109884 | 1172.86ms | 24893 | 2560 | 57366.8 | 4308 | 0.0125205 | 0.925936 | 2.96843 | 0.378741 | 0.000133917 | 2.3805e-05 | 1.19888e-05 | 1(Win) | true |
| Glaze | 3494.6 | 0.10694 | 1418.34ms | 24579 | 2560 | 131720 | 6707.59 | 0.112258 | 1.4545 | 3.73498 | 0.479556 | 0.000310749 | 2.10577e-05 | 9.83754e-06 | 2(Loss) | true |
