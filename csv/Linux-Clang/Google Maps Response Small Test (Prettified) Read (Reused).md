
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3801.1 | 0.0541519 | 256.048ms | 9378 | 80 | 129.873 | 2352.89 | 0.207089 | 0.643923 | 1(Win) | true |
| Jsonifier | 3291.05 | 0.157005 | 292.786ms | 9378 | 4890 | 89020.7 | 2717.54 | 0.072648 | 0.744664 | 2(Loss) | true |
| Glaze | 2790.36 | 0.0755705 | 343.206ms | 9378 | 30 | 176.006 | 3205.17 | 0.021835 | 0.880245 | 3(Loss) | true |
| simdjson (ondemand) | 2227.89 | 0.168192 | 422.586ms | 9378 | 30 | 1367.62 | 4014.37 | 0.276439 | 1.1037 | 4(Loss) | true |
