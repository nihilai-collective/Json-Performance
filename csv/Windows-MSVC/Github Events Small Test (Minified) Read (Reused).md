
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1419.29 | 0.476 | 137.891ms | 1691 | 80 | 2340.19 | 1136.25 | 0.10989 | 1.69954 | 1(Win) | true |
| Jsonifier | 1381.76 | 0.57496 | 159.172ms | 1691 | 2560 | 115276 | 1167.11 | 0.0334806 | 1.75036 | 2(Loss) | true |
| Jsonifier (two-stage) | 1215.96 | 0.295127 | 172.021ms | 1691 | 160 | 2451.26 | 1326.25 | 0.188147 | 2.00304 | 3(Loss) | true |
| simdjson (ondemand) | 846.542 | 0.262467 | 215.03ms | 1691 | 80 | 2000 | 1905 | 0.131406 | 2.87456 | 4(Loss) | true |
