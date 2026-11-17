
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6001.18 | 0.268274 | 7571.81ms | 461466 | 1280 | 4.95419e+07 | 73333.6 | 2.9328 | 1(Win) | true |
| simdjson (stage-1) | 5486.73 | 0.900455 | 8545.74ms | 461466 | 640 | 3.33854e+08 | 80209.6 | 1.14131 | 2(Loss) | true |
