
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3691.83 | 0.0852833 | 957.973ms | 9378 | 2560 | 10927.1 | 2422.53 | 0.224896 | 1.41717 | 6.60621 | 1.13702 | 0.00152876 | 6.10221e-05 | 4.21115e-05 | 1(Win) | true |
| simdjson (reflection) | 3068.78 | 0.134598 | 1015.52ms | 9378 | 30 | 461.62 | 2914.37 | 0.00571847 | 1.73412 | 6.89401 | 1.02367 | 0.00115519 | 1.77721e-05 | 3.55442e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2998.35 | 0.0796971 | 1027.2ms | 9378 | 80 | 452.096 | 2982.82 | 0.0351891 | 1.77402 | 8.23683 | 1.25357 | 0.0019927 | 2.13265e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 2392.8 | 0.0381759 | 1094.85ms | 9378 | 4890 | 9956.3 | 3737.7 | 0.10884 | 2.18023 | 8.80753 | 1.46556 | 0.00101351 | 2.5884e-05 | 7.04342e-06 | 4(Loss) | true |
| Glaze | 2388.85 | 0.0572584 | 1094ms | 9378 | 160 | 735.263 | 3743.88 | 0.0602287 | 2.17972 | 9.47121 | 1.81009 | 0.00356619 | 2.1993e-05 | 1.33291e-06 | 5(Loss) | true |
