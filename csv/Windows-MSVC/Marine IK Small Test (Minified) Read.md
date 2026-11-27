
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 510.548 | 0.136563 | 928.137ms | 4604 | 30 | 4137.93 | 8600 | 0.15528 | 5.9313 | 1(Win) | true |
| Jsonifier (two-stage) | 446.211 | 0.177692 | 1029.73ms | 4604 | 320 | 97830.7 | 9840 | 0.0826394 | 6.79739 | 2(Loss) | true |
| simdjson (ondemand) | 306.258 | 0.131595 | 1496.78ms | 4604 | 30 | 10678.2 | 14336.7 | 0.116117 | 9.90589 | 3(Loss) | true |
| Glaze | 270.531 | 0.0601812 | 1680ms | 4604 | 30 | 2862.07 | 16230 | 0.0410931 | 11.2227 | 4(Loss) | true |
