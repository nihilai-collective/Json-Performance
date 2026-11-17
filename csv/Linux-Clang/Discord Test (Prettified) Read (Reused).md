
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2332.79 | 0.142176 | 3792.33ms | 83958 | 1280 | 3.04814e+06 | 34323.1 | 0.185615 | 1.06043 | 1(Win) | true |
| simdjson (ondemand) | 2000.15 | 0.506299 | 4417.35ms | 83958 | 80 | 3.28628e+06 | 40031.4 | 0.614398 | 1.23694 | 2(Loss) | true |
