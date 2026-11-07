
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2180.95 | 0.575785 | 284.449ms | 5094 | 640 | 105276 | 2227.48 | 0.203417 | 1.12208 | 1(Win) | true |
| Jsonifier (two-stage) | 1828.9 | 0.282526 | 317.4ms | 5094 | 160 | 9011 | 2656.24 | 0.400508 | 1.33936 | 2(Loss) | true |
| Glaze | 1581.43 | 0.0576544 | 359.045ms | 5094 | 80 | 250.942 | 3071.91 | 0.13079 | 1.55205 | 3(Loss) | true |
| simdjson (ondemand) | 961.324 | 0.182876 | 554.039ms | 5094 | 2560 | 218642 | 5053.47 | 0.141447 | 2.56074 | 4(Loss) | true |
