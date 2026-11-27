
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 787.683 | 0.323722 | 7216.59ms | 461466 | 80 | 2.61705e+08 | 558712 | 2.10306 | 3.1429 | 1(Win) | true |
| Jsonifier (two-stage) | 686.544 | 0.231935 | 8355.47ms | 461466 | 160 | 3.53667e+08 | 641020 | 0.978245 | 3.60595 | 2(Loss) | true |
| Glaze | 601.651 | 0.200716 | 9425.14ms | 461466 | 80 | 1.72443e+08 | 731468 | 0.421678 | 4.11475 | 3(Loss) | true |
| simdjson (ondemand) | 495.314 | 0.257387 | 5767.17ms | 461466 | 30 | 1.56896e+08 | 888503 | 0.0431251 | 4.99829 | 4(Loss) | true |
