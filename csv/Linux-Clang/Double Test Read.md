
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2214.77 | 0.348472 | 789.358ms | 1811 | 320 | 2363.01 | 779.812 | 0.137664 | 2.447 | 11.4666 | 1.15075 | 0.00101808 | 3.10602e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 902.545 | 0.0399079 | 904.146ms | 1811 | 160 | 93.3119 | 1913.59 | 0.0114327 | 5.82693 | 30.6129 | 2.45555 | 0.00133559 | 7.59249e-05 | 0 | 2(Loss) | true |
