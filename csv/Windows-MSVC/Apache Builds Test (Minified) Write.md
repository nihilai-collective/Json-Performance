
----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11465 | 0.120775 | 832.452ms | 94653 | 30 | 2712.64 | 7873.33 | 0.212134 | 0.214822 | 1(Win) | true |
| Glaze | 4502.15 | 0.0472484 | 2044.31ms | 94653 | 40 | 3589.74 | 20050 | 0.333611 | 0.549182 | 2(Loss) | true |
