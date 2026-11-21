
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8076.04 | 0.0587405 | 48.2577ms | 3808 | 320 | 22.3266 | 449.675 | 0.194207 | 0.288518 | 1(Win) | true |
| Jsonifier | 7819.4 | 0.0339471 | 49.4704ms | 3808 | 1280 | 31.8173 | 464.434 | 0.0102601 | 0.298827 | 2(Loss) | true |
| simdjson (ondemand) | 7781.75 | 0.034156 | 49.7942ms | 3808 | 1280 | 32.5225 | 466.68 | 0.00786869 | 0.299375 | 3(Loss) | true |
| Glaze | 4012.92 | 0.0505688 | 93.8852ms | 3808 | 160 | 33.5088 | 904.975 | 0.0138144 | 0.599358 | 4(Loss) | true |
