
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3237.79 | 0.0808677 | 3524.77ms | 108313 | 4890 | 3.2548e+06 | 31903.1 | 0.0607845 | 1(Win) | true |
| Jsonifier (two-stage) | 1916.89 | 0.0933491 | 5668.61ms | 108313 | 2560 | 6.47777e+06 | 53886.8 | 0.0368403 | 2(Loss) | true |
| Glaze | 1671.64 | 0.165885 | 6455.62ms | 108313 | 640 | 6.72467e+06 | 61792.8 | 0.031072 | 3(Loss) | true |
| simdjson (ondemand) | 704.929 | 0.0785917 | 7627.66ms | 108313 | 2560 | 3.39519e+07 | 146533 | 0.0388817 | 4(Loss) | true |
