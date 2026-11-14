
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12445.3 | 0.172698 | 750.432ms | 2632 | 160 | 19.4112 | 201.688 | 0.360764 | 0.487835 | 1.67819 | 0.255699 | 0.000379939 | 2.37462e-05 | 0 | 1(Win) | true |
| Glaze | 3503.83 | 0.150757 | 800.673ms | 2632 | 4890 | 5703.62 | 716.38 | 0.138488 | 1.52646 | 4.30509 | 0.647417 | 0.000387787 | 4.43651e-05 | 3.03019e-06 | 2(Loss) | true |
