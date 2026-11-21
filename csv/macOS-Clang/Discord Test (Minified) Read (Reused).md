
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2826.03 | 0.445807 | 2187.49ms | 56369 | 640 | 4.60258e+06 | 19022.3 | 0.502691 | 1(Win) | true |
| Glaze | 1906.44 | 0.19876 | 3594.08ms | 56369 | 40 | 125647 | 28197.9 | 0.145632 | 2(Loss) | true |
| Jsonifier (two-stage) | 1464.59 | 0.221361 | 4372.86ms | 56369 | 2560 | 1.69003e+07 | 36705 | 0.295118 | 3(Loss) | true |
| simdjson (ondemand) | 784.596 | 0.226297 | 7019.96ms | 56369 | 640 | 1.5386e+07 | 68516.4 | 0.0310081 | 4(Loss) | true |
