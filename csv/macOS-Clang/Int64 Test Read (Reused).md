
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1449.17 | 0.428741 | 89.7694ms | 1313 | 1280 | 17566.6 | 864.061 | 0.0171761 | 1(Win) | true |
| Glaze | 860.4 | 0.110881 | 150.271ms | 1313 | 320 | 833.279 | 1455.34 | 0.0633844 | 2(Loss) | true |
| simdjson (ondemand) | 328.525 | 0.0876227 | 389.031ms | 1313 | 40 | 446.154 | 3811.5 | 0.0113704 | 3(Loss) | true |
