
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1375.04 | 0.212404 | 144.506ms | 1691 | 320 | 1985.8 | 1172.81 | 0.292242 | 1.75501 | 1(Win) | true |
| Jsonifier | 1218.76 | 0.567118 | 165.812ms | 1691 | 2560 | 144159 | 1323.2 | 0.462661 | 1.98794 | 2(Loss) | true |
| Jsonifier (two-stage) | 1092.1 | 0.839401 | 181.033ms | 1691 | 30 | 4609.2 | 1476.67 | 0 | 2.22172 | 3(Loss) | true |
| simdjson (ondemand) | 711.6 | 0.129226 | 252.082ms | 1691 | 320 | 2744.51 | 2266.25 | 0 | 3.43635 | 4(Loss) | true |
