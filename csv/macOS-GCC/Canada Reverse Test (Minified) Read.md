
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 401.936 | 0.709598 | 7674.24ms | 2090234 | 80 | 9.90811e+10 | 4.9595e+06 | 0.510645 | 1(Win) | true |
| simdjson (ondemand) | 367.334 | 2.6382 | 7755.2ms | 2090234 | 40 | 8.19869e+11 | 5.42668e+06 | 2.90737 | 2(Loss) | true |
