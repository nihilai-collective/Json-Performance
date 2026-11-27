
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2481.76 | 0.11905 | 149.462ms | 3808 | 4890 | 14840.2 | 1463.32 | 0.0245453 | 1(Win) | true |
| Jsonifier (two-stage) | 2289.91 | 0.0321023 | 162.523ms | 3808 | 1280 | 331.772 | 1585.91 | 0.0015764 | 2(Loss) | true |
| Glaze | 2044.21 | 0.154185 | 183.819ms | 3808 | 2560 | 19207.4 | 1776.52 | 0.681519 | 3(Loss) | true |
| simdjson (ondemand) | 1095.14 | 0.146018 | 337.091ms | 3808 | 80 | 1875.65 | 3316.09 | 0.111829 | 4(Loss) | true |
