
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 846.508 | 0.0818853 | 8828.07ms | 2090234 | 80 | 2.97461e+08 | 2.35485e+06 | 0.0473293 | 2.92468 | 1(Win) | true |
| simdjson (ondemand) | 825.025 | 0.061578 | 9024.6ms | 2090234 | 80 | 1.77091e+08 | 2.41617e+06 | 0.953223 | 3.00084 | 2(Loss) | true |
