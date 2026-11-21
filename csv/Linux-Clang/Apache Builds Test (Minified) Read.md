
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1722.39 | 0.209958 | 5331.89ms | 94653 | 320 | 3.87456e+06 | 52408.8 | 0.261603 | 1.4367 | 1(Win) | true |
| Jsonifier (two-stage) | 1538.34 | 0.137966 | 5977.9ms | 94653 | 640 | 4.1946e+06 | 58679.1 | 0.054521 | 1.60868 | 2(Loss) | true |
| Glaze | 1440.57 | 0.0889979 | 6237.83ms | 94653 | 1280 | 3.98079e+06 | 62661.4 | 0.492388 | 1.71788 | 3(Loss) | true |
| simdjson (ondemand) | 1137.7 | 0.204994 | 8285.17ms | 94653 | 160 | 4.23267e+06 | 79342.4 | 0.0417117 | 2.17545 | 4(Loss) | true |
