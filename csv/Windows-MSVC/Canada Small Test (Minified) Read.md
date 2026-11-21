
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 557.984 | 0.179055 | 814.078ms | 4630 | 30 | 6022.99 | 7913.33 | 0.21106 | 4.41381 | 1(Win) | true |
| Jsonifier (two-stage) | 529.755 | 0.145995 | 881.343ms | 4630 | 40 | 5923.08 | 8335 | 0.10008 | 4.66156 | 2(Loss) | true |
| simdjson (ondemand) | 179.638 | 0.157701 | 2555.86ms | 4630 | 40 | 60102.6 | 24580 | 0.189496 | 13.7599 | 3(Loss) | true |
| Glaze | 175.639 | 0.137763 | 2588.87ms | 4630 | 2560 | 3.07064e+06 | 25139.7 | 0.0639026 | 14.0791 | 4(Loss) | true |
