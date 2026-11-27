
----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17621.6 | 0.110225 | 2571.54ms | 475954 | 2560 | 2.06368e+06 | 25758.5 | 0.105253 | 0.140344 | 1(Win) | true |
| Glaze | 5869.04 | 0.367071 | 7732.6ms | 475954 | 40 | 3.22372e+06 | 77338.9 | 0.193874 | 0.421624 | 2(Loss) | true |
