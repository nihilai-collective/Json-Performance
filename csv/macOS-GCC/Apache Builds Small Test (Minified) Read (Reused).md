
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2166.84 | 3.47149 | 175.775ms | 2632 | 80 | 129371 | 1158.4 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1819.95 | 2.81704 | 201.998ms | 2632 | 160 | 241525 | 1379.2 | 0.461894 | 2(Loss) | true |
| Glaze | 1697.45 | 0.509087 | 174.367ms | 2632 | 4890 | 277120 | 1478.73 | 1.23415 | 3(Loss) | true |
| simdjson (reflection) | 1157.03 | 0.784375 | 251.704ms | 2632 | 1280 | 370627 | 2169.4 | 0.472397 | 4(Loss) | true |
| simdjson (ondemand) | 1103.38 | 0.425362 | 280.316ms | 2632 | 2560 | 239708 | 2274.9 | 1.19441 | 5(Loss) | true |
