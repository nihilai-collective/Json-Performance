
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1325.14 | 0.0985968 | 131.896ms | 1811 | 30 | 49.5402 | 1303.33 | 0.0511247 | 1.8309 | 1(Win) | true |
| Jsonifier (two-stage) | 1267.07 | 0.0892604 | 135.992ms | 1811 | 30 | 44.4092 | 1363.07 | 0.146944 | 1.91796 | 2(Loss) | true |
| Glaze | 899.565 | 0.0701883 | 196.709ms | 1811 | 30 | 54.4782 | 1919.93 | 0.171586 | 2.71622 | 3(Loss) | true |
| simdjson (ondemand) | 463.61 | 0.29005 | 379.483ms | 1811 | 640 | 74723.8 | 3725.34 | 0.0405419 | 5.30404 | 4(Loss) | true |
