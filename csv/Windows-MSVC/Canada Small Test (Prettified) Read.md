
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1302.7 | 0.244488 | 875.051ms | 11579 | 30 | 12885.1 | 8476.67 | 0.0785855 | 2.32843 | 1(Win) | true |
| Jsonifier | 1247 | 0.15708 | 902.682ms | 11579 | 320 | 61915.3 | 8855.31 | 0.0529624 | 2.43122 | 2(Loss) | true |
| simdjson (ondemand) | 808.093 | 0.369379 | 1382.62ms | 11579 | 80 | 203823 | 13665 | 0.0182983 | 3.75691 | 3(Loss) | true |
| Glaze | 712.224 | 0.23204 | 1577.61ms | 11579 | 160 | 207088 | 15504.4 | 0.108959 | 4.26021 | 4(Loss) | true |
