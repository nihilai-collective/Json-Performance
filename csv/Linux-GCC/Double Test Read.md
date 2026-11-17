
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2026.73 | 0.0836008 | 798.721ms | 1811 | 4890 | 2481.85 | 852.164 | 0.0237018 | 2.65747 | 14.1883 | 1.25069 | 0.00305506 | 0.000102758 | 2.67622e-05 | 1(Win) | true |
| simdjson (stage-1) | 691.08 | 0.0365978 | 963.967ms | 1811 | 1280 | 1070.78 | 2499.14 | 0.0263146 | 7.57727 | 38.2275 | 2.89619 | 0.00110436 | 8.32586e-05 | 3.45113e-06 | 2(Loss) | true |
