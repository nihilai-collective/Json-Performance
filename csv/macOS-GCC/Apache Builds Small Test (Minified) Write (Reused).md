
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10631.1 | 2.64011 | 28.6641ms | 2632 | 4890 | 190006 | 236.106 | 3.55133 | 1(Win) | true |
| simdjson (reflection) | 6943.49 | 3.01926 | 37.2099ms | 2632 | 2560 | 304970 | 361.5 | 0.696379 | 2(Loss) | true |
| Glaze | 3096.3 | 0.740091 | 84.5571ms | 2632 | 4890 | 176020 | 810.667 | 0.72896 | 3(Loss) | true |
