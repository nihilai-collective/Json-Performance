
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5070.33 | 6.9937 | 94.1489ms | 3862 | 80 | 206470 | 726.4 | 0.438596 | 1(Win) | true |
| simdjson (reflection) | 3079.51 | 1.8765 | 143.311ms | 3862 | 320 | 161179 | 1196 | 1.1502 | 2(Loss) | true |
| Glaze | 1977.37 | 0.730058 | 187.391ms | 3862 | 4890 | 904218 | 1862.62 | 1.41203 | 3(Loss) | true |
