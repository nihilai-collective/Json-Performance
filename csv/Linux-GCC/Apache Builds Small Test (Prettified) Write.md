
----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14676.1 | 0.176503 | 746.043ms | 3643 | 4890 | 853.706 | 236.727 | 0.455465 | 0.405135 | 1.30058 | 0.213835 | 0.000274667 | 2.53729e-05 | 7.29752e-06 | 1(Win) | true |
| Glaze | 4118.47 | 0.403309 | 816.754ms | 3682 | 640 | 7567.47 | 852.605 | 0.369534 | 1.3002 | 4.21564 | 0.702607 | 0.00027244 | 3.35246e-05 | 5.94106e-06 | 2(Loss) | true |
| simdjson (reflection) | 547.68 | 0.0589337 | 1376.91ms | 3643 | 4890 | 68344.1 | 6343.55 | 0.0414783 | 9.24841 | 36.0807 | 7.55861 | 0.0140967 | 0.000218364 | 0.000103232 | 3(Loss) | true |
