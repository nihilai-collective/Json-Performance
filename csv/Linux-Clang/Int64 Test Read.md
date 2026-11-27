
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1465.16 | 0.141537 | 87.581ms | 1313 | 30 | 43.8954 | 854.633 | 0.234567 | 1.6343 | 1(Win) | true |
| Glaze | 931.132 | 0.051585 | 138.721ms | 1313 | 80 | 38.4986 | 1344.79 | 0.0921067 | 2.60757 | 2(Loss) | true |
| simdjson (ondemand) | 358.353 | 0.053577 | 369.824ms | 1313 | 40 | 140.192 | 3494.25 | 0.0767339 | 6.85588 | 3(Loss) | true |
