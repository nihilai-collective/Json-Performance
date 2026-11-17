
----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9371.26 | 2.95753 | 23.5169ms | 1996 | 4890 | 176479 | 203.125 | 0.96307 | 1(Win) | true |
| simdjson (reflection) | 8120.88 | 3.65519 | 25.769ms | 1996 | 2560 | 187920 | 234.4 | 0.509338 | 2(Loss) | true |
| Glaze | 2487.63 | 2.23484 | 76.1321ms | 1996 | 640 | 187165 | 765.2 | 0.468262 | 3(Loss) | true |
