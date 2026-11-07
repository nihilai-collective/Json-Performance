
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16711.4 | 0.0658531 | 327.34ms | 56369 | 30 | 134.626 | 3216.83 | 0.0735172 | 0.146966 | 1(Win) | true |
| Glaze | 3819.24 | 0.0975614 | 1408.3ms | 56369 | 2560 | 482751 | 14075.5 | 0.0646345 | 0.647081 | 2(Loss) | true |
