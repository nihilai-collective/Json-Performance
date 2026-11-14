
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8326.58 | 0.0762357 | 6186.01ms | 466906 | 1280 | 2.12742e+06 | 53476.5 | 0.0103087 | 0.605532 | 3.02291 | 0.383405 | 0.00108391 | 4.0091e-06 | 2.11331e-06 | 1(Win) | true |
| Jsonifier | 8264.04 | 0.0371375 | 6236.41ms | 466906 | 4890 | 1.95798e+06 | 53881.2 | 0.0888979 | 0.609971 | 3.03245 | 0.385832 | 0.00112993 | 3.55646e-06 | 1.7029e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6921.54 | 0.0920676 | 7308.86ms | 466906 | 640 | 2.24516e+06 | 64332 | 0.117883 | 0.728972 | 3.43715 | 0.371826 | 0.000791069 | 7.8375e-06 | 3.20595e-06 | 3(Loss) | true |
| Glaze | 3448.31 | 0.0742109 | 7011.67ms | 466906 | 320 | 2.93854e+06 | 129129 | 0.0970952 | 1.4672 | 5.69568 | 0.986075 | 0.00163759 | 1.43832e-05 | 9.85878e-06 | 4(Loss) | true |
