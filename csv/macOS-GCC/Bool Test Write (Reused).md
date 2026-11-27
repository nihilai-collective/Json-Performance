
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2745.15 | 5.86901 | 44.6039ms | 905 | 640 | 217909 | 314.4 | 5.08021 | -(Win) | false |
| simdjson (reflection) | 2441.3 | 1.96681 | 47.1278ms | 905 | 4890 | 236423 | 353.531 | 0.577891 | 2(Loss) | true |
| Glaze | 706.05 | 2.79119 | 132.404ms | 905 | 160 | 186262 | 1222.4 | 0.791557 | 3(Loss) | true |
