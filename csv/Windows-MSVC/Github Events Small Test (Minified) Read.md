
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1165.96 | 0.241754 | 154.769ms | 1691 | 160 | 1788.92 | 1383.12 | 0.135379 | 2.07638 | 1(Win) | true |
| Glaze | 1054.34 | 0.45137 | 156.766ms | 1691 | 4890 | 233078 | 1529.55 | 0.116291 | 2.30326 | 2(Loss) | true |
| Jsonifier (two-stage) | 972.949 | 0.524161 | 172.607ms | 1691 | 40 | 3019.23 | 1657.5 | 0.150602 | 2.49694 | 3(Loss) | true |
| simdjson (ondemand) | 620.255 | 0.412351 | 266.465ms | 1691 | 30 | 3448.28 | 2600 | 0 | 3.9561 | 4(Loss) | true |
