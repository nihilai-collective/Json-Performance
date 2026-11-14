
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 457.678 | 0.0528408 | 6643.07ms | 2090234 | 40 | 2.11869e+08 | 4.35547e+06 | 0.141948 | 1(Win) | true |
| Jsonifier (generic) | 431.84 | 0.643231 | 6949.61ms | 2090234 | 80 | 7.05289e+10 | 4.61606e+06 | 0.592109 | 2(Loss) | true |
