
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1134.63 | 0.249492 | 145.689ms | 1691 | 4890 | 61489 | 1421.31 | 0.648486 | 2.13889 | 1(Win) | true |
| Jsonifier | 976.632 | 0.222627 | 178.182ms | 1691 | 320 | 4324.45 | 1651.25 | 0.15163 | 2.49647 | 2(Loss) | true |
| Jsonifier (two-stage) | 876.447 | 0.507445 | 189.988ms | 1691 | 40 | 3487.18 | 1840 | 0.180832 | 2.80557 | 3(Loss) | true |
| simdjson (ondemand) | 581.884 | 0.232556 | 290.04ms | 1691 | 4890 | 203132 | 2771.45 | 0.17249 | 4.2096 | 4(Loss) | true |
