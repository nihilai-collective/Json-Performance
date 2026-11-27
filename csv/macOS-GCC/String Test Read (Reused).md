
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 852.434 | 0.48186 | 586.332ms | 4215 | 640 | 330443 | 4715.6 | 1.0824 | 1(Win) | true |
| simdjson (ondemand) | 672.658 | 0.21162 | 704.912ms | 4215 | 4890 | 782042 | 5975.9 | 0.565414 | 2(Loss) | true |
