
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 960.014 | 0.824744 | 7819.91ms | 2090234 | 30 | 8.79821e+09 | 2.07643e+06 | 0.824766 | 2.5789 | 1(Win) | true |
| simdjson (ondemand) | 885.635 | 0.101601 | 8372.57ms | 2090234 | 80 | 4.18378e+08 | 2.25082e+06 | 0.0911498 | 2.79547 | 2(Loss) | true |
