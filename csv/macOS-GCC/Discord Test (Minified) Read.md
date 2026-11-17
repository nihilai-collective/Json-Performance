
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 957.783 | 0.412488 | 5583.45ms | 56369 | 2560 | 1.37218e+08 | 56127.2 | 1.93751 | 1(Win) | true |
| simdjson (ondemand) | 714.255 | 1.44188 | 7099.37ms | 56369 | 30 | 3.53307e+07 | 75264 | 1.20482 | 2(Loss) | true |
