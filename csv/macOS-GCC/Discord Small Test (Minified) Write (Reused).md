
----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11434.3 | 1.79597 | 44.1452ms | 4857 | 4890 | 258837 | 405.098 | 0.929873 | 1(Win) | true |
| simdjson (reflection) | 9039.81 | 2.04316 | 55.69ms | 4857 | 2560 | 280583 | 512.4 | 0.543478 | 2(Loss) | true |
| Glaze | 2290.12 | 0.629696 | 196.206ms | 4857 | 2560 | 415261 | 2022.6 | 1.89173 | 3(Loss) | true |
