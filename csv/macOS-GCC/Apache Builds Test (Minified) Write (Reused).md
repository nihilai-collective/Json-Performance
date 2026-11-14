
----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9578.54 | 1.84967 | 833.969ms | 94653 | 80 | 2.43079e+06 | 9424 | 0.372124 | 1(Win) | true |
| simdjson (reflection) | 8622.59 | 1.04448 | 1100.24ms | 94653 | 160 | 1.91299e+06 | 10468.8 | 1.69772 | 2(Loss) | true |
| Glaze | 5151.94 | 0.538238 | 1654.87ms | 94653 | 1280 | 1.13838e+07 | 17521.2 | 1.41227 | 3(Loss) | true |
