
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1540.54 | 0.306535 | 756.27ms | 11579 | 320 | 154492 | 7168 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1426.32 | 0.119296 | 782.517ms | 11579 | 4890 | 417128 | 7742.04 | 0.0224385 | 2(Loss) | true |
| simdjson (reflection) | 1139.81 | 0.23965 | 925.101ms | 11579 | 4890 | 2.63599e+06 | 9688.11 | 1.05088 | 3(Loss) | true |
| simdjson (ondemand) | 1114.6 | 0.165588 | 1028.93ms | 11579 | 320 | 86121.3 | 9907.2 | 0.0484262 | 4(Loss) | true |
| Glaze | 1093.58 | 0.0961365 | 1020.78ms | 11579 | 2560 | 241247 | 10097.7 | 0.03267 | 5(Loss) | true |
