
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1668.11 | 0.43121 | 150.037ms | 2158 | 80 | 2264.24 | 1233.75 | 0.30303 | 1.45689 | 1(Win) | true |
| Jsonifier (two-stage) | 1476.61 | 0.368682 | 186.747ms | 2158 | 80 | 2112.34 | 1393.75 | 0.996377 | 1.64283 | 2(Loss) | true |
| Jsonifier | 1205.29 | 0.439239 | 216.769ms | 2158 | 40 | 2250 | 1707.5 | 0.0488281 | 2.02042 | 3(Loss) | true |
| simdjson (ondemand) | 1054.26 | 0.46462 | 214.277ms | 2158 | 2560 | 210593 | 1952.11 | 0.232661 | 2.31544 | 4(Loss) | true |
