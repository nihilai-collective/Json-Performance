
----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15234.1 | 0.0786654 | 354.443ms | 56369 | 40 | 308.23 | 3528.78 | 0.176096 | 0.16133 | 1(Win) | true |
| Glaze | 3922.92 | 0.102467 | 1377.11ms | 56369 | 2560 | 504747 | 13703.5 | 0.24995 | 0.629926 | 2(Loss) | true |
