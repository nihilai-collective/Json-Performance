
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 642.77 | 0.317015 | 564.957ms | 3862 | 1280 | 422360 | 5730.03 | 0.721169 | 1(Win) | true |
| simdjson (ondemand) | 456.964 | 0.0681333 | 900.692ms | 3862 | 80 | 2412.51 | 8059.91 | 0.0965269 | 2(Loss) | true |
