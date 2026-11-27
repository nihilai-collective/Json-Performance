
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1391.11 | 0.347712 | 581.149ms | 8051 | 160 | 58930.4 | 5519.38 | 0.011325 | 2.17892 | 1(Win) | true |
| Jsonifier (two-stage) | 1254.5 | 0.434137 | 615.293ms | 8051 | 4890 | 3.45236e+06 | 6120.37 | 0.186344 | 2.41521 | 2(Loss) | true |
| Glaze | 953.793 | 0.183392 | 847.711ms | 8051 | 40 | 8717.95 | 8050 | 0.374065 | 3.18193 | 3(Loss) | true |
| simdjson (ondemand) | 851.946 | 0.137535 | 921.056ms | 8051 | 640 | 98329.4 | 9012.34 | 0.196296 | 3.55923 | 4(Loss) | true |
