
----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11758.8 | 0.10231 | 831.314ms | 94653 | 30 | 1850.57 | 7676.67 | 0.432339 | 0.209897 | 1(Win) | true |
| Glaze | 4966.01 | 0.371146 | 1861.96ms | 94653 | 640 | 2.91287e+06 | 18177.2 | 0.220541 | 0.497736 | 2(Loss) | true |
