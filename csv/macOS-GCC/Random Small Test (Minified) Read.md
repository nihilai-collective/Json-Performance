
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1227.48 | 0.392946 | 402.506ms | 5094 | 2560 | 619144 | 3957.7 | 0.0328582 | 1(Win) | true |
| Jsonifier (two-stage) | 924.984 | 1.11233 | 579.038ms | 5094 | 320 | 1.09211e+06 | 5252 | 3.51264 | 2(Loss) | true |
| Glaze | 765.355 | 0.273981 | 648.856ms | 5094 | 1280 | 387116 | 6347.4 | 0.160954 | 3(Loss) | true |
| simdjson (reflection) | 714.302 | 2.8115 | 714.736ms | 5094 | 30 | 1.09686e+06 | 6801.07 | 1.48331 | 4(Loss) | true |
| simdjson (ondemand) | 588.622 | 0.605706 | 840.388ms | 5094 | 640 | 1.59937e+06 | 8253.2 | 1.00352 | 5(Loss) | true |
