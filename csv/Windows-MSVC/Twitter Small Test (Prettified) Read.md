
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1695.15 | 0.136427 | 217.554ms | 3808 | 1280 | 10934.3 | 2142.34 | 0.00729395 | 1.77749 | 1(Win) | true |
| simdjson (ondemand) | 1658.35 | 0.103261 | 221.701ms | 3808 | 4890 | 25004.9 | 2189.88 | 0.306121 | 1.81845 | 2(Loss) | true |
| Jsonifier (two-stage) | 1633.87 | 0.10078 | 225.158ms | 3808 | 2560 | 12845.4 | 2222.7 | 0.0368926 | 1.84432 | 3(Loss) | true |
| Jsonifier | 1524.78 | 0.139816 | 240.591ms | 3808 | 2560 | 28387.8 | 2381.72 | 0.0689316 | 1.97473 | 4(Loss) | true |
