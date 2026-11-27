
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2113.67 | 0.717194 | 3223.33ms | 56369 | 30 | 998161 | 25433.3 | 0.508541 | 1.43624 | 1(Win) | true |
| Glaze | 1770.55 | 0.801899 | 3559.81ms | 56369 | 4890 | 2.89876e+08 | 30362.1 | 0.103407 | 1.71513 | 2(Loss) | true |
| Jsonifier (two-stage) | 1445.84 | 0.266251 | 4211.98ms | 56369 | 4890 | 4.79219e+07 | 37181 | 0.283064 | 2.1005 | 3(Loss) | true |
| simdjson (ondemand) | 1010.1 | 0.501833 | 5952.9ms | 56369 | 320 | 2.28254e+07 | 53220 | 0.395368 | 3.00737 | 4(Loss) | true |
