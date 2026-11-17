
----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10447.6 | 0.0505487 | 47.0453ms | 4857 | 1280 | 64.2883 | 443.354 | 0.0903159 | 0.222042 | 1(Win) | true |
| simdjson (reflection) | 7623.12 | 0.215282 | 63.3926ms | 4857 | 40 | 68.4455 | 607.625 | 0.26945 | 0.310058 | 2(Loss) | true |
| Glaze | 3406.21 | 0.316513 | 138.39ms | 4857 | 4890 | 90591.2 | 1359.87 | 0.297065 | 0.710629 | 3(Loss) | true |
