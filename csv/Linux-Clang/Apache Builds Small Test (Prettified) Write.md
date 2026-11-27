
----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10978.2 | 0.291214 | 761.97ms | 3643 | 2560 | 2174.3 | 316.466 | 0.587019 | 0.520414 | 1.75872 | 0.293989 | 0.000442094 | 2.54126e-05 | 2.35898e-06 | 1(Win) | true |
| Glaze | 3379.42 | 0.156822 | 835.979ms | 3682 | 2560 | 6797.27 | 1039.06 | 0.0240919 | 1.55801 | 4.54943 | 0.761 | 0.000283049 | 2.85383e-05 | 3.2888e-06 | 2(Loss) | true |
