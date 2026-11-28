
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 873 | 0.165896 | 210.691ms | 1811 | 160 | 1723.46 | 1978.36 | 0.360495 | 1(Win) | true |
| Glaze | 770.352 | 0.0955009 | 219.76ms | 1811 | 160 | 733.49 | 2241.97 | 0.103532 | 2(Loss) | true |
| simdjson (ondemand) | 284.171 | 0.185196 | 641.127ms | 1811 | 30 | 3800.7 | 6077.7 | 0.0476927 | 3(Loss) | true |
