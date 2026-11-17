
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1627.22 | 0.410643 | 7638.92ms | 124597 | 80 | 7.19355e+06 | 73023.5 | 0.719204 | 1(Win) | true |
| Jsonifier (two-stage) | 1391.37 | 0.0889973 | 9135.88ms | 124597 | 640 | 3.69714e+06 | 85401.6 | 0.176461 | 2(Loss) | true |
| Glaze | 1362.56 | 0.10823 | 8944.47ms | 124597 | 640 | 5.70142e+06 | 87207.4 | 0.123335 | 3(Loss) | true |
| simdjson (ondemand) | 1113.65 | 0.116565 | 5608.12ms | 124597 | 1280 | 1.97997e+07 | 106698 | 0.439325 | 4(Loss) | true |
