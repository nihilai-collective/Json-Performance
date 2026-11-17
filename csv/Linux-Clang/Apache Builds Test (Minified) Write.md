
----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16396.7 | 0.204823 | 1287.45ms | 94653 | 160 | 20343.9 | 5505.26 | 0.0675035 | 0.310797 | 1.3301 | 0.183903 | 0.00020595 | 1.22157e-05 | 8.51796e-06 | 1(Win) | true |
| Glaze | 5704.39 | 0.13439 | 2369.92ms | 94653 | 320 | 144722 | 15824.3 | 0.250498 | 0.886696 | 4.37627 | 0.666677 | 7.98971e-05 | 5.67864e-06 | 2.41012e-06 | 2(Loss) | true |
