
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2991.28 | 0.224183 | 145.885ms | 3862 | 80 | 609.544 | 1231.28 | 0.342277 | 1(Win) | true |
| Glaze | 487.95 | 0.372093 | 770.3ms | 3862 | 2560 | 2.01938e+06 | 7548.09 | 0.615698 | 2(Loss) | true |
