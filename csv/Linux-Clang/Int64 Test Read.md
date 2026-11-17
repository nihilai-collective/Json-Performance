
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1546.04 | 0.102544 | 957.83ms | 3862 | 30 | 179.03 | 2382.27 | 0.0671178 | 3.38726 | 16.9443 | 2.10176 | 0.00133782 | 2.58933e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 794.342 | 0.0598263 | 1186.57ms | 3862 | 1280 | 9849.25 | 4636.65 | 0.0338114 | 6.53503 | 28.2372 | 3.48887 | 0.0130735 | 6.49356e-05 | 2.4275e-05 | 2(Loss) | true |
