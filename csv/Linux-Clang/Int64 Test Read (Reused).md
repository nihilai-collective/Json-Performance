
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1662.5 | 0.0343521 | 79.7752ms | 1313 | 640 | 42.8443 | 753.188 | 0.158656 | 1.43814 | 1(Win) | true |
| Glaze | 993.168 | 0.046896 | 129.886ms | 1313 | 80 | 27.9669 | 1260.79 | 0.0287436 | 2.44197 | 2(Loss) | true |
| simdjson (ondemand) | 367.383 | 0.123235 | 344.197ms | 1313 | 4890 | 86271.9 | 3408.37 | 0.0477511 | 6.68699 | 3(Loss) | true |
