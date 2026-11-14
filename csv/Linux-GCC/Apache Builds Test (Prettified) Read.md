
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1991.32 | 0.0582467 | 6709.87ms | 124597 | 640 | 773134 | 59671.4 | 0.013474 | 2.56554 | 11.671 | 2.17247 | 0.00714995 | 3.51132e-06 | 6.77183e-07 | 1(Win) | true |
| simdjson (ondemand) | 1582.02 | 0.0425103 | 8223.48ms | 124597 | 640 | 652468 | 75109.5 | 0.0292846 | 3.22116 | 12.3701 | 2.3687 | 0.00909846 | 2.73381e-06 | 4.63996e-07 | 2(Loss) | true |
