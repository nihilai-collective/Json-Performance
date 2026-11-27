
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 482.562 | 0.483937 | 6115.91ms | 1834197 | 30 | 9.23176e+09 | 3.62487e+06 | 0.276428 | 1(Win) | true |
| Jsonifier (generic) | 462.464 | 0.45939 | 6205.46ms | 1834197 | 80 | 2.41541e+10 | 3.78241e+06 | 0.172544 | 2(Loss) | true |
