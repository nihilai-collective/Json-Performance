
----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12813.7 | 1.92632 | 38.4251ms | 4857 | 4890 | 237113 | 361.489 | 2.9296 | 1(Win) | true |
| simdjson (reflection) | 10284.6 | 1.58756 | 47.87ms | 4857 | 4890 | 249995 | 450.382 | 1.44814 | 2(Loss) | true |
| Glaze | 2956.34 | 0.909038 | 162.083ms | 4857 | 1280 | 259657 | 1566.8 | 0.457433 | 3(Loss) | true |
