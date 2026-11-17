
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1010.74 | 0.256249 | 173.465ms | 1811 | 160 | 3067.61 | 1708.75 | 0.0732064 | 2.94179 | 1(Win) | true |
| Jsonifier (two-stage) | 635.841 | 0.201261 | 286.149ms | 1811 | 80 | 2390.82 | 2716.25 | 0.138249 | 4.74433 | 2(Loss) | true |
| Glaze | 598.304 | 0.218675 | 299.25ms | 1811 | 30 | 1195.4 | 2886.67 | 0 | 4.99249 | 3(Loss) | true |
| simdjson (ondemand) | 281.746 | 0.117522 | 623.163ms | 1811 | 80 | 4151.9 | 6130 | 0.0814996 | 10.7308 | 4(Loss) | true |
