
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1411.42 | 0.112132 | 8119ms | 108313 | 640 | 4.31009e+06 | 73185.6 | 0.0360597 | 1(Win) | true |
| simdjson (ondemand) | 1230.46 | 0.174757 | 8947.57ms | 108313 | 80 | 1.72181e+06 | 83948.8 | 0.252216 | 2(Loss) | true |
