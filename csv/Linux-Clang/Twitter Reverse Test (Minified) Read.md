
----
### Twitter Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 685.659 | 0.130618 | 9474.94ms | 264040 | 1280 | 2.94535e+08 | 367250 | 0.47524 | 3.61041 | 1(Win) | true |
| simdjson (ondemand) | 246.892 | 0.149989 | 6373.56ms | 264040 | 30 | 7.02045e+07 | 1.01991e+06 | 0.651511 | 10.0274 | 2(Loss) | true |
