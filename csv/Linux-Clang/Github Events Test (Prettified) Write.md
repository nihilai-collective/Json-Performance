
----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15247.2 | 0.360905 | 1237.59ms | 78778 | 1280 | 404783 | 4927.35 | 0.371627 | 0.333706 | 1.1357 | 0.180063 | 2.8839e-05 | 7.17007e-06 | 3.87759e-06 | 1(Win) | true |
| Glaze | 4469.24 | 0.198267 | 2431.34ms | 78778 | 1280 | 1.42186e+06 | 16810.2 | 0.19131 | 1.13302 | 3.0214 | 0.489122 | 0.000340444 | 2.43168e-05 | 8.96507e-06 | 2(Loss) | true |
