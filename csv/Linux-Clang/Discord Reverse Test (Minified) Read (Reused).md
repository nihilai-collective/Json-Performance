
----
### Discord Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 784.716 | 0.0333705 | 7941.8ms | 56369 | 4890 | 2.55558e+06 | 68505.9 | 0.0640101 | 6.47528 | 31.3328 | 6.68967 | 0.0090664 | 2.48654e-05 | 1.59989e-05 | 1(Win) | true |
| simdjson (ondemand) | 205.586 | 0.0471633 | 6948.55ms | 56369 | 1280 | 1.94677e+07 | 261486 | 0.187368 | 24.619 | 137.594 | 27.6144 | 0.0373479 | 0.000113441 | 8.73984e-05 | 2(Loss) | true |
