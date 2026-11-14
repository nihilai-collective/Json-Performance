
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2004.28 | 0.206301 | 799.452ms | 1811 | 320 | 1011.29 | 861.709 | 0.262157 | 2.71467 | 14.1883 | 1.25069 | 0.0032872 | 4.31391e-05 | 1.72557e-06 | 1(Win) | true |
| simdjson (stage-1) | 691.728 | 0.0582386 | 963.364ms | 1811 | 1280 | 2706.44 | 2496.8 | 0.0230035 | 7.56683 | 38.2275 | 2.89619 | 0.00110436 | 0.000101808 | 1.29417e-05 | 2(Loss) | true |
