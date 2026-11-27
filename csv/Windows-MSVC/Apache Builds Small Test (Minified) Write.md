
----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8410.71 | 0.479708 | 34.1648ms | 2632 | 320 | 655.858 | 298.438 | 0.104822 | 0.2679 | 1(Win) | true |
| Glaze | 3325.72 | 0.382124 | 79.4443ms | 2632 | 4890 | 40673.9 | 754.744 | 0.368916 | 0.716369 | 2(Loss) | true |
