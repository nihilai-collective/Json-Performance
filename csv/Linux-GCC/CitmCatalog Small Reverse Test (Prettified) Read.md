
----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1305.03 | 0.104785 | 1448.66ms | 9739 | 40 | 2224.56 | 7116.95 | 0.157357 | 3.9697 | 17.0865 | 3.40589 | 0.00326266 | 2.0536e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 847.462 | 0.030974 | 1834.16ms | 9739 | 320 | 3687.51 | 10959.6 | 0.236969 | 6.10213 | 28.6063 | 5.73355 | 0.00817429 | 0.000144394 | 8.7278e-05 | 2(Loss) | true |
