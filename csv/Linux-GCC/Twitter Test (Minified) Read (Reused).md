
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2271.24 | 0.199776 | 5592.22ms | 466906 | 640 | 9.81746e+07 | 196050 | 0.000184903 | 1.0899 | 1(Win) | true |
| Jsonifier (two-stage) | 2142.78 | 0.783328 | 6052.1ms | 466906 | 160 | 4.23947e+08 | 207803 | 0.0105068 | 1.15523 | 2(Loss) | true |
| Glaze | 2014.22 | 0.25403 | 6126.78ms | 466906 | 80 | 2.52292e+07 | 221066 | 0.32545 | 1.22901 | 3(Loss) | true |
| simdjson (reflection) | 1966.5 | 0.224062 | 6509.67ms | 466906 | 160 | 4.11838e+07 | 226430 | 0.0151366 | 1.25877 | 4(Loss) | true |
| simdjson (ondemand) | 1099.09 | 0.172845 | 5410.42ms | 466906 | 80 | 3.92282e+07 | 405132 | 0.28804 | 2.25242 | 5(Loss) | true |
