
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 863.709 | 1.33887 | 7756.29ms | 4506446 | 40 | 1.7753e+11 | 4.97584e+06 | 0.324324 | 1(Win) | true |
| simdjson (ondemand) | 516.714 | 0.52161 | 5680.69ms | 4506446 | 40 | 7.5287e+10 | 8.31733e+06 | 3.89823 | 2(Loss) | true |
