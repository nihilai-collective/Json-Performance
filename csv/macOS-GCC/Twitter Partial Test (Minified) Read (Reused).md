
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4792.95 | 1.03884 | 5121.33ms | 466906 | 40 | 3.72574e+07 | 92902.4 | 0.202485 | 1(Win) | true |
| Jsonifier (two-stage) | 4378.54 | 0.779676 | 9782.37ms | 466906 | 320 | 2.01177e+08 | 101695 | 1.5985 | 2(Loss) | true |
| simdjson (reflection) | 4048.29 | 0.20411 | 6166.43ms | 466906 | 320 | 1.61285e+07 | 109991 | 0.27642 | 3(Loss) | true |
| simdjson (ondemand) | 3711.43 | 0.645372 | 6113.21ms | 466906 | 80 | 4.79609e+07 | 119974 | 0.0639727 | 4(Loss) | true |
| Glaze | 2132.05 | 0.455949 | 5051.71ms | 466906 | 640 | 5.80333e+08 | 208849 | 0.932946 | 5(Loss) | true |
