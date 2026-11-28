
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 927.398 | 0.293688 | 189.954ms | 1811 | 4890 | 146280 | 1862.31 | 0.110716 | 2.62945 | 1(Win) | true |
| Glaze | 472.29 | 0.110106 | 380.904ms | 1811 | 160 | 2593.95 | 3656.88 | 0.221692 | 5.21578 | 2(Loss) | true |
| simdjson (ondemand) | 338.854 | 0.178527 | 540.437ms | 1811 | 4890 | 404883 | 5096.89 | 0.387497 | 7.26625 | 3(Loss) | true |
