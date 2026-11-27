
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 581.595 | 0.356976 | 290.268ms | 1811 | 1280 | 143841 | 2969.6 | 0.270124 | 1(Win) | true |
| simdjson (ondemand) | 308.5 | 0.789445 | 617.592ms | 1811 | 160 | 312530 | 5598.4 | 0.878187 | 2(Loss) | true |
