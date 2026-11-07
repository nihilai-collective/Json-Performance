
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1512.16 | 0.222825 | 367.295ms | 4857 | 2560 | 119264 | 3063.16 | 0.239039 | 1.62338 | 1(Win) | true |
| Glaze | 1435.17 | 0.28675 | 394.409ms | 4857 | 160 | 13704.4 | 3227.5 | 0.0775194 | 1.71159 | 2(Loss) | true |
| Jsonifier (two-stage) | 1160.54 | 0.161894 | 465.433ms | 4857 | 80 | 3340.19 | 3991.25 | 0.281074 | 2.12154 | 3(Loss) | true |
| simdjson (ondemand) | 942.9 | 0.166008 | 532.158ms | 4857 | 40 | 2660.26 | 4912.5 | 0.0169607 | 2.60774 | 4(Loss) | true |
