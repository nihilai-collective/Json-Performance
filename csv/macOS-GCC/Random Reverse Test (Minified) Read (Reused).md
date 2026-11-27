
----
### Random Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 799.416 | 0.395647 | 7185.95ms | 409725 | 40 | 1.49595e+08 | 488787 | 0.327098 | 1(Win) | true |
| simdjson (ondemand) | 361.46 | 0.476343 | 7347.11ms | 409725 | 40 | 1.06063e+09 | 1.08102e+06 | 0.353903 | 2(Loss) | true |
