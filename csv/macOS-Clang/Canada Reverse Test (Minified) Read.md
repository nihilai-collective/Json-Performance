
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 408.371 | 0.67843 | 6988.66ms | 2090234 | 80 | 8.77368e+10 | 4.88136e+06 | 0.432489 | 1(Win) | true |
| simdjson (ondemand) | 354.412 | 0.683203 | 8132.82ms | 2090234 | 40 | 5.90653e+10 | 5.62453e+06 | 1.15058 | 2(Loss) | true |
