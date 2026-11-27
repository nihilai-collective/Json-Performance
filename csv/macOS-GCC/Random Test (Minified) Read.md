
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 948.071 | 0.0737826 | 5424.07ms | 409725 | 320 | 2.95911e+07 | 412146 | 0.329859 | 1(Win) | true |
| simdjson (ondemand) | 605.612 | 0.0932097 | 8644.94ms | 409725 | 640 | 2.31472e+08 | 645206 | 0.193241 | 2(Loss) | true |
