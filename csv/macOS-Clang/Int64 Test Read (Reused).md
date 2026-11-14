
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 614.441 | 0.427953 | 633.768ms | 3862 | 1280 | 842298 | 5994.21 | 0.256934 | 1(Win) | true |
| simdjson (ondemand) | 415.765 | 0.305314 | 882.767ms | 3862 | 2560 | 1.87267e+06 | 8858.59 | 4.36171 | 2(Loss) | true |
