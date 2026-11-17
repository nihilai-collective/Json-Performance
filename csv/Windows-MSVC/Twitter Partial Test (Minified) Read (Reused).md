
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8373.4 | 0.575247 | 5822.06ms | 466906 | 80 | 7.48607e+06 | 53177.5 | 0.197843 | 0.295491 | 1(Win) | true |
| Jsonifier (two-stage) | 7935.86 | 0.341556 | 5846.79ms | 466906 | 320 | 1.17529e+07 | 56109.4 | 0.385777 | 0.311747 | 2(Loss) | true |
| simdjson (ondemand) | 3089.03 | 0.451959 | 7500.99ms | 466906 | 40 | 1.69774e+07 | 144148 | 0.0399056 | 0.801319 | 3(Loss) | true |
| Glaze | 2745.71 | 0.0824496 | 8427.6ms | 466906 | 2560 | 4.57685e+07 | 162172 | 0.348499 | 0.901532 | 4(Loss) | true |
