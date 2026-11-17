
----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11086.1 | 1.73478 | 47.3751ms | 4857 | 4890 | 256905 | 417.819 | 0.258004 | 1(Win) | true |
| simdjson (reflection) | 8431.01 | 2.56833 | 61.4812ms | 4857 | 1280 | 254852 | 549.4 | 0.918442 | 2(Loss) | true |
| Glaze | 2557.42 | 2.42184 | 204.305ms | 4857 | 80 | 153927 | 1811.2 | 0.711744 | 3(Loss) | true |
