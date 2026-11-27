
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1763.15 | 0.281182 | 266.122ms | 4857 | 4890 | 266834 | 2627.11 | 0.0564967 | 1(Win) | true |
| Jsonifier (two-stage) | 1376.44 | 0.351018 | 344.177ms | 4857 | 2560 | 357207 | 3365.2 | 0.260818 | 2(Loss) | true |
| Glaze | 1296.97 | 0.443529 | 359.584ms | 4857 | 1280 | 321167 | 3571.4 | 0.128967 | 3(Loss) | true |
| simdjson (reflection) | 1078.29 | 0.181132 | 434.496ms | 4857 | 4890 | 296048 | 4295.67 | 0.0924932 | 4(Loss) | true |
| simdjson (ondemand) | 903.205 | 0.373564 | 520.577ms | 4857 | 640 | 234895 | 5128.4 | 0.352223 | 5(Loss) | true |
