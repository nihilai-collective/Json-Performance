
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1180.89 | 0.548336 | 944.753ms | 11579 | 640 | 1.68266e+06 | 9351.09 | 0.0786121 | 1(Win) | true |
| Jsonifier (two-stage) | 1049.72 | 0.922299 | 989.51ms | 11579 | 160 | 1.50612e+06 | 10519.6 | 0.160455 | 2(Loss) | true |
| simdjson (ondemand) | 964.445 | 0.211949 | 1192.12ms | 11579 | 4890 | 2.87977e+06 | 11449.7 | 0.101947 | 3(Loss) | true |
| Glaze | 905.399 | 0.673977 | 1243.22ms | 11579 | 320 | 2.16223e+06 | 12196.4 | 0.179962 | 4(Loss) | true |
