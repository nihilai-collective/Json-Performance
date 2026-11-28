
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1976.05 | 0.114188 | 67.3711ms | 1313 | 40 | 20.9429 | 633.675 | 0.0539474 | 1.20188 | 1(Win) | true |
| simdjson (reflection) | 1106.2 | 0.0546986 | 116.787ms | 1313 | 80 | 30.6695 | 1131.96 | 0.0231952 | 2.18899 | 2(Loss) | true |
| Glaze | 1021.48 | 0.201649 | 124.96ms | 1313 | 4890 | 29878.9 | 1225.84 | 0.00211362 | 2.37284 | 3(Loss) | true |
| simdjson (ondemand) | 357.498 | 0.140939 | 353.372ms | 1313 | 4890 | 119166 | 3502.6 | 0.146058 | 6.87479 | 4(Loss) | true |
