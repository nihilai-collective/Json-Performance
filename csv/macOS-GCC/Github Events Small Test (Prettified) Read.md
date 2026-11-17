
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1569.58 | 1.41118 | 142.757ms | 2158 | 640 | 219119 | 1311.2 | 3.47468 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1414.36 | 1.56397 | 156.497ms | 2158 | 2560 | 1.32581e+06 | 1455.1 | 1.4427 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1411.35 | 1.03906 | 153.402ms | 2158 | 1280 | 293850 | 1458.2 | 2.17209 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1321.11 | 0.690664 | 162.281ms | 2158 | 2560 | 296345 | 1557.8 | 0.319939 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1284.66 | 1.25053 | 166.222ms | 2158 | 640 | 256858 | 1602 | 0.273904 | 4(Tie) | true |
