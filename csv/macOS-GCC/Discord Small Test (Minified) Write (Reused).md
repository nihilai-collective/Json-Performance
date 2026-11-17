
----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12989.3 | 3.9536 | 41.4131ms | 4857 | 1280 | 254424 | 356.6 | 0.281215 | 1(Win) | true |
| simdjson (reflection) | 7661.79 | 1.54415 | 61.577ms | 4857 | 4890 | 426149 | 604.558 | 2.25945 | 2(Loss) | true |
| Glaze | 2731.94 | 0.564075 | 181.81ms | 4857 | 2560 | 234158 | 1695.5 | 0.00589762 | 3(Loss) | true |
