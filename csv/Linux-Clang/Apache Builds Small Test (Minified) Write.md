
----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9070.02 | 0.491903 | 759.095ms | 2632 | 160 | 296.506 | 276.744 | 0.00225846 | 0.63964 | 1.94947 | 0.31193 | 0.000674392 | 1.66223e-05 | 0 | 1(Win) | true |
| Glaze | 3397.47 | 0.178777 | 803.316ms | 2632 | 2560 | 4466.04 | 738.806 | 0.127893 | 1.57176 | 4.75874 | 0.740122 | 0.000391961 | 4.49694e-05 | 8.16276e-06 | 2(Loss) | true |
