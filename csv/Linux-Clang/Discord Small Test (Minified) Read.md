
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2196.31 | 0.369306 | 213.188ms | 4857 | 640 | 38824.2 | 2108.99 | 0.179763 | 1.11308 | 1(Win) | true |
| Jsonifier (two-stage) | 1788.51 | 0.28981 | 262.494ms | 4857 | 2560 | 144218 | 2589.87 | 0.0848072 | 1.3685 | 2(Loss) | true |
| Glaze | 1593.98 | 0.257119 | 291.013ms | 4857 | 40 | 2233.05 | 2905.93 | 0.010038 | 1.53847 | 3(Loss) | true |
| simdjson (ondemand) | 796.28 | 0.203146 | 588.193ms | 4857 | 1280 | 178744 | 5817.05 | 0.181156 | 3.09503 | 4(Loss) | true |
