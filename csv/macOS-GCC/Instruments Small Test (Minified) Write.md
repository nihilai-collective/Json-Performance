
----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13316.7 | 2.06375 | 36.2322ms | 4669 | 4890 | 232851 | 334.371 | 0.95659 | 1(Win) | true |
| simdjson (reflection) | 7593.29 | 4.78817 | 65.334ms | 4669 | 320 | 252277 | 586.4 | 2.26667 | 2(Loss) | true |
| Glaze | 1652.15 | 0.47887 | 255.701ms | 4669 | 2560 | 426407 | 2695.1 | 2.99115 | 3(Loss) | true |
