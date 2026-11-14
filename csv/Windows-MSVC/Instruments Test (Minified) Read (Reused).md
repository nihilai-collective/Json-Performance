
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2929.22 | 0.125219 | 3793.75ms | 108313 | 320 | 623948 | 35263.8 | 0.0922476 | 1.03688 | 1(Win) | true |
| Jsonifier (two-stage) | 1776.59 | 0.0440606 | 6071.1ms | 108313 | 2560 | 1.68007e+06 | 58142.4 | 0.00356064 | 1.71011 | 2(Loss) | true |
| Glaze | 1742.33 | 0.168358 | 6230.63ms | 108313 | 1280 | 1.2752e+07 | 59285.7 | 0.0754513 | 1.7435 | 3(Loss) | true |
| simdjson (ondemand) | 991.74 | 0.0924404 | 5479.88ms | 108313 | 640 | 5.93293e+06 | 104156 | 0.132189 | 3.06388 | 4(Loss) | true |
