
----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1132.88 | 0.81003 | 5703.39ms | 4197495 | 30 | 2.45776e+10 | 3.53352e+06 | 0.667982 | 2.6827 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 705.185 | 1.60902 | 8237.72ms | 4197495 | 40 | 3.33702e+11 | 5.67658e+06 | 3.95058 | 4.30983 | -(Loss) | false |
