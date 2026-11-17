
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2870.54 | 0.144162 | 3853.18ms | 108313 | 4890 | 1.31596e+07 | 35984.6 | 0.479009 | 1(Win) | true |
| Jsonifier (two-stage) | 1862.87 | 0.387542 | 6127.96ms | 108313 | 80 | 3.69424e+06 | 55449.6 | 0.253281 | 2(Loss) | true |
| Glaze | 1500.74 | 0.222444 | 6802.99ms | 108313 | 2560 | 6.00105e+07 | 68829.4 | 0.819046 | 3(Loss) | true |
| simdjson (reflection) | 1318.51 | 0.521613 | 8890.48ms | 108313 | 40 | 6.67959e+06 | 78342.4 | 1.90458 | 4(Loss) | true |
| simdjson (ondemand) | 1090.39 | 0.152397 | 9575.14ms | 108313 | 4890 | 1.01919e+08 | 94732 | 0.448782 | 5(Loss) | true |
