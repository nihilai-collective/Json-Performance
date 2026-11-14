
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 790.89 | 0.290381 | 6018.46ms | 409725 | 30 | 6.17463e+07 | 494056 | 0.509782 | 3.13018 | 1(Win) | true |
| simdjson (ondemand) | 382.687 | 0.12561 | 6222.78ms | 409725 | 80 | 1.31594e+08 | 1.02105e+06 | 0.261618 | 6.4693 | 2(Loss) | true |
