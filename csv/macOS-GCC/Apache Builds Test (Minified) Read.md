
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1059.97 | 0.272428 | 9196.59ms | 94653 | 2560 | 1.37793e+08 | 85161.2 | 0.591777 | 1(Win) | true |
| Glaze | 975.956 | 0.674779 | 9295.19ms | 94653 | 320 | 1.24647e+08 | 92492 | 0.126985 | 2(Loss) | true |
| Jsonifier (two-stage) | 847.534 | 0.397647 | 5648.7ms | 94653 | 1280 | 2.29594e+08 | 106507 | 1.85804 | 3(Loss) | true |
| simdjson (reflection) | 823.602 | 0.539333 | 5841.33ms | 94653 | 320 | 1.11814e+08 | 109602 | 0.508344 | 4(Loss) | true |
| simdjson (ondemand) | 599.097 | 0.798617 | 7304.83ms | 94653 | 160 | 2.31671e+08 | 150674 | 2.99792 | 5(Loss) | true |
