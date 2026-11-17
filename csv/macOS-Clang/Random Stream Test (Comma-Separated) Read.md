
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1017.58 | 0.445397 | 6991.64ms | 4506446 | 30 | 1.06157e+10 | 4.22345e+06 | 0.032082 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 610.468 | 0.220888 | 5374.07ms | 4506446 | 40 | 9.67272e+09 | 7.03998e+06 | 8.53117 | -(Loss) | false |
