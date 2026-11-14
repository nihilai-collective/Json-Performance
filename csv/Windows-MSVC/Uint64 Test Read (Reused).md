
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1946.71 | 0.258905 | 193.731ms | 3873 | 2560 | 61774.9 | 1897.34 | 0.0123513 | 1.53578 | 1(Win) | true |
| Glaze | 1156.84 | 0.14877 | 322.301ms | 3873 | 640 | 14439.7 | 3192.81 | 0 | 2.59571 | 2(Loss) | true |
| Jsonifier (two-stage) | 1019.53 | 0.0736571 | 363.832ms | 3873 | 2560 | 18228.9 | 3622.81 | 0.0625769 | 2.96009 | 3(Loss) | true |
| simdjson (ondemand) | 470.52 | 0.313187 | 779.795ms | 3873 | 80 | 48354.4 | 7850 | 1.19572 | 6.44029 | 4(Loss) | true |
