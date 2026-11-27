
----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13601.7 | 0.15482 | 3371.73ms | 475954 | 2560 | 6.83348e+06 | 33371.3 | 0.380262 | 0.181843 | 1(Win) | true |
| Glaze | 5366.94 | 0.145785 | 8566.86ms | 475954 | 1280 | 1.94585e+07 | 84574.3 | 0.186482 | 0.461133 | 2(Loss) | true |
