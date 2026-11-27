
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1062.83 | 0.693614 | 5771.64ms | 124597 | 2560 | 1.53945e+09 | 111801 | 1.23395 | 2.85883 | 1(Win) | true |
| Jsonifier (two-stage) | 956.575 | 1.45346 | 6227.06ms | 124597 | 640 | 2.08623e+09 | 124219 | 1.0657 | 3.17636 | 2(Loss) | true |
| Glaze | 901.495 | 0.696351 | 6656.39ms | 124597 | 2560 | 2.15668e+09 | 131809 | 0.661159 | 3.37041 | 3(Loss) | true |
| simdjson (ondemand) | 827.255 | 0.780189 | 7315.73ms | 124597 | 2560 | 3.21497e+09 | 143638 | 0.821045 | 3.67274 | 4(Loss) | true |
