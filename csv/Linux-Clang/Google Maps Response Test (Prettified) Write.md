
----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15701 | 0.159437 | 928.837ms | 31235 | 320 | 2927.93 | 1897.21 | 0.001153 | 0.329131 | 1.41972 | 0.26307 | 5.22251e-05 | 8.30399e-06 | 3.80182e-06 | 1(Win) | true |
| Glaze | 5207.74 | 0.0884955 | 1314.11ms | 31235 | 1280 | 32797.2 | 5719.95 | 0.163648 | 0.977917 | 3.70312 | 0.653946 | 0.00233492 | 1.56325e-05 | 6.22799e-06 | 2(Loss) | true |
