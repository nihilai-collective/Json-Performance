
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 823.411 | 0.11919 | 221.446ms | 1811 | 40 | 250 | 2097.5 | 0.119048 | 3.6513 | 1(Win) | true |
| simdjson (stage-1) | 399.735 | 0.421615 | 451.517ms | 1811 | 160 | 53093.9 | 4320.62 | 0.101156 | 7.5647 | 2(Loss) | true |
