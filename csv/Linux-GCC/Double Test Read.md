
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 591.023 | 0.0643782 | 1009.86ms | 1811 | 1280 | 4530.19 | 2922.23 | 0.0312164 | 8.83174 | 41.5191 | 6.03368 | 0.00115785 | 0.00014883 | 3.79625e-05 | 1(Win) | true |
| simdjson (ondemand) | 329.117 | 0.0528346 | 1245.49ms | 1811 | 2560 | 19679.4 | 5247.69 | 0.0081949 | 15.7115 | 77.2275 | 9.76091 | 0.00228875 | 0.000115613 | 3.58055e-05 | 2(Loss) | true |
