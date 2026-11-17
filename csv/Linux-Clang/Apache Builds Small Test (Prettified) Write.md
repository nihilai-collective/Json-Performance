
----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10280.8 | 0.253075 | 764.618ms | 3643 | 4890 | 3576.64 | 337.936 | 0.00209133 | 0.555974 | 1.77436 | 0.307713 | 0.000415959 | 4.50201e-05 | 1.29671e-05 | 1(Win) | true |
| Glaze | 3640.6 | 0.118555 | 832.971ms | 3682 | 4890 | 6393.96 | 964.519 | 0.0777497 | 1.45288 | 4.48588 | 0.746605 | 0.000278812 | 5.29298e-05 | 1.04416e-05 | 2(Loss) | true |
