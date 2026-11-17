
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3259.37 | 0.140183 | 115.393ms | 3862 | 1280 | 3211.88 | 1130 | 0.069185 | 0.915612 | 1(Win) | true |
| simdjson (stage-1) | 1124.42 | 0.0958014 | 330.54ms | 3862 | 2560 | 25208.8 | 3275.55 | 0.0667382 | 2.68281 | 2(Loss) | true |
