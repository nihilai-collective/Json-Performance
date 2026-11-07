
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10580.5 | 0.106159 | 4226.79ms | 466906 | 1280 | 2.55489e+06 | 42084.6 | 0.0763207 | 0.233838 | 1(Win) | true |
| Jsonifier (two-stage) | 10533.9 | 0.0814777 | 4231.61ms | 466906 | 2560 | 3.0367e+06 | 42271 | 0.0260488 | 0.234851 | 2(Loss) | true |
| simdjson (ondemand) | 8346.43 | 0.093088 | 5422.78ms | 466906 | 2560 | 6.31372e+06 | 53349.3 | 0.0474963 | 0.296466 | 3(Loss) | true |
| Glaze | 3429.03 | 0.0759568 | 6722.57ms | 466906 | 640 | 6.22629e+06 | 129855 | 0.30934 | 0.721871 | 4(Loss) | true |
