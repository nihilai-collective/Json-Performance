
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1184.24 | 0.0854191 | 8520.05ms | 409725 | 160 | 1.27096e+07 | 329953 | 0.216772 | 2.0903 | 1(Win) | true |
| simdjson (ondemand) | 1067.22 | 0.0844547 | 9450.18ms | 409725 | 160 | 1.52982e+07 | 366131 | 0.184946 | 2.31961 | 2(Loss) | true |
