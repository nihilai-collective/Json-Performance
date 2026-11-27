
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1880.46 | 0.15983 | 151.1ms | 2889 | 4890 | 26815.7 | 1465.15 | 0.267126 | 1.59516 | 1(Win) | true |
| Glaze | 1670.43 | 0.240391 | 171.651ms | 2889 | 160 | 2515.33 | 1649.38 | 0.64006 | 1.7999 | 2(Loss) | true |
| simdjson (ondemand) | 1406.59 | 0.20439 | 198.126ms | 2889 | 160 | 2564.47 | 1958.75 | 0.191816 | 2.14221 | 3(Loss) | true |
| Jsonifier (two-stage) | 1354.31 | 0.185151 | 210.839ms | 2889 | 160 | 2270.05 | 2034.38 | 0.0307314 | 2.22569 | 4(Loss) | true |
