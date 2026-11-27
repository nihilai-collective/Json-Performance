
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9450.57 | 4.66697 | 30.817ms | 2632 | 1280 | 196669 | 265.6 | 3.90738 | 1(Win) | true |
| simdjson (reflection) | 7759.11 | 2.87071 | 35.6989ms | 2632 | 2560 | 220784 | 323.5 | 0.949173 | 2(Loss) | true |
| Glaze | 3126.18 | 0.742461 | 83.5891ms | 2632 | 4890 | 173780 | 802.919 | 0.327203 | 3(Loss) | true |
