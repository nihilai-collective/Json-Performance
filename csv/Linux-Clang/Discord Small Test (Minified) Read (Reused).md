
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3119.29 | 0.134251 | 171.503ms | 4857 | 40 | 158.972 | 1484.95 | 0.0280672 | 0.780852 | 1(Win) | true |
| Jsonifier (two-stage) | 2253.87 | 0.154291 | 229.004ms | 4857 | 30 | 301.637 | 2055.13 | 0.241089 | 1.08468 | 2(Loss) | true |
| Glaze | 2127.91 | 0.161363 | 241.291ms | 4857 | 4890 | 60331.8 | 2176.78 | 0.134789 | 1.14922 | 3(Loss) | true |
| simdjson (ondemand) | 900.048 | 0.220493 | 535.395ms | 4857 | 2560 | 329635 | 5146.39 | 0.0524819 | 2.73608 | 4(Loss) | true |
