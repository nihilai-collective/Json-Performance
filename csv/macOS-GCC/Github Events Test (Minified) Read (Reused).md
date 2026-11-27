
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1469.99 | 0.257975 | 4064.1ms | 53331 | 2560 | 2.03951e+07 | 34599.1 | 1.18326 | 1(Win) | true |
| simdjson (ondemand) | 948.33 | 0.0750499 | 6129.88ms | 53331 | 4890 | 7.92226e+06 | 53631.5 | 0.0456075 | 2(Loss) | true |
