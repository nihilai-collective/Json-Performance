
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 422.644 | 0.705637 | 411.102ms | 1811 | 320 | 266073 | 4086.43 | 2.82491 | 1(Win) | true |
| simdjson (ondemand) | 262.939 | 0.295389 | 683.464ms | 1811 | 2560 | 963730 | 6568.47 | 1.33874 | 2(Loss) | true |
