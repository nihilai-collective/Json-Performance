
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3507.7 | 0.995206 | 115.951ms | 3862 | 30 | 3275.86 | 1050 | 0.318471 | 0.688244 | 1(Win) | true |
| Glaze | 1656.31 | 0.31719 | 236.464ms | 3862 | 2560 | 127357 | 2223.67 | 0.03163 | 1.4761 | 2(Loss) | true |
