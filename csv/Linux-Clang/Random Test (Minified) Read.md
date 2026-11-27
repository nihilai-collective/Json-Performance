
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 23534.7 | 0.118438 | 1882.93ms | 461466 | 1280 | 627852 | 18699.6 | 0.0321133 | 0.105056 | 1(Win) | true |
| simdjson (stage-1) | 18608.4 | 0.0603405 | 2375.31ms | 461466 | 4890 | 995836 | 23650 | 0.15645 | 0.132882 | 2(Loss) | true |
