
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1227.94 | 0.177366 | 4337.18ms | 56369 | 4890 | 2.94832e+07 | 43778.6 | 0.328382 | 1(Win) | true |
| simdjson (ondemand) | 752.885 | 0.370338 | 6893.09ms | 56369 | 1280 | 8.95012e+07 | 71402.2 | 1.33376 | 2(Loss) | true |
