
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2907.93 | 0.112749 | 9350.25ms | 466906 | 640 | 1.90764e+07 | 153125 | 0.0749665 | 1(Win) | true |
| Jsonifier (two-stage) | 2184.7 | 0.127501 | 6160.13ms | 466906 | 320 | 2.16099e+07 | 203816 | 0.0197629 | 2(Loss) | true |
| Glaze | 2117.23 | 0.123495 | 6069.8ms | 466906 | 1280 | 8.63436e+07 | 210310 | 0.082806 | 3(Loss) | true |
| simdjson (ondemand) | 907.351 | 0.186377 | 6631.88ms | 466906 | 30 | 2.50966e+07 | 490743 | 0.0260693 | 4(Loss) | true |
