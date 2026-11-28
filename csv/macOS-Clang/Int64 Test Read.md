
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1093.68 | 0.0534885 | 122.824ms | 1313 | 1280 | 480.046 | 1144.92 | 0.165471 | 1(Win) | true |
| Glaze | 614.082 | 0.196772 | 200.618ms | 1313 | 80 | 1287.94 | 2039.1 | 0.175016 | 2(Loss) | true |
| simdjson (ondemand) | 264.956 | 0.281984 | 463.372ms | 1313 | 4890 | 868445 | 4725.98 | 0.924034 | 3(Loss) | true |
