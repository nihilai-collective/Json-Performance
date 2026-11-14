
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2845.18 | 0.100915 | 134.131ms | 3873 | 160 | 274.606 | 1298.19 | 0.0597343 | 1(Win) | true |
| Glaze | 1471.87 | 0.173857 | 255.383ms | 3873 | 40 | 761.382 | 2509.45 | 0.157653 | 2(Loss) | true |
| Jsonifier (two-stage) | 896.333 | 0.148844 | 415.254ms | 3873 | 30 | 1128.6 | 4120.77 | 0.336985 | 3(Loss) | true |
| simdjson (ondemand) | 474.109 | 0.136243 | 793.893ms | 3873 | 40 | 4506.4 | 7790.57 | 0.0507835 | 4(Loss) | true |
