
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 944.862 | 0.0991897 | 8049.97ms | 2090234 | 80 | 3.50329e+08 | 2.10973e+06 | 0.120304 | 2.62021 | 1(Win) | true |
| simdjson (ondemand) | 851.327 | 0.103368 | 8630.67ms | 2090234 | 40 | 2.34329e+08 | 2.34152e+06 | 0.000161931 | 2.90812 | 2(Loss) | true |
