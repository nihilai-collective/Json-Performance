
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2401.92 | 0.12922 | 90.2888ms | 2158 | 320 | 392.276 | 856.825 | 0.00948178 | 0.997873 | 1(Win) | true |
| Glaze | 1923.45 | 0.209392 | 111.051ms | 2158 | 30 | 150.585 | 1069.97 | 0.211397 | 1.25419 | 2(Loss) | true |
| simdjson (ondemand) | 1726.46 | 0.516688 | 124.401ms | 2158 | 1280 | 48557.3 | 1192.05 | 0.0220913 | 1.40031 | 3(Loss) | true |
| Jsonifier | 1511.28 | 0.11395 | 137.223ms | 2158 | 80 | 192.632 | 1361.78 | 0.150313 | 1.60509 | 4(Loss) | true |
