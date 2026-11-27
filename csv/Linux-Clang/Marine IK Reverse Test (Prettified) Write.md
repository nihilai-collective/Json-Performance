
----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5097.55 | 0.0557549 | 5841.88ms | 10018896 | 80 | 8.73721e+07 | 1.87438e+06 | 0.0339777 | 0.992539 | 3.46093 | 0.404708 | 0.000339107 | 0.0245813 | 0.00012325 | 1(Win) | true |
| Glaze | 3712.6 | 0.140313 | 7941.47ms | 9930228 | 40 | 5.12409e+08 | 2.55083e+06 | 0.345719 | 1.36135 | 4.21672 | 0.48471 | 0.00108257 | 0.0412821 | 0.00109768 | 2(Loss) | true |
