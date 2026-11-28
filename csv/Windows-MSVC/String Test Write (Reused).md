
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3407.46 | 0.190948 | 132.451ms | 4215 | 320 | 1623.73 | 1179.69 | 0.0794071 | 0.707367 | 1(Win) | true |
| Glaze | 1794.02 | 0.122725 | 236.476ms | 4215 | 320 | 2419.67 | 2240.62 | 0.0837521 | 1.36211 | 2(Loss) | true |
