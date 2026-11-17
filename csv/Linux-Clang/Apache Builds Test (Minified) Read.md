
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1363.3 | 0.0803134 | 6735.28ms | 94653 | 4890 | 1.38284e+07 | 66213.1 | 0.60906 | 1.81528 | 1(Win) | true |
| simdjson (ondemand) | 1204.35 | 0.0477079 | 7544.1ms | 94653 | 4890 | 6.25255e+06 | 74952 | 0.0699816 | 2.055 | 2(Loss) | true |
