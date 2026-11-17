
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11971.4 | 0.354277 | 751.911ms | 2632 | 2560 | 1412.58 | 209.673 | 0.00391219 | 0.506198 | 1.67819 | 0.255699 | 0.000381423 | 3.6955e-05 | 4.15559e-06 | 1(Win) | true |
| Glaze | 3657.25 | 0.118583 | 801.838ms | 2632 | 4890 | 3239.06 | 686.328 | 0.0561341 | 1.46576 | 4.30509 | 0.647417 | 0.000383824 | 4.70845e-05 | 6.60426e-06 | 2(Loss) | true |
