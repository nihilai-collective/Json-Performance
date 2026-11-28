
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1405.23 | 0.0754512 | 92.5113ms | 1313 | 2560 | 1157.2 | 891.083 | 0.0039455 | 1(Win) | true |
| Glaze | 821.098 | 0.309602 | 160.903ms | 1313 | 30 | 668.759 | 1525 | 0.0875082 | 2(Loss) | true |
| simdjson (ondemand) | 303.791 | 0.0668995 | 430.879ms | 1313 | 40 | 304.148 | 4121.82 | 0.157743 | 3(Loss) | true |
