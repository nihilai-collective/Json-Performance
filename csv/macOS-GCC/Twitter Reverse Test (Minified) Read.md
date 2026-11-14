
----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 631.711 | 0.144265 | 5082.61ms | 264040 | 160 | 5.2911e+07 | 398613 | 0.0349333 | 1(Win) | true |
| simdjson (ondemand) | 283.668 | 0.0987232 | 5648.65ms | 264040 | 80 | 6.14395e+07 | 887686 | 0.0475617 | 2(Loss) | true |
