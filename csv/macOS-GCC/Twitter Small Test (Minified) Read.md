
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2024.67 | 1.42856 | 148.243ms | 2889 | 640 | 241862 | 1360.8 | 2.63309 | 1(Win) | true |
| Glaze | 1751.31 | 0.891976 | 170.696ms | 2889 | 1280 | 252048 | 1573.2 | 0.177665 | 2(Loss) | true |
| Jsonifier (two-stage) | 1557.96 | 0.605655 | 187.416ms | 2889 | 4890 | 560971 | 1768.44 | 1.26505 | 3(Loss) | true |
| simdjson (reflection) | 1144.46 | 0.627034 | 261.12ms | 2889 | 1280 | 291668 | 2407.4 | 0.223806 | 4(Loss) | true |
| simdjson (ondemand) | 855.854 | 1.83278 | 312.304ms | 2889 | 320 | 1.11395e+06 | 3219.2 | 4.46521 | 5(Loss) | true |
