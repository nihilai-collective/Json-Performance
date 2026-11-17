
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 814.852 | 0.0323278 | 460.949ms | 3873 | 40 | 85.8917 | 4532.82 | 0.190284 | 3.02022 | 1(Win) | true |
| simdjson (ondemand) | 534.053 | 0.0835154 | 672.356ms | 3873 | 30 | 1000.88 | 6916.13 | 0.00144592 | 4.61751 | 2(Loss) | true |
