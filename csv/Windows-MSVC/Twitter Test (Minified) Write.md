
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4757.68 | 0.0958754 | 9646.58ms | 475954 | 4890 | 4.09131e+07 | 95404.7 | 0.446988 | 0.520138 | 1(Win) | true |
| Jsonifier | 3768.58 | 0.301166 | 6234.72ms | 475954 | 1280 | 1.68421e+08 | 120445 | 2.06576 | 0.65636 | 2(Loss) | true |
