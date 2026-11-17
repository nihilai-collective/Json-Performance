
----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19684 | 0.120484 | 25.0843ms | 4669 | 640 | 47.5398 | 226.209 | 0.166878 | 0.111371 | 1(Win) | true |
| simdjson (reflection) | 9576.74 | 0.114512 | 49.3831ms | 4669 | 160 | 45.356 | 464.95 | 0.0215031 | 0.243848 | 2(Loss) | true |
| Glaze | 2196.95 | 0.141756 | 210.506ms | 4669 | 80 | 660.361 | 2026.76 | 0.120411 | 1.11244 | 3(Loss) | true |
