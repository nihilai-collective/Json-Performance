
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1129.71 | 0.126615 | 147.524ms | 1691 | 640 | 2090.77 | 1427.5 | 0.197412 | 2.14712 | 1(Win) | true |
| Jsonifier | 994.704 | 0.341627 | 167.912ms | 1691 | 80 | 2454.11 | 1621.25 | 0.384025 | 2.44213 | 2(Loss) | true |
| Jsonifier (two-stage) | 897.931 | 0.471083 | 192.173ms | 1691 | 2560 | 183247 | 1795.98 | 0.0805398 | 2.71283 | 3(Loss) | true |
| simdjson (ondemand) | 602.724 | 0.236067 | 266.291ms | 1691 | 160 | 6383.25 | 2675.62 | 0.302748 | 4.06629 | 4(Loss) | true |
