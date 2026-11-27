
----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1831.29 | 0.0913878 | 3089.54ms | 56369 | 2560 | 1.8424e+06 | 29355.1 | 0.0777901 | 1(Win) | true |
| simdjson (ondemand) | 1006.63 | 0.0545471 | 5508.82ms | 56369 | 4890 | 4.14946e+06 | 53403.5 | 0.0304481 | 2(Loss) | true |
