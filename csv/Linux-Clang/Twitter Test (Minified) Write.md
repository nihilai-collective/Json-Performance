
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17059 | 0.188693 | 2704.75ms | 475954 | 1280 | 3.22663e+06 | 26608 | 0.0597706 | 0.144948 | 1(Win) | true |
| Glaze | 5785.13 | 0.27568 | 7844.23ms | 475954 | 160 | 7.48575e+06 | 78460.6 | 0.044716 | 0.427741 | 2(Loss) | true |
