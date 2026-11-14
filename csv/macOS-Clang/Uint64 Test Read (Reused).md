
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 619.766 | 1.88725 | 627.753ms | 3873 | 30 | 379507 | 5959.63 | 0.0497546 | 1(Win) | true |
| simdjson (ondemand) | 434.082 | 0.188348 | 865.21ms | 3873 | 4890 | 1.25598e+06 | 8508.95 | 0.836643 | 2(Loss) | true |
