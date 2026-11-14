
----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 718.13 | 0.310835 | 7622.43ms | 409725 | 160 | 4.57677e+08 | 544114 | 1.84465 | 1(Win) | true |
| simdjson (ondemand) | 379.191 | 0.0713388 | 6990.32ms | 409725 | 160 | 8.64652e+07 | 1.03047e+06 | 0.0427173 | 2(Loss) | true |
