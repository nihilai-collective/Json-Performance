
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1059.35 | 0.138378 | 122.014ms | 1313 | 160 | 428.056 | 1182.02 | 0.017452 | 1(Win) | true |
| Glaze | 717.665 | 0.0888579 | 179.811ms | 1313 | 320 | 769.182 | 1744.79 | 0.0141513 | 2(Loss) | true |
| simdjson (ondemand) | 295.228 | 0.180451 | 424.297ms | 1313 | 1280 | 74979.3 | 4241.38 | 0.0621868 | 3(Loss) | true |
