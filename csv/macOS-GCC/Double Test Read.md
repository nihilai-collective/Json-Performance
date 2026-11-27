
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 2411.4 | 0.933956 | 75.0431ms | 1811 | 4890 | 218806 | 716.224 | 0.635679 | 1(Win) | true |
| simdjson (stage-1) | 980.975 | 0.567402 | 178.177ms | 1811 | 2560 | 255472 | 1760.6 | 0.755408 | 2(Loss) | true |
