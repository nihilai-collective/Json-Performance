
----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15544.9 | 0.0695054 | 348.889ms | 56369 | 40 | 231.102 | 3458.22 | 0.0672763 | 0.158022 | 1(Win) | true |
| simdjson (reflection) | 13809.4 | 0.0933307 | 393.627ms | 56369 | 30 | 396.006 | 3892.83 | 0.0676915 | 0.17801 | 2(Loss) | true |
| Glaze | 5961.66 | 0.110272 | 918.543ms | 56369 | 30 | 2966.19 | 9017.23 | 0.111882 | 0.414029 | 3(Loss) | true |
