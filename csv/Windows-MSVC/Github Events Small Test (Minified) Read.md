
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1185.78 | 0.66891 | 141.315ms | 1691 | 30 | 2482.76 | 1360 | 1.21065 | 2.5399 | 1(Win) | true |
| Glaze STATISTICAL TIE | 907.69 | 0.517929 | 146.771ms | 1691 | 30 | 2540.23 | 1776.67 | 1.91205 | 3.29156 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 897.17 | 0.31417 | 167.877ms | 1691 | 40 | 1275.64 | 1797.5 | 1.23626 | 3.32784 | 2(Tie) | true |
| simdjson (ondemand) | 759.496 | 0.433369 | 225.341ms | 1691 | 30 | 2540.23 | 2123.33 | 0.791139 | 3.98253 | 4(Loss) | true |
