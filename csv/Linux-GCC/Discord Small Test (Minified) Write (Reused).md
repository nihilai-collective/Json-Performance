
----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12081.9 | 0.0789227 | 40.5151ms | 4857 | 640 | 58.5934 | 383.383 | 0.25002 | 0.189973 | 1(Win) | true |
| simdjson (reflection) | 9307.71 | 0.0545037 | 63.2594ms | 4857 | 640 | 47.085 | 497.652 | 0.0505244 | 0.250746 | 2(Loss) | true |
| Glaze | 3895.26 | 0.211836 | 121.863ms | 4857 | 80 | 507.639 | 1189.14 | 0.220181 | 0.620218 | 3(Loss) | true |
