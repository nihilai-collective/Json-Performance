
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 3058.53 | 0.0759739 | 758.364ms | 1811 | 4890 | 900.013 | 564.684 | 0.0663919 | 1.81755 | 8.79293 | 2.35726 | 0.000810317 | 8.10769e-05 | 6.32355e-06 | 1(Win) | true |
| simdjson (stage-1) | 1340.74 | 0.0526539 | 835.088ms | 1811 | 80 | 36.8044 | 1288.17 | 0.120181 | 3.96404 | 20.8564 | 4.96135 | 0.000938708 | 2.76091e-05 | 0 | 2(Loss) | true |
