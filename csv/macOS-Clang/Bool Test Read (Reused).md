
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1292.56 | 0.570932 | 74.0777ms | 905 | 40 | 581.333 | 667.725 | 0.344387 | 1(Win) | true |
| Jsonifier | 1230.46 | 0.372084 | 76.261ms | 905 | 640 | 4359.4 | 701.427 | 0.0737881 | 2(Loss) | true |
| simdjson (ondemand) | 281.946 | 0.24201 | 310.129ms | 905 | 30 | 1646.46 | 3061.13 | 0.136301 | 3(Loss) | true |
