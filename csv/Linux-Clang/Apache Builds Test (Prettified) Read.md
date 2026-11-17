
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1793.11 | 0.152421 | 6749.1ms | 124597 | 640 | 6.52938e+06 | 66267.7 | 0.01122 | 1.38014 | 1(Win) | true |
| Jsonifier | 1678.55 | 0.209187 | 7204.21ms | 124597 | 160 | 3.50862e+06 | 70790.2 | 0.135895 | 1.47439 | 2(Loss) | true |
| Glaze | 1562.21 | 0.188738 | 7522ms | 124597 | 1280 | 2.63796e+07 | 76062.2 | 0.0971283 | 1.58423 | 3(Loss) | true |
| simdjson (ondemand) | 1356.23 | 0.129394 | 8884.99ms | 124597 | 1280 | 1.64508e+07 | 87614 | 0.176012 | 1.82492 | 4(Loss) | true |
