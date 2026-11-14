
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13103.4 | 0.353711 | 755.83ms | 3643 | 640 | 562.89 | 265.139 | 0.325769 | 0.445212 | 1.6146 | 0.266813 | 0.000275786 | 2.14452e-05 | 8.57809e-07 | 1(Win) | true |
| Glaze | 3839 | 0.126975 | 822.689ms | 3682 | 4890 | 6595.97 | 914.673 | 0.197134 | 1.37761 | 4.19772 | 0.680608 | 0.000274313 | 3.31575e-05 | 2.99917e-06 | 2(Loss) | true |
