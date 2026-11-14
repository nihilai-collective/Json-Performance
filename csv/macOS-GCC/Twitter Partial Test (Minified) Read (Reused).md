
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5338.38 | 0.191109 | 5216.24ms | 466906 | 320 | 8.13116e+06 | 83410.4 | 0.000959122 | 1(Win) | true |
| Jsonifier (two-stage) | 4736.01 | 0.558383 | 5104.64ms | 466906 | 640 | 1.76392e+08 | 94019.2 | 1.39421 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 3830.77 | 0.247541 | 6048.06ms | 466906 | 1280 | 1.05972e+08 | 116237 | 0.515411 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3815.8 | 0.24146 | 6167.76ms | 466906 | 320 | 2.54056e+07 | 116693 | 0.315729 | 3(Tie) | true |
| Glaze | 2389.01 | 0.553605 | 5013.45ms | 466906 | 30 | 3.19406e+07 | 186385 | 0.155421 | 5(Loss) | true |
