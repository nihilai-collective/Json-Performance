
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1494.92 | 0.0552818 | 3939.47ms | 53331 | 30 | 10612.3 | 34022.2 | 0.147081 | 1(Win) | true |
| simdjson (ondemand) | 942.432 | 0.148731 | 6059.86ms | 53331 | 320 | 2.06163e+06 | 53967.2 | 0.0208098 | 2(Loss) | true |
