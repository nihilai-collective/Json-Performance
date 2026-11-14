
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1467.38 | 0.113181 | 9793.28ms | 264040 | 1280 | 4.82855e+07 | 171604 | 0.00346011 | 2.07097 | 1(Win) | true |
| simdjson (ondemand) | 1227.29 | 0.199384 | 5738.15ms | 264040 | 320 | 5.35519e+07 | 205174 | 0.00670117 | 2.47619 | 2(Loss) | true |
