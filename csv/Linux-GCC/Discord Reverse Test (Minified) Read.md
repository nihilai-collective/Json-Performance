
----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 784.035 | 0.205193 | 6948.23ms | 56369 | 80 | 1.58353e+06 | 68565.4 | 0.0521857 | 3.15661 | 1(Win) | true |
| simdjson (ondemand) | 188.624 | 0.0862951 | 7241.53ms | 56369 | 640 | 3.87115e+07 | 284999 | 0.0901689 | 13.1244 | 2(Loss) | true |
