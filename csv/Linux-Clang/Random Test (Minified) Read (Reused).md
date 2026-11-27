
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1445.68 | 0.278732 | 8257.04ms | 409725 | 30 | 1.70269e+07 | 270284 | 0.0303539 | 1.71234 | 1(Win) | true |
| simdjson (ondemand) | 1280.72 | 0.0910372 | 9044.59ms | 409725 | 320 | 2.46866e+07 | 305096 | 0.0192218 | 1.93292 | 2(Loss) | true |
