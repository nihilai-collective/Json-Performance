
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1942.44 | 0.0376111 | 1119.76ms | 8150 | 4890 | 11075.5 | 4001.39 | 0.0153293 | 2.67686 | 11.0044 | 2.05153 | 0.00276884 | 2.80026e-05 | 7.1261e-06 | 1(Win) | true |
| simdjson (ondemand) | 1657.65 | 0.0500094 | 1187.62ms | 8150 | 640 | 3518.96 | 4688.85 | 0.127766 | 3.13421 | 12.3863 | 2.1065 | 0.00282458 | 1.97469e-05 | 2.68405e-06 | 2(Loss) | true |
