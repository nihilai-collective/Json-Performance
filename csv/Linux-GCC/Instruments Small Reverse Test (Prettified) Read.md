
----
### Instruments Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 942.825 | 0.0406935 | 1527.52ms | 7932 | 1280 | 13644.7 | 8023.28 | 0.112252 | 5.48719 | 23.4244 | 4.59493 | 0.00512471 | 5.68307e-05 | 2.82676e-05 | 1(Win) | true |
| simdjson (ondemand) | 403.033 | 0.0257274 | 2593.55ms | 7932 | 2560 | 59691.9 | 18769.1 | 0.221243 | 12.643 | 55.5677 | 11.2029 | 0.0369385 | 7.65294e-05 | 3.59994e-05 | 2(Loss) | true |
