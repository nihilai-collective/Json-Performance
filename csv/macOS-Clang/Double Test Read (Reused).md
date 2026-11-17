
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 311.226 | 0.247904 | 547.93ms | 1811 | 4890 | 925471 | 5549.36 | 2.82852 | 1(Win) | true |
| simdjson (ondemand) | 177.34 | 0.657244 | 934.469ms | 1811 | 320 | 1.31108e+06 | 9738.96 | 0.245172 | 2(Loss) | true |
